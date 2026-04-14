#include <memory>
#include <map>
#include <string>
#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

#include "smarthome_vision/msg/detected_target.hpp"
#include "smarthome_vision/detector.hpp"
#include "smarthome_vision/gimbal_bridge.hpp"
#include "smarthome_vision/pose_solver.hpp"
#include "smarthome_vision/types.hpp"

using std::placeholders::_1;

namespace smarthome_vision
{

class VisionNode : public rclcpp::Node
{
public:
  VisionNode() : Node("smarthome_vision_node")
  {
    // 参数声明
    declare_parameter<std::string>("image_topic", "/camera/image_raw");
    declare_parameter<std::string>("serial_device", "/dev/gimbal");
    declare_parameter<int>("baudrate", 115200);
    declare_parameter<int>("input_width", 640);
    declare_parameter<int>("input_height", 640);
    declare_parameter<double>("conf_threshold", 0.25);
    declare_parameter<double>("score_threshold", 0.25);
    declare_parameter<bool>("show_debug", false);
    declare_parameter<bool>("use_cuda_preprocess", true);
    declare_parameter<std::string>("keypoint_engine_path", "");
    declare_parameter<bool>("use_keypoint_detector", false);
    declare_parameter<std::string>("bbox_engine_path", "");
    declare_parameter<bool>("use_bbox_detector", true);
    declare_parameter<bool>("enable_bbox_fallback", true);
    declare_parameter<bool>("force_bbox_only", false);

    declare_parameter<std::vector<double>>("camera_matrix", {800.0, 0.0, 320.0, 0.0, 800.0, 240.0, 0.0, 0.0, 1.0});
    declare_parameter<std::vector<double>>("dist_coeffs", {0.0, 0.0, 0.0, 0.0, 0.0});
    declare_parameter<std::vector<long int>>("class_names", {0, 1, 2, 3});
    declare_parameter<std::vector<double>>("class_sizes", {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05});

    // 读取调试标志
    show_debug_ = get_parameter("show_debug").as_bool();

    // 初始化相机内参和结算器
    auto k = get_parameter("camera_matrix").as_double_array();
    auto d = get_parameter("dist_coeffs").as_double_array();
    auto class_names = get_parameter("class_names").as_integer_array();
    auto class_sizes = get_parameter("class_sizes").as_double_array();

    CameraIntrinsics cam;
    cam.camera_matrix = (cv::Mat_<double>(3, 3) << k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7], k[8]);
    cam.dist_coeffs = cv::Mat(d).clone().reshape(1, 1);

    std::map<int, cv::Size2f> class_size_map;
    for (size_t i = 0; i < class_names.size(); ++i) {
      size_t idx = i * 2;
      if (idx + 1 < class_sizes.size()) {
        class_size_map[static_cast<int>(class_names[i])] =
          cv::Size2f(static_cast<float>(class_sizes[idx]), static_cast<float>(class_sizes[idx + 1]));
      }
    }

    pose_solver_ = std::make_unique<PoseSolver>();
    pose_solver_->set_camera(cam);
    pose_solver_->set_class_size_map(class_size_map);

    // 初始化检测器
    detector_ = std::make_unique<Detector>(
      get_parameter("keypoint_engine_path").as_string(),
      get_parameter("use_keypoint_detector").as_bool(),
      get_parameter("bbox_engine_path").as_string(),
      get_parameter("use_bbox_detector").as_bool(),
      get_parameter("enable_bbox_fallback").as_bool(),
      get_parameter("force_bbox_only").as_bool(),
      get_parameter("input_width").as_int(),
      get_parameter("input_height").as_int(),
      static_cast<float>(get_parameter("conf_threshold").as_double()),
      static_cast<float>(get_parameter("score_threshold").as_double()),
      get_parameter("use_cuda_preprocess").as_bool());

    gimbal_ = std::make_unique<GimbalBridge>(
      get_parameter("serial_device").as_string(),
      get_parameter("baudrate").as_int());

    // 发布器和订阅器
    pub_ = create_publisher<smarthome_vision::msg::DetectedTarget>("detected_target", 10);
    
    // 新增：调试图像发布器
    debug_img_pub_ = create_publisher<sensor_msgs::msg::Image>("vision/debug_image", 10);

    sub_ = create_subscription<sensor_msgs::msg::Image>(
      get_parameter("image_topic").as_string(), 10,
      std::bind(&VisionNode::imageCallback, this, _1));
      
    RCLCPP_INFO(this->get_logger(), "Vision Node started. Publishing debug images to /vision/debug_image");
  }

private:
  void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
  {
    cv::Mat image;
    try {
      image = cv_bridge::toCvCopy(msg, "bgr8")->image;
    } catch (const std::exception & e) {
      RCLCPP_WARN(this->get_logger(), "cv_bridge error: %s", e.what());
      return;
    }

    // 执行推理
    auto dets = detector_->infer(image);

    Detection best_det;
    PoseResult best_pose;
    bool found = false;
    float best_score = -1.0f;

    // 位姿解算
    for (const auto & det : dets) {
      auto pose = pose_solver_->solve(det);
      if (!pose.success) continue;

      if (det.score > best_score) {
        best_score = det.score;
        best_det = det;
        best_pose = pose;
        found = true;
      }
    }

    // 填充并发布目标消息
    smarthome_vision::msg::DetectedTarget out;
    out.stamp = msg->header.stamp;

    if (found) {
      out.tracking = true;
      out.class_id = best_det.class_id;
      out.score = best_det.score;
      out.x = static_cast<float>(best_pose.tvec[0]);
      out.y = static_cast<float>(best_pose.tvec[1]);
      out.z = static_cast<float>(best_pose.tvec[2]);

      out.corners_uv.resize(8);
      for (int i = 0; i < 4; ++i) {
        out.corners_uv[2 * i] = best_det.corners[i].x;
        out.corners_uv[2 * i + 1] = best_det.corners[i].y;
      }

      gimbal_->sendTarget(true, static_cast<uint8_t>(best_det.class_id), out.x, out.y, out.z);
    } else {
      out.tracking = false;
      out.class_id = -1;
      gimbal_->sendTarget(false, 0, 0.0f, 0.0f, 0.0f);
    }
    pub_->publish(out);

    // --- 可视化绘图与发布逻辑 ---
    if (show_debug_) {
      for (const auto & det : dets) {
        // 画框和角点
        cv::rectangle(image, det.bbox, cv::Scalar(0, 255, 0), 2);
        for (const auto & pt : det.corners) {
          cv::circle(image, pt, 4, cv::Scalar(0, 0, 255), -1);
        }
        std::string label = "ID:" + std::to_string(det.class_id) + " Conf:" + std::to_string(det.score).substr(0, 4);
        cv::putText(image, label, cv::Point(det.bbox.x, det.bbox.y - 5), 
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
      }

      if (found) {
        std::string pose_text = "X=" + std::to_string(out.x).substr(0, 5) + " Z=" + std::to_string(out.z).substr(0, 5);
        cv::putText(image, pose_text, cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 0), 2);
      }

      // 将画好框的 image 转换并发布到 /vision/debug_image
      auto debug_msg = cv_bridge::CvImage(msg->header, "bgr8", image).toImageMsg();
      debug_img_pub_->publish(*debug_msg);
    }
  }

private:
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
  rclcpp::Publisher<smarthome_vision::msg::DetectedTarget>::SharedPtr pub_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr debug_img_pub_; // 图像发布器

  std::unique_ptr<Detector> detector_;
  std::unique_ptr<PoseSolver> pose_solver_;
  std::unique_ptr<GimbalBridge> gimbal_;
  bool show_debug_;
};

} // namespace smarthome_vision

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<smarthome_vision::VisionNode>());
  rclcpp::shutdown();
  return 0;
}
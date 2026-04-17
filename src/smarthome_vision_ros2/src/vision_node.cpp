#include <memory>
#include <map>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <iomanip>

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

namespace
{

cv::Scalar colorForClass(int class_id)
{
  static const std::array<cv::Scalar, 6> colors = {
    cv::Scalar(255, 0, 0),
    cv::Scalar(0, 255, 0),
    cv::Scalar(0, 255, 255),
    cv::Scalar(255, 0, 255),
    cv::Scalar(255, 255, 0),
    cv::Scalar(0, 128, 255)
  };
  return colors[static_cast<size_t>(std::abs(class_id)) % colors.size()];
}

void drawDetectionDebug(cv::Mat & image, const Detection & det)
{
  const cv::Scalar bbox_color = colorForClass(det.class_id);

  if (det.has_bbox) {
    cv::rectangle(image, det.bbox, bbox_color, 2);
  }

  std::ostringstream oss;
  oss << "ID:" << det.class_id
      << " Conf:" << std::fixed << std::setprecision(2) << det.score
      << " Src:" << (det.corner_source == CornerSource::KEYPOINT ? "KP" : "BBOX");

  const std::string label = oss.str();

  int baseline = 0;
  const cv::Size text_size =
    cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.55, 1, &baseline);

  const int tx = std::max(0, static_cast<int>(det.bbox.x));
  const int ty = std::max(text_size.height + 6, static_cast<int>(det.bbox.y) - 6);

  cv::rectangle(
    image,
    cv::Rect(tx, ty - text_size.height - 6, text_size.width + 8, text_size.height + 8),
    bbox_color,
    cv::FILLED);

  cv::putText(
    image,
    label,
    cv::Point(tx + 4, ty - 4),
    cv::FONT_HERSHEY_SIMPLEX,
    0.55,
    cv::Scalar(255, 255, 255),
    1);

  static const std::array<std::string, 4> names = {"P0(TL)", "P1(TR)", "P2(BR)", "P3(BL)"};

  for (int i = 0; i < 4; ++i) {
    const cv::Point2f & p = det.corners[i];
    cv::circle(image, p, 5, cv::Scalar(0, 0, 255), -1);
    cv::putText(
      image,
      names[i],
      cv::Point(static_cast<int>(p.x) + 6, static_cast<int>(p.y) - 6),
      cv::FONT_HERSHEY_SIMPLEX,
      0.5,
      cv::Scalar(0, 0, 255),
      2);
  }

  for (int i = 0; i < 4; ++i) {
    const cv::Point2f & p1 = det.corners[i];
    const cv::Point2f & p2 = det.corners[(i + 1) % 4];
    cv::line(image, p1, p2, cv::Scalar(0, 255, 255), 2);
  }
}

void drawPoseInsideBox(
  cv::Mat & image,
  const Detection & det,
  const PoseResult & pose)
{
  if (!det.has_bbox) {
    return;
  }

  const int x = std::max(0, static_cast<int>(det.bbox.x));
  const int y = std::max(0, static_cast<int>(det.bbox.y));

  const double font_scale = 0.45;
  const int thickness = 1;
  const int line_gap = 4;
  const int padding = 4;

  std::ostringstream sx, sy, sz;
  sx << "X=" << std::fixed << std::setprecision(3) << pose.tvec[0];
  sy << "Y=" << std::fixed << std::setprecision(3) << pose.tvec[1];
  sz << "Z=" << std::fixed << std::setprecision(3) << pose.tvec[2];

  const std::string line1 = sx.str();
  const std::string line2 = sy.str();
  const std::string line3 = sz.str();

  int base1 = 0, base2 = 0, base3 = 0;
  const cv::Size s1 = cv::getTextSize(line1, cv::FONT_HERSHEY_SIMPLEX, font_scale, thickness, &base1);
  const cv::Size s2 = cv::getTextSize(line2, cv::FONT_HERSHEY_SIMPLEX, font_scale, thickness, &base2);
  const cv::Size s3 = cv::getTextSize(line3, cv::FONT_HERSHEY_SIMPLEX, font_scale, thickness, &base3);

  const int text_w = std::max({s1.width, s2.width, s3.width});
  const int line_h = std::max({s1.height, s2.height, s3.height});
  const int box_h = padding * 2 + line_h * 3 + line_gap * 2;
  const int box_w = padding * 2 + text_w;

  int bx = x + 2;
  int by = y + 2;

  bx = std::min(std::max(0, bx), std::max(0, image.cols - box_w - 1));
  by = std::min(std::max(0, by), std::max(0, image.rows - box_h - 1));

  cv::rectangle(
    image,
    cv::Rect(bx, by, std::min(box_w, image.cols - bx), std::min(box_h, image.rows - by)),
    cv::Scalar(0, 0, 0),
    cv::FILLED);

  cv::rectangle(
    image,
    cv::Rect(bx, by, std::min(box_w, image.cols - bx), std::min(box_h, image.rows - by)),
    cv::Scalar(255, 255, 0),
    1);

  const int tx = bx + padding;
  int ty = by + padding + line_h;

  cv::putText(
    image, line1,
    cv::Point(tx, ty),
    cv::FONT_HERSHEY_SIMPLEX, font_scale,
    cv::Scalar(255, 255, 0), thickness);

  ty += line_h + line_gap;
  cv::putText(
    image, line2,
    cv::Point(tx, ty),
    cv::FONT_HERSHEY_SIMPLEX, font_scale,
    cv::Scalar(255, 255, 0), thickness);

  ty += line_h + line_gap;
  cv::putText(
    image, line3,
    cv::Point(tx, ty),
    cv::FONT_HERSHEY_SIMPLEX, font_scale,
    cv::Scalar(255, 255, 0), thickness);
}

}  // namespace

class VisionNode : public rclcpp::Node
{
public:
  VisionNode() : Node("smarthome_vision_node")
  {
    declare_parameter<std::string>("image_topic", "/image_raw");
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

    declare_parameter<std::vector<double>>(
      "camera_matrix",
      {800.0, 0.0, 320.0, 0.0, 800.0, 240.0, 0.0, 0.0, 1.0});
    declare_parameter<std::vector<double>>("dist_coeffs", {0.0, 0.0, 0.0, 0.0, 0.0});
    declare_parameter<std::vector<long int>>("class_names", {0, 1, 2, 3});
    declare_parameter<std::vector<double>>(
      "class_sizes",
      {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05});

    show_debug_ = get_parameter("show_debug").as_bool();

    auto k = get_parameter("camera_matrix").as_double_array();
    auto d = get_parameter("dist_coeffs").as_double_array();
    auto class_names = get_parameter("class_names").as_integer_array();
    auto class_sizes = get_parameter("class_sizes").as_double_array();

    CameraIntrinsics cam;
    cam.camera_matrix =
      (cv::Mat_<double>(3, 3) << k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7], k[8]);
    cam.dist_coeffs = cv::Mat(d).clone().reshape(1, 1);

    std::map<int, cv::Size2f> class_size_map;
    for (size_t i = 0; i < class_names.size(); ++i) {
      const size_t idx = i * 2;
      if (idx + 1 < class_sizes.size()) {
        class_size_map[static_cast<int>(class_names[i])] =
          cv::Size2f(
            static_cast<float>(class_sizes[idx]),
            static_cast<float>(class_sizes[idx + 1]));
      }
    }

    pose_solver_ = std::make_unique<PoseSolver>();
    pose_solver_->set_camera(cam);
    pose_solver_->set_class_size_map(class_size_map);

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

    pub_ = create_publisher<smarthome_vision::msg::DetectedTarget>("detected_target", 10);

    sub_ = create_subscription<sensor_msgs::msg::Image>(
      get_parameter("image_topic").as_string(), 10,
      std::bind(&VisionNode::imageCallback, this, _1));

    if (show_debug_) {
      cv::namedWindow("smarthome_vision_debug", cv::WINDOW_NORMAL);
    }

    RCLCPP_INFO(this->get_logger(), "Vision Node started.");
  }

  ~VisionNode()
  {
    if (show_debug_) {
      cv::destroyWindow("smarthome_vision_debug");
    }
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

    auto dets = detector_->infer(image);

    Detection best_det;
    PoseResult best_pose;
    bool found = false;
    float best_score = -1.0f;

    for (const auto & det : dets) {
      auto pose = pose_solver_->solve(det);
      if (!pose.success) {
        continue;
      }

      if (det.score > best_score) {
        best_score = det.score;
        best_det = det;
        best_pose = pose;
        found = true;
      }
    }

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

      gimbal_->sendTarget(
        true,
        static_cast<uint8_t>(best_det.class_id),
        out.x, out.y, out.z);
    } else {
      out.tracking = false;
      out.class_id = -1;
      gimbal_->sendTarget(false, 0, 0.0f, 0.0f, 0.0f);
    }

    pub_->publish(out);

    if (show_debug_) {
      cv::Mat vis = image.clone();

      for (const auto & det : dets) {
        drawDetectionDebug(vis, det);
      }

      if (found) {
        drawPoseInsideBox(vis, best_det, best_pose);
      }

      const int scale = 2;
      cv::Mat vis_big;
      cv::resize(
        vis,
        vis_big,
        cv::Size(vis.cols * scale, vis.rows * scale),
        0,
        0,
        cv::INTER_NEAREST);

      cv::resizeWindow("smarthome_vision_debug", vis_big.cols, vis_big.rows);
      cv::imshow("smarthome_vision_debug", vis_big);
      cv::waitKey(1);
    }
  }

private:
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
  rclcpp::Publisher<smarthome_vision::msg::DetectedTarget>::SharedPtr pub_;

  std::unique_ptr<Detector> detector_;
  std::unique_ptr<PoseSolver> pose_solver_;
  std::unique_ptr<GimbalBridge> gimbal_;
  bool show_debug_;
};

}  // namespace smarthome_vision

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<smarthome_vision::VisionNode>());
  rclcpp::shutdown();
  return 0;
}
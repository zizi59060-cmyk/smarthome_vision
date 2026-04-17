#include "smarthome_vision/detector.hpp"

#include <opencv2/imgproc.hpp>

#include <algorithm>
#include <cmath>
#include <vector>

namespace smarthome_vision
{

Detector::Detector(
  const std::string & keypoint_engine_path,
  bool use_keypoint_detector,
  const std::string & bbox_engine_path,
  bool use_bbox_detector,
  bool enable_bbox_fallback,
  bool force_bbox_only,
  int input_width,
  int input_height,
  float conf_thres,
  float score_thres,
  bool use_cuda_preprocess)
: use_keypoint_detector_(use_keypoint_detector),
  use_bbox_detector_(use_bbox_detector),
  enable_bbox_fallback_(enable_bbox_fallback),
  force_bbox_only_(force_bbox_only),
  use_cuda_preprocess_(use_cuda_preprocess)
{
  if (use_keypoint_detector_) {
    keypoint_detector_ = std::make_unique<TRTDetector>(
      keypoint_engine_path,
      input_width,
      input_height,
      conf_thres,
      score_thres,
      true,
      use_cuda_preprocess_);
  }

  if (use_bbox_detector_) {
    bbox_detector_ = std::make_unique<TRTDetector>(
      bbox_engine_path,
      input_width,
      input_height,
      conf_thres,
      score_thres,
      false,
      use_cuda_preprocess_);
  }
}

std::array<cv::Point2f, 4> Detector::bbox_to_corners(const cv::Rect2f & box)
{
  return {
    cv::Point2f(box.x, box.y),
    cv::Point2f(box.x + box.width, box.y),
    cv::Point2f(box.x + box.width, box.y + box.height),
    cv::Point2f(box.x, box.y + box.height)
  };
}

// 语义关键点模型：固定输出顺序就是 TL, TR, BR, BL
// 因此这里不再做几何重排，直接原样返回
std::array<cv::Point2f, 4> Detector::reorder_corners(const std::array<cv::Point2f, 4> & pts)
{
  return pts;
}

bool Detector::keypoints_valid(
  const std::array<cv::Point2f, 4> & pts,
  const cv::Rect2f & box,
  int img_w,
  int img_h)
{
  for (const auto & p : pts) {
    if (p.x < 0 || p.y < 0 || p.x >= img_w || p.y >= img_h) {
      return false;
    }
  }

  int outside_count = 0;
  for (const auto & p : pts) {
    if (!box.contains(p)) {
      outside_count++;
    }
  }
  if (outside_count > 1) {
    return false;
  }

  std::vector<cv::Point2f> poly = {pts[0], pts[1], pts[2], pts[3]};
  float area = std::fabs(static_cast<float>(cv::contourArea(poly)));
  if (area < 25.0f) {
    return false;
  }

  return true;
}

std::vector<Detection> Detector::infer(const cv::Mat & image)
{
  std::vector<Detection> out;

  std::vector<RawPrediction> kp_preds;
  std::vector<RawPrediction> box_preds;

  if (use_keypoint_detector_ && keypoint_detector_) {
    kp_preds = keypoint_detector_->infer(image);
  }

  if (use_bbox_detector_ && bbox_detector_) {
    box_preds = bbox_detector_->infer(image);
  }

  for (const auto & pred : kp_preds) {
    Detection det;
    det.class_id = pred.class_id;
    det.score = pred.score;
    det.bbox = pred.bbox;
    det.has_bbox = true;
    det.keypoints = pred.keypoints;
    det.has_keypoints = pred.has_keypoints;

    if (!force_bbox_only_ &&
        pred.has_keypoints &&
        keypoints_valid(pred.keypoints, pred.bbox, image.cols, image.rows)) {
      // 关键修改：
      // 网络输出语义已经固定为 TL, TR, BR, BL，不能再做几何重排
      det.corners = pred.keypoints;
      det.corner_source = CornerSource::KEYPOINT;
    } else if (enable_bbox_fallback_) {
      det.corners = bbox_to_corners(pred.bbox);
      det.corner_source = CornerSource::BBOX;
    } else {
      continue;
    }

    out.push_back(det);
  }

  if ((out.empty() || force_bbox_only_) && !box_preds.empty()) {
    out.clear();
    for (const auto & pred : box_preds) {
      Detection det;
      det.class_id = pred.class_id;
      det.score = pred.score;
      det.bbox = pred.bbox;
      det.has_bbox = true;
      det.has_keypoints = false;
      det.corners = bbox_to_corners(pred.bbox);
      det.corner_source = CornerSource::BBOX;
      out.push_back(det);
    }
  }

  return out;
}

}  // namespace smarthome_vision
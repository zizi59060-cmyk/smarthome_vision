#include "smarthome_vision/pose_solver.hpp"

#include <opencv2/calib3d.hpp>

namespace smarthome_vision
{

void PoseSolver::set_camera(const CameraIntrinsics & camera)
{
  camera_ = camera;
}

void PoseSolver::set_class_size_map(const std::map<int, cv::Size2f> & class_size_map)
{
  class_size_map_ = class_size_map;
}

PoseResult PoseSolver::solve(const Detection & det) const
{
  PoseResult result;

  auto it = class_size_map_.find(det.class_id);
  if (it == class_size_map_.end()) {
    return result;
  }

  if (camera_.camera_matrix.empty()) {
    return result;
  }

  const float w = it->second.width;
  const float h = it->second.height;

  std::vector<cv::Point3f> object_points = {
    {-w / 2.0f, -h / 2.0f, 0.0f},
    { w / 2.0f, -h / 2.0f, 0.0f},
    { w / 2.0f,  h / 2.0f, 0.0f},
    {-w / 2.0f,  h / 2.0f, 0.0f}
  };

  std::vector<cv::Point2f> image_points = {
    det.corners[0], det.corners[1], det.corners[2], det.corners[3]
  };

  cv::Vec3d rvec, tvec;
  bool ok = cv::solvePnP(
    object_points,
    image_points,
    camera_.camera_matrix,
    camera_.dist_coeffs,
    rvec,
    tvec,
    false,
    cv::SOLVEPNP_IPPE_SQUARE);

  if (!ok) {
    ok = cv::solvePnP(
      object_points,
      image_points,
      camera_.camera_matrix,
      camera_.dist_coeffs,
      rvec,
      tvec,
      false,
      cv::SOLVEPNP_ITERATIVE);
  }

  result.success = ok;
  result.rvec = rvec;
  result.tvec = tvec;
  return result;
}

}  // namespace smarthome_vision
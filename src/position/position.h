// Copyright 2026 NUX

#ifndef SRC_POSITION_POSITION_H_
#define SRC_POSITION_POSITION_H_

#include <opencv2/opencv.hpp>

namespace application::window::object_position {

// PositionCalculator tracks an object's motion across frames and computes
// kinematic properties like velocity and acceleration based on horizontal
// displacement.
class PositionCalculator {
 public:
  PositionCalculator() = default;

  // Analyzes the provided frame to locate the object, update its movement
  // state, and calculate kinematics if the object stops moving.
  void TrackObject(cv::Mat& mask, cv::Mat& hsv, cv::Mat& frame,
                   const cv::Scalar& lower_bound,
                   const cv::Scalar& upper_bound);

 private:
  double previous_position_ = 0.0;
  bool has_previous_position_ = false;
  bool is_moving_ = false;
  double start_position_ = 0.0;
  double last_position_ = 0.0;
  double start_time_ = 0.0;
  double last_movement_time_ = 0.0;

  // Threshold to filter noise and define active movement.
  const double movement_threshold_ = 5.0;
  // Duration of stillness to determine if the object has stopped.
  const double stop_time_ = 1.0;
};

}  // namespace application::window::object_position

#endif  // SRC_POSITION_POSITION_H_

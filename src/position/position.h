// Copyright 2026 NUX

#ifndef SRC_POSITION_POSITION_H_
#define SRC_POSITION_POSITION_H_

#include <deque>
#include <opencv2/geometry.hpp>
#include <opencv2/opencv.hpp>

#include "movement/movement.h"

namespace application::window::object_position {

class PositionCalculator {
 public:
  PositionCalculator(
      application::window::object_position::movement::MovementType type =
          application::window::object_position::movement::MovementType::
              Horizontal)
      : controller_(type) {}

  void SetMovementType(
      application::window::object_position::movement::MovementType type) {
    controller_.SetType(type);
  }

  // Analyzes the provided frame to locate the object, update its movement
  // state, and calculate kinematics if the object stops moving.
  void TrackObject(cv::Mat& mask, cv::Mat& hsv, cv::Mat& frame,
                   const cv::Scalar& lower_bound,
                   const cv::Scalar& upper_bound);

 private:
  double GetSmoothedPosition(double new_position);

  application::window::object_position::movement::MovementController
      controller_;
  double previous_position_ = 0.0;
  bool has_previous_position_ = false;
  bool is_moving_ = false;
  double start_position_ = 0.0;
  double last_position_ = 0.0;
  double start_time_ = 0.0;
  double last_movement_time_ = 0.0;

  // Smoothing buffer
  std::deque<double> position_buffer_;
  const size_t buffer_size_ = 5;

  // Threshold to filter noise and define active movement.
  const double movement_threshold_ = 5.0;
  // Duration of stillness to determine if the object has stopped.
  const double stop_time_ = 1.0;
};

}  // namespace application::window::object_position

#endif  // SRC_POSITION_POSITION_H_

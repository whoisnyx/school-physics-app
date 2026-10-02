#ifndef SRC_POSITION_POSITION_H_
#define SRC_POSITION_POSITION_H_

#include <cstddef>
#include <deque>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>

#include "movement/movement.h"

// Namespace for object position tracking and analysis.
namespace application::object::position {

// Class for tracking object position in video frames and calculating
// kinematics.
class ObjectPositionCalculator {
 public:
  // Constructs a calculator with a specific movement strategy.
  explicit ObjectPositionCalculator(
      std::unique_ptr<application::object::movement::Movement> movement);

  // Processes the video frame to track object position and compute physics.
  void TrackObject(cv::Mat& mask, cv::Mat& hsv, cv::Mat& frame,
                   const cv::Scalar& lower_bound,
                   const cv::Scalar& upper_bound);

 private:
  // Smooths position measurements using a rolling buffer.
  double GetSmoothedPosition(double new_position);

  std::unique_ptr<application::object::movement::Movement>
      movement_;  // Movement strategy.

  bool is_moving_ = false;  // Flag indicating if object is currently moving.
  bool has_previous_position_ =
      false;  // Flag indicating if a previous position exists.

  double previous_position_ = 0.0;  // Previous tracked position coordinate.
  double start_position_ = 0.0;     // Starting position of movement.
  double last_position_ = 0.0;      // Last recorded position during movement.

  double start_time_ = 0.0;    // Start timestamp of movement.
  double current_time_ = 0.0;  // Current timestamp.
  double last_movement_time_ =
      0.0;  // Last timestamp when movement was detected.

  std::deque<double>
      position_buffer_;  // Rolling buffer for position smoothing.

  static constexpr std::size_t kBufferSize = 5;  // Size of smoothing buffer.
  static constexpr double kMovementThreshold =
      5.0;  // Threshold to detect movement.
  static constexpr double kStopTime =
      2.0;  // Time threshold to consider object stopped.
};

}  // namespace application::object::position

#endif  // SRC_POSITION_POSITION_H_

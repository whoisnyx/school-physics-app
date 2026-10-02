#ifndef SRC_POSITION_POSITION_H_
#define SRC_POSITION_POSITION_H_

#include <cstddef>
#include <deque>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>

#include "movement/movement.h"

namespace application::object::position {

class ObjectPositionCalculator {
 public:
  explicit ObjectPositionCalculator(
      std::unique_ptr<application::object::movement::Movement> movement);

  void TrackObject(cv::Mat& mask, cv::Mat& hsv, cv::Mat& frame,
                   const cv::Scalar& lower_bound,
                   const cv::Scalar& upper_bound);

 private:
  double GetSmoothedPosition(double new_position);

  std::unique_ptr<application::object::movement::Movement> movement_;

  bool is_moving_ = false;
  bool has_previous_position_ = false;

  double previous_position_ = 0.0;
  double start_position_ = 0.0;
  double last_position_ = 0.0;

  double start_time_ = 0.0;
  double current_time_ = 0.0;
  double last_movement_time_ = 0.0;

  std::deque<double> position_buffer_;

  static constexpr std::size_t kBufferSize = 5;
  static constexpr double kMovementThreshold = 5.0;
  static constexpr double kStopTime = 2.0;
};

}  // namespace application::object::position

#endif  // SRC_POSITION_POSITION_H_

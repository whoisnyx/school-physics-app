#ifndef SRC_WINDOW_WINDOW_H_
#define SRC_WINDOW_WINDOW_H_

#include <memory>
#include <opencv2/opencv.hpp>

#include "position/position.h"

namespace application::window {
class CameraFrame {
 public:
  CameraFrame(
      cv::VideoCapture& camera,
      std::unique_ptr<application::object::position::ObjectPositionCalculator>
          position_calculator,
      const cv::Scalar& lower_bound, const cv::Scalar& upper_bound);
  void RunCameraLoop();

 private:
  cv::VideoCapture& camera_frame_;
  std::unique_ptr<application::object::position::ObjectPositionCalculator>
      position_calculator_;
  cv::Scalar lower_bound_;
  cv::Scalar upper_bound_;
};
}  // namespace application::window

#endif  // SRC_WINDOW_WINDOW_H_

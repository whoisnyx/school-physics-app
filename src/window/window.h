#ifndef SRC_WINDOW_WINDOW_H_
#define SRC_WINDOW_WINDOW_H_

#include <memory>
#include <opencv2/opencv.hpp>

#include "position/position.h"

// Namespace for window and video capture handling.
namespace application::window {

// Class responsible for capturing video frames and running the main display
// loop.
class CameraFrame {
 public:
  // Constructs CameraFrame with video capture stream, position calculator, and
  // color bounds.
  CameraFrame(
      cv::VideoCapture& camera,
      std::unique_ptr<application::object::position::ObjectPositionCalculator>
          position_calculator,
      const cv::Scalar& lower_bound, const cv::Scalar& upper_bound);

  // Runs the continuous video capture and tracking loop.
  void RunCameraLoop();

 private:
  cv::VideoCapture& camera_frame_;  // Reference to video capture device.
  std::unique_ptr<application::object::position::ObjectPositionCalculator>
      position_calculator_;  // Object position calculator.
  cv::Scalar lower_bound_;   // Lower HSV color threshold.
  cv::Scalar upper_bound_;   // Upper HSV color threshold.
};

}  // namespace application::window

#endif  // SRC_WINDOW_WINDOW_H_

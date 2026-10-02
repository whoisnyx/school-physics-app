// Copyright 2026 NUX.

#include "window/window.h"

#include <opencv2/opencv.hpp>

// Namespace for window and video capture handling.
namespace application::window {

// Initializes CameraFrame with capture stream, calculator, and bounds.
CameraFrame::CameraFrame(
    cv::VideoCapture& camera,
    std::unique_ptr<application::object::position::ObjectPositionCalculator>
        position_calculator,
    const cv::Scalar& lower_bound, const cv::Scalar& upper_bound)
    : camera_frame_(camera),
      position_calculator_(std::move(position_calculator)),
      lower_bound_(lower_bound),
      upper_bound_(upper_bound) {}

// Executes the main capture loop displaying frames and tracking objects.
void CameraFrame::RunCameraLoop() {
  cv::Mat frame;
  cv::Mat hsv;
  cv::Mat mask;

  while (true) {
    // Read next frame from camera.
    camera_frame_ >> frame;

    if (frame.empty()) {
      break;
    }

    // Process frame with position tracker if available.
    if (position_calculator_) {
      position_calculator_->TrackObject(mask, hsv, frame, lower_bound_,
                                        upper_bound_);
    }

    // Display the processed frame in a window.
    cv::imshow("Camera", frame);

    // Exit loop when 'q' key is pressed.
    if (cv::waitKey(10) == 'q') {
      break;
    }
  }
  // Close all OpenCV windows.
  cv::destroyAllWindows();
}

}  // namespace application::window

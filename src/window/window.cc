// Copyright 2026 NUX.

#include "window/window.h"

#include <opencv2/opencv.hpp>

#include "position/position.h"

namespace application::window {

void RunCameraLoop(cv::VideoCapture& camera) {
  // HSV thresholds to isolate the object of interest.
  cv::Scalar lower_bound(100, 150, 50);
  cv::Scalar upper_bound(140, 255, 255);
  application::window::object_position::PositionCalculator calculator;

  while (true) {
    cv::Mat camera_frame, hsv, mask;
    camera >> camera_frame;

    if (camera_frame.empty()) {
      break;
    }

    // Process the frame to detect motion and calculate kinematics.
    calculator.TrackObject(mask, hsv, camera_frame, lower_bound, upper_bound);

    cv::imshow("Camera", camera_frame);

    // Terminate loop on 'q' key press.
    if (cv::waitKey(10) == 'q') {
      break;
    }
  }
}

}  // namespace application::window

// Copyright 2026, NUX.

#include "window/window.h"

#include <opencv2/opencv.hpp>

#include "position/position.h"

namespace application::window {

void CameraRunning(cv::VideoCapture& object) {
  cv::Scalar lower_bound(100, 150, 50);
  cv::Scalar upper_bound(140, 255, 255);

  while (true) {
    // Connect object to frame.
    cv::Mat camera_frame, hsv, mask;
    object >> camera_frame;

    // Condition: if frame is empty, then we close it.
    if (camera_frame.empty()) {
      break;
    }

    // Find object and print position(x: number, y: number);
    application::window::object_position::PositionCalculating(
        mask, hsv, camera_frame, lower_bound, upper_bound);

    // Camera output.
    cv::imshow("Camera", camera_frame);

    // Closing frame key.
    if (cv::waitKey(10) == 'q') {
      break;
    }
  }
}
}  // namespace application::window

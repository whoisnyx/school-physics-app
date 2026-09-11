// Copyright 2026, NUX.

#include <opencv2/opencv.hpp>

#include "window/window.h"

int main() {
  // Get camera live-video.
  cv::VideoCapture camera_object(0);
  application::window::CameraRunning(camera_object);

  // Closing frame.
  camera_object.release();
  cv::destroyAllWindows();

  return 0;
}

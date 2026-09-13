// Copyright 2026 NUX.

#include <opencv2/opencv.hpp>

#include "window/window.h"

int main() {
  // Initialize camera capture and start the processing loop.
  cv::VideoCapture camera(0);
  application::window::RunCameraLoop(camera);

  camera.release();
  cv::destroyAllWindows();

  return 0;
}

// Copyright 2026 NUX.

#ifndef SRC_WINDOW_WINDOW_H_
#define SRC_WINDOW_WINDOW_H_

#include <opencv2/opencv.hpp>

namespace application::window {

// Runs the main camera procesing loop, handling frame acquisition
// and object tracking.
void RunCameraLoop(cv::VideoCapture& camera);

}  // namespace application::window

#endif  // SRC_WINDOW_WINDOW_H_

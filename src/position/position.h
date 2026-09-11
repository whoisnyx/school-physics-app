// Copyright 2026, NUX

#include <opencv2/opencv.hpp>

#ifndef SRC_POSITION_POSITION_H_
#define SRC_POSITION_POSITION_H_

namespace application::window::object_position {

void PositionCalculating(cv::Mat& mask, cv::Mat& hsv, cv::Mat& frame,
                         const cv::Scalar& lower_bound,
                         const cv::Scalar& upper_bound);

}
#endif  // SRC_POSITION_POSITION_H_

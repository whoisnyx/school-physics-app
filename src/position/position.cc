// Copyright 2026, NUX.

#include "position/position.h"

#include <opencv2/opencv.hpp>
#include <vector>

namespace application::window::object_position {

void PositionCalculating(cv::Mat& mask, cv::Mat& hsv, cv::Mat& frame,
                         const cv::Scalar& lower_bound,
                         const cv::Scalar& upper_bound) {
  // Find color.
  cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
  cv::inRange(hsv, lower_bound, upper_bound, mask);

  // Find contours.
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  if (!contours.empty()) {
    auto largest_contour = std::max_element(
        contours.begin(), contours.end(),
        [](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b) {
          return cv::contourArea(a) < cv::contourArea(b);
        });

    if (cv::contourArea(*largest_contour) > 500) {
      cv::Moments m = cv::moments(*largest_contour);
      int x = static_cast<int>(m.m10 / m.m00);
      int y = static_cast<int>(m.m01 / m.m00);

      cv::circle(frame, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);
      std::string coords =
          "x: " + std::to_string(x) + " y: " + std::to_string(y);
      cv::putText(frame, coords, cv::Point(x + 15, y), cv::FONT_HERSHEY_SIMPLEX,
                  0.6, cv::Scalar(255, 255, 255), 2);
    }
  }
}

}  // namespace application::window::object_position

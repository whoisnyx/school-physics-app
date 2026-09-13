// Copyright 2026 NUX.

#include "position/position.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

namespace application::window::object_position {

void PositionCalculator::TrackObject(cv::Mat& mask, cv::Mat& hsv,
                                     cv::Mat& frame,
                                     const cv::Scalar& lower_bound,
                                     const cv::Scalar& upper_bound) {
  // Isolate the object using color thresholding in HSV color space.
  cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
  cv::inRange(hsv, lower_bound, upper_bound, mask);

  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  if (!contours.empty()) {
    // Select the largest contour to ensure we track the intended object,
    // assuming it occupies the most space.
    auto largest_contour = std::max_element(
        contours.begin(), contours.end(),
        [](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b) {
          return cv::contourArea(a) < cv::contourArea(b);
        });

    if (cv::contourArea(*largest_contour) > 500) {
      cv::Moments m = cv::moments(*largest_contour);

      if (m.m00 != 0) {
        int x = static_cast<int>(m.m10 / m.m00);
        int y = static_cast<int>(m.m01 / m.m00);

        double current_position = static_cast<double>(x);
        double current_time =
            static_cast<double>(cv::getTickCount()) / cv::getTickFrequency();

        if (has_previous_position_) {
          double delta = std::abs(current_position - previous_position_);

          // Detect movement initiation if displacement exceeds the noise
          // threshold.
          if (delta > movement_threshold_ && !is_moving_) {
            is_moving_ = true;
            start_position_ = current_position;
            last_position_ = current_position;
            start_time_ = current_time;
            last_movement_time_ = current_time;

            std::cout << "Movement started" << std::endl;
          }

          // Update state if movement persists.
          if (is_moving_ && delta > movement_threshold_) {
            last_position_ = current_position;
            last_movement_time_ = current_time;
          }

          // Compute kinematics only after the object is detected as stopped.
          if (is_moving_ && current_time - last_movement_time_ > stop_time_) {
            double distance = std::abs(last_position_ - start_position_);
            double time = last_movement_time_ - start_time_;

            if (time > 0.0) {
              double velocity = distance / time;
              // Assuming constant acceleration from rest: s = 0.5 * a * t^2.
              double acceleration = 2.0 * distance / (time * time);

              std::cout << "S = " << distance << " px" << std::endl;
              std::cout << "T = " << time << " s" << std::endl;
              std::cout << "v = " << velocity << " px/s" << std::endl;
              std::cout << "a = " << acceleration << " px/s^2" << std::endl;
            }

            is_moving_ = false;
          }
        }

        previous_position_ = current_position;
        has_previous_position_ = true;

        // Visual feedback on the frame.
        cv::circle(frame, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);
        std::string coords =
            "x: " + std::to_string(x) + " y: " + std::to_string(y);
        cv::putText(frame, coords, cv::Point(x + 15, y),
                    cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255),
                    2);
      }
    }
  }
}

}  // namespace application::window::object_position

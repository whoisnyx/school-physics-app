// Copyright 2026 NUX.

#include "position/position.h"

#include <iostream>
#include <numeric>
#include <opencv2/opencv.hpp>
#include <vector>

namespace application::window::object_position {

double PositionCalculator::GetSmoothedPosition(double new_position) {
  position_buffer_.push_back(new_position);
  if (position_buffer_.size() > buffer_size_) {
    position_buffer_.pop_front();
  }
  return std::accumulate(position_buffer_.begin(), position_buffer_.end(),
                         0.0) /
         position_buffer_.size();
}

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

        // Use y-coordinate for vertical movement, x for horizontal
        double raw_position =
            (controller_.GetType() == application::window::object_position::
                                          movement::MovementType::Vertical)
                ? static_cast<double>(y)
                : static_cast<double>(x);

        double current_position = GetSmoothedPosition(raw_position);

        double current_time =
            static_cast<double>(cv::getTickCount()) / cv::getTickFrequency();

        if (has_previous_position_) {
          double delta = std::abs(current_position - previous_position_);

          // Detect movement initiation
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

          // Compute kinematics. Increased stop_time_ to 2.0 to account for
          // bounces.
          const double active_stop_time =
              (controller_.GetType() == application::window::object_position::
                                            movement::MovementType::Vertical)
                  ? 2.0
                  : stop_time_;
          if (is_moving_ &&
              current_time - last_movement_time_ > active_stop_time) {
            double distance = std::abs(last_position_ - start_position_);
            double time = last_movement_time_ - start_time_;

            if (time > 0.0) {
              auto kinematics = controller_.Calculate(distance, time);

              std::cout << "S = " << distance << " px" << std::endl;
              std::cout << "T = " << time << " s" << std::endl;
              std::cout << "v = " << kinematics.velocity << " px/s"
                        << std::endl;
              std::cout << kinematics.accel_name << " = "
                        << kinematics.acceleration << " px/s^2" << std::endl;
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

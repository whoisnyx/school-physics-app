// Copyright 2026 NUX.

#include "position/position.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

// Namespace for object position tracking and analysis.
namespace application::object::position {

// Initializes ObjectPositionCalculator with movement strategy.
ObjectPositionCalculator::ObjectPositionCalculator(
    std::unique_ptr<application::object::movement::Movement> movement)
    : movement_(std::move(movement)) {}

// Smooths raw position input using a moving average buffer.
double ObjectPositionCalculator::GetSmoothedPosition(double new_position) {
  position_buffer_.push_back(new_position);

  if (position_buffer_.size() > kBufferSize) {
    position_buffer_.pop_front();
  }

  double sum = 0.0;

  for (double position : position_buffer_) {
    sum += position;
  }

  return sum / position_buffer_.size();
}

// Tracks the object in the current video frame and computes movement metrics.
void ObjectPositionCalculator::TrackObject(cv::Mat& mask, cv::Mat& hsv,
                                           cv::Mat& frame,
                                           const cv::Scalar& lower_bound,
                                           const cv::Scalar& upper_bound) {
  // Convert frame to HSV color space.
  cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
  // Threshold image to isolate color mask.
  cv::inRange(hsv, lower_bound, upper_bound, mask);

  std::vector<std::vector<cv::Point>> contours;

  // Find contours in the masked image.
  cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  if (contours.empty()) {
    return;
  }

  // Find the largest contour by area.
  auto largest_contour = std::max_element(
      contours.begin(), contours.end(),
      [](const std::vector<cv::Point>& first,
         const std::vector<cv::Point>& second) {
        return cv::contourArea(first) < cv::contourArea(second);
      });

  // Ignore small contours to filter out noise.
  if (cv::contourArea(*largest_contour) <= 500) {
    return;
  }

  // Calculate image moments to find centroid.
  cv::Moments moments = cv::moments(*largest_contour);

  if (moments.m00 == 0) {
    return;
  }

  // Compute centroid coordinates.
  const int x = static_cast<int>(moments.m10 / moments.m00);
  const int y = static_cast<int>(moments.m01 / moments.m00);

  double raw_position;

  // Determine coordinate axis based on movement type.
  if (movement_->GetMovementType() ==
      application::object::movement::MovementType::kVertical) {
    raw_position = static_cast<double>(y);
  } else {
    raw_position = static_cast<double>(x);
  }

  // Smooth position reading.
  const double current_position = GetSmoothedPosition(raw_position);

  // Get current timestamp in seconds.
  const double current_time =
      static_cast<double>(cv::getTickCount()) / cv::getTickFrequency();

  if (has_previous_position_) {
    const double delta = std::abs(current_position - previous_position_);

    // Detect when object starts moving.
    if (delta > kMovementThreshold && !is_moving_) {
      is_moving_ = true;

      start_position_ = current_position;
      last_position_ = current_position;

      start_time_ = current_time;
      last_movement_time_ = current_time;

      std::cout << "Movement started\n";
    }

    // Update position while object is moving.
    if (is_moving_ && delta > kMovementThreshold) {
      last_position_ = current_position;
      last_movement_time_ = current_time;
    }

    // Detect when object stops moving.
    if (is_moving_ && current_time - last_movement_time_ > kStopTime) {
      const double distance = std::abs(last_position_ - start_position_);

      const double time = last_movement_time_ - start_time_;

      if (time > 0.0) {
        // Calculate physics parameters.
        const auto result = movement_->Calculating(distance, time);

        std::cout << "S = " << distance << " px\n";

        std::cout << "t = " << time << " s\n";

        std::cout << "v = " << result.velocity << " px/s\n";

        std::cout << result.accel_name << " = " << result.acceleration
                  << " px/s^2\n";
      }

      is_moving_ = false;
    }
  }

  previous_position_ = current_position;
  has_previous_position_ = true;

  // Draw tracking circle on frame.
  cv::circle(frame, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);

  const std::string coordinates =
      "x: " + std::to_string(x) + " y: " + std::to_string(y);

  // Display coordinates on frame.
  cv::putText(frame, coordinates, cv::Point(x + 15, y),
              cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
}

}  // namespace application::object::position

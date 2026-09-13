// Copyright 2026 NUX.

#include <gtest/gtest.h>

#include <opencv2/opencv.hpp>

#include "position/position.h"

namespace application::window::object_position::tests {

TEST(PositionCalculatorTest, BasicInitialization) {
  application::window::object_position::PositionCalculator calculator;
  // We expect the calculator to be initialized without issues.
  SUCCEED();
}

TEST(PositionCalculatorTest, TrackObjectWithValidFrame) {
  application::window::object_position::PositionCalculator calculator;
  cv::Mat mask, hsv, frame = cv::Mat::zeros(100, 100, CV_8UC3);
  cv::Scalar lower_bound(0, 0, 0);
  cv::Scalar upper_bound(255, 255, 255);

  // Should not throw and should execute successfully with a valid frame
  EXPECT_NO_THROW(
      calculator.TrackObject(mask, hsv, frame, lower_bound, upper_bound));
}
}  // namespace application::window::object_position::tests

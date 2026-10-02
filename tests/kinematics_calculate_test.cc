#include <gtest/gtest.h>
#include "kinematics/kinematics.h"

// Test horizontal kinematics calculation correctness.
TEST(KinematicsTest, HorizontalCalculation) {
  application::object::kinematics::Kinematics kinematics;
  auto result = kinematics.HorizontalCalculating(100.0, 2.0);
  EXPECT_DOUBLE_EQ(result.velocity, 50.0);
  EXPECT_DOUBLE_EQ(result.acceleration, 50.0);
  EXPECT_EQ(result.accel_name, "Acceleration");
}

// Test vertical kinematics calculation correctness.
TEST(KinematicsTest, VerticalCalculation) {
  application::object::kinematics::Kinematics kinematics;
  auto result = kinematics.VerticalCalculating(200.0, 4.0);
  EXPECT_DOUBLE_EQ(result.velocity, 50.0);
  EXPECT_DOUBLE_EQ(result.acceleration, 25.0);
  EXPECT_EQ(result.accel_name, "Gravity");
}

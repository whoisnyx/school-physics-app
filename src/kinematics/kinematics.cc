#include "kinematics/kinematics.h"

// Namespace for physics kinematics calculations.
namespace application::object::kinematics {

// Computes velocity and acceleration for horizontal movement.
KinematicsResult Kinematics::HorizontalCalculating(double distance,
                                                   double time) {
  double velocity = time > 0.0 ? distance / time : 0.0;
  double acceleration = time > 0.0 ? (2.0 * distance) / (time * time) : 0.0;
  return {velocity, acceleration, "Acceleration"};
}

// Computes velocity and acceleration for vertical movement.
KinematicsResult Kinematics::VerticalCalculating(double distance, double time) {
  double velocity = time > 0.0 ? distance / time : 0.0;
  double acceleration = time > 0.0 ? (2.0 * distance) / (time * time) : 0.0;
  return {velocity, acceleration, "Gravity"};
}

}  // namespace application::object::kinematics

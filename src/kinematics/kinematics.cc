#include "kinematics/kinematics.h"

namespace application::object::kinematics {

KinematicsResult Kinematics::HorizontalCalculating(double distance,
                                                   double time) {
  double velocity = time > 0.0 ? distance / time : 0.0;
  double acceleration = time > 0.0 ? (2.0 * distance) / (time * time) : 0.0;
  return {velocity, acceleration, "Acceleration"};
}

KinematicsResult Kinematics::VerticalCalculating(double distance, double time) {
  double velocity = time > 0.0 ? distance / time : 0.0;
  double acceleration = time > 0.0 ? (2.0 * distance) / (time * time) : 0.0;
  return {velocity, acceleration, "Gravity"};
}

}  // namespace application::object::kinematics

// Copyright 2026 NUX.

#ifndef SRC_KINEMATICS_KINEMATICS_H_
#define SRC_KINEMATICS_KINEMATICS_H_

#include <string>

// Namespace for physics kinematics calculations.
namespace application::object::kinematics {

// Structure holding calculated physics results.
struct KinematicsResult {
  double velocity;         // Calculated velocity magnitude.
  double acceleration;     // Calculated acceleration magnitude.
  std::string accel_name;  // Descriptive name of the acceleration type.
};

// Class responsible for performing kinematic calculations.
class Kinematics {
 public:
  // Calculates kinematics for horizontal motion given distance and time.
  KinematicsResult HorizontalCalculating(double distance, double time);

  // Calculates kinematics for vertical motion given distance and time.
  KinematicsResult VerticalCalculating(double distance, double time);
};

}  // namespace application::object::kinematics

#endif  // SRC_KINEMATICS_KINEMATICS_H_

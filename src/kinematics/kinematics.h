#ifndef SRC_KINEMATICS_KINEMATICS_H_
#define SRC_KINEMATICS_KINEMATICS_H_

#include <string>

namespace application::object::kinematics {

struct KinematicsResult {
  double velocity;
  double acceleration;
  std::string accel_name;
};

class Kinematics {
 public:
  KinematicsResult HorizontalCalculating(double distance, double time);

  KinematicsResult VerticalCalculating(double distance, double time);
};

}  // namespace application::object::kinematics

#endif  // SRC_KINEMATICS_KINEMATICS_H_

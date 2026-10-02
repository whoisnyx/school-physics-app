// Copyright 2026 NUX.

#ifndef SRC_MOVEMENT_MOVEMENT_H_
#define SRC_MOVEMENT_MOVEMENT_H_

#include "kinematics/kinematics.h"

namespace application::object::movement {

enum class MovementType { kHorizontal, kVertical };

class Movement {
 public:
  Movement(MovementType movement_type,
           application::object::kinematics::Kinematics& kinematics);

  virtual ~Movement() = default;

  virtual application::object::kinematics::KinematicsResult Calculating(
      double distance, double time) = 0;

  MovementType GetMovementType() const;

 protected:
  MovementType movement_type_;
  application::object::kinematics::Kinematics& kinematics_;
};

class HorizontalMovement : public Movement {
 public:
  explicit HorizontalMovement(
      application::object::kinematics::Kinematics& kinematics);

  application::object::kinematics::KinematicsResult Calculating(
      double distance, double time) override;
};

class VerticalMovement : public Movement {
 public:
  explicit VerticalMovement(
      application::object::kinematics::Kinematics& kinematics);

  application::object::kinematics::KinematicsResult Calculating(
      double distance, double time) override;
};

}  // namespace application::object::movement

#endif  // SRC_MOVEMENT_MOVEMENT_H_

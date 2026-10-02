// Copyright 2026 NUX.

#include "movement/movement.h"

namespace application::object::movement {

Movement::Movement(MovementType movement_type,
                   application::object::kinematics::Kinematics& kinematics)
    : movement_type_(movement_type), kinematics_(kinematics) {}

MovementType Movement::GetMovementType() const { return movement_type_; }

HorizontalMovement::HorizontalMovement(
    application::object::kinematics::Kinematics& kinematics)
    : Movement(MovementType::kHorizontal, kinematics) {}

application::object::kinematics::KinematicsResult
HorizontalMovement::Calculating(double distance, double time) {
  return kinematics_.HorizontalCalculating(distance, time);
}

VerticalMovement::VerticalMovement(
    application::object::kinematics::Kinematics& kinematics)
    : Movement(MovementType::kVertical, kinematics) {}

application::object::kinematics::KinematicsResult VerticalMovement::Calculating(
    double distance, double time) {
  return kinematics_.VerticalCalculating(distance, time);
}

}  // namespace application::object::movement

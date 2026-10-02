// Copyright 2026 NUX.

#include "movement/movement.h"

// Namespace for object movement tracking and classification.
namespace application::object::movement {

// Initializes movement base properties.
Movement::Movement(MovementType movement_type,
                   application::object::kinematics::Kinematics& kinematics)
    : movement_type_(movement_type), kinematics_(kinematics) {}

// Returns the movement type.
MovementType Movement::GetMovementType() const { return movement_type_; }

// Initializes horizontal movement.
HorizontalMovement::HorizontalMovement(
    application::object::kinematics::Kinematics& kinematics)
    : Movement(MovementType::kHorizontal, kinematics) {}

// Performs horizontal calculation via kinematics.
application::object::kinematics::KinematicsResult
HorizontalMovement::Calculating(double distance, double time) {
  return kinematics_.HorizontalCalculating(distance, time);
}

// Initializes vertical movement.
VerticalMovement::VerticalMovement(
    application::object::kinematics::Kinematics& kinematics)
    : Movement(MovementType::kVertical, kinematics) {}

// Performs vertical calculation via kinematics.
application::object::kinematics::KinematicsResult VerticalMovement::Calculating(
    double distance, double time) {
  return kinematics_.VerticalCalculating(distance, time);
}

}  // namespace application::object::movement

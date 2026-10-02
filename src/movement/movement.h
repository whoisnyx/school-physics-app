// Copyright 2026 NUX.

#ifndef SRC_MOVEMENT_MOVEMENT_H_
#define SRC_MOVEMENT_MOVEMENT_H_

#include "kinematics/kinematics.h"

// Namespace for object movement tracking and classification.
namespace application::object::movement {

// Enum defining supported movement directions.
enum class MovementType { kHorizontal, kVertical };

// Abstract base class representing object movement.
class Movement {
 public:
  // Constructs a Movement instance with a given type and kinematics calculator.
  Movement(MovementType movement_type,
           application::object::kinematics::Kinematics& kinematics);

  // Virtual destructor for polymorphic cleanup.
  virtual ~Movement() = default;

  // Pure virtual function to calculate movement physics.
  virtual application::object::kinematics::KinematicsResult Calculating(
      double distance, double time) = 0;

  // Returns the movement type (horizontal or vertical).
  MovementType GetMovementType() const;

 protected:
  MovementType movement_type_;  // Type of movement.
  application::object::kinematics::Kinematics&
      kinematics_;  // Kinematics reference.
};

// Class handling horizontal movement calculations.
class HorizontalMovement : public Movement {
 public:
  // Constructs a HorizontalMovement with kinematics reference.
  explicit HorizontalMovement(
      application::object::kinematics::Kinematics& kinematics);

  // Overrides Calculating for horizontal motion.
  application::object::kinematics::KinematicsResult Calculating(
      double distance, double time) override;
};

// Class handling vertical movement calculations.
class VerticalMovement : public Movement {
 public:
  // Constructs a VerticalMovement with kinematics reference.
  explicit VerticalMovement(
      application::object::kinematics::Kinematics& kinematics);

  // Overrides Calculating for vertical motion.
  application::object::kinematics::KinematicsResult Calculating(
      double distance, double time) override;
};

}  // namespace application::object::movement

#endif  // SRC_MOVEMENT_MOVEMENT_H_

// Copyright 2026 NUX.

#include "movement/movement.h"

namespace application::window::object_position::movement {

Kinematics MovementController::Calculate(double distance, double time) const {
  if (time <= 0.0) {
    return {0.0, 0.0, "a"};
  }

  double velocity = distance / time;

  if (type_ == MovementType::Horizontal) {
    // Assuming constant acceleration from rest: s = 0.5 * a * t^2.
    double acceleration = 2.0 * distance / (time * time);
    return {velocity, acceleration, "a"};
  } else {
    // Vertical movement: calculate g based on observed distance and time.
    double g = 2.0 * distance / (time * time);
    return {velocity, g, "g"};
  }
}

}  // namespace application::window::object_position::movement

// Copyright 2026 NUX

#ifndef SRC_MOVEMENT_MOVEMENT_H_
#define SRC_MOVEMENT_MOVEMENT_H_

#include <string>

namespace application::window::object_position::movement {

enum class MovementType { kHorizontal, kVertical };

struct Kinematics {
  double velocity;
  double acceleration;  // In horizontal, 'a'. In vertical, 'g'.
  std::string accel_name;
};

class MovementController {
 public:
  explicit MovementController(MovementType type) : type_(type) {}

  void SetType(MovementType type) { type_ = type; }
  MovementType GetType() const { return type_; }

  Kinematics Calculate(double distance, double time) const;

 private:
  MovementType type_;
};

}  // namespace application::window::object_position::movement

#endif  // SRC_MOVEMENT_MOVEMENT_H_

// Copyright 2026 NUX.

#include <algorithm>
#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>

#include "colors/colors.h"
#include "kinematics/kinematics.h"
#include "movement/movement.h"
#include "position/position.h"
#include "window/window.h"

// Entry point of the school physics project application.
int main() {
  std::unique_ptr<application::object::color::Color> color;

  std::string hue_input;
  // Prompt user to select object color.
  std::cout
      << "Enter color (possible values | green, blue, yellow, red, pink): ";
  std::cin >> hue_input;

  // Convert input to lowercase for case-insensitive comparison.
  std::transform(hue_input.begin(), hue_input.end(), hue_input.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  // Instantiate corresponding color object based on user input.
  if (hue_input == "blue") {
    color = std::make_unique<application::object::color::Blue>();
  } else if (hue_input == "green") {
    color = std::make_unique<application::object::color::Green>();
  } else if (hue_input == "red") {
    color = std::make_unique<application::object::color::Red>();
  } else if (hue_input == "pink") {
    color = std::make_unique<application::object::color::Pink>();
  } else if (hue_input == "yellow") {
    color = std::make_unique<application::object::color::Yellow>();
  } else {
    std::cerr << "Unknown color\n";
    return 1;
  }

  std::string movement_input;
  // Prompt user to select movement type.
  std::cout << "Enter movement type (horizontal, vertical): ";
  std::cin >> movement_input;

  // Convert movement input to lowercase.
  std::transform(movement_input.begin(), movement_input.end(),
                 movement_input.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  auto kinematics =
      std::make_unique<application::object::kinematics::Kinematics>();
  std::unique_ptr<application::object::movement::Movement> movement;

  // Instantiate movement strategy based on user selection.
  if (movement_input == "horizontal") {
    movement =
        std::make_unique<application::object::movement::HorizontalMovement>(
            *kinematics);
  } else if (movement_input == "vertical") {
    movement =
        std::make_unique<application::object::movement::VerticalMovement>(
            *kinematics);
  } else {
    std::cerr << "Unknown movement type\n";
    return 1;
  }

  // Create position calculator with movement strategy.
  auto position_calculator =
      std::make_unique<application::object::position::ObjectPositionCalculator>(
          std::move(movement));

  std::cout << "Selected color: " << color->GetHue() << '\n';
  cv::Scalar lower = color->GetLowerBound();
  cv::Scalar upper = color->GetUpperBound();

  // Initialize video capture from default camera.
  cv::VideoCapture camera(0);

  if (!camera.isOpened()) {
    std::cerr << "Failed to open camera!\n";
    return 1;
  }

  // Initialize and run camera window loop.
  application::window::CameraFrame camera_frame(
      camera, std::move(position_calculator), lower, upper);
  camera_frame.RunCameraLoop();

  return 0;
}

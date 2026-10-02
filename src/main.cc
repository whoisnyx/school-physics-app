#include <algorithm>
#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>

#include "colors/colors.h"
#include "kinematics/kinematics.h"
#include "movement/movement.h"
#include "position/position.h"
#include "window/window.h"

int main() {
  std::unique_ptr<application::object::color::Color> color;

  std::string hue_input;
  std::cout
      << "Enter color (possible values | green, blue, yellow, red, pink): ";
  std::cin >> hue_input;

  std::transform(hue_input.begin(), hue_input.end(), hue_input.begin(),
                 [](unsigned char c) { return std::tolower(c); });

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
  std::cout << "Enter movement type (horizontal, vertical): ";
  std::cin >> movement_input;

  std::transform(movement_input.begin(), movement_input.end(),
                 movement_input.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  auto kinematics =
      std::make_unique<application::object::kinematics::Kinematics>();
  std::unique_ptr<application::object::movement::Movement> movement;

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

  auto position_calculator =
      std::make_unique<application::object::position::ObjectPositionCalculator>(
          std::move(movement));

  std::cout << "Selected color: " << color->GetHue() << '\n';
  cv::Scalar lower = color->GetLowerBound();
  cv::Scalar upper = color->GetUpperBound();

  cv::VideoCapture camera(0);

  if (!camera.isOpened()) {
    std::cerr << "Failed to open camera!\n";
    return 1;
  }

  application::window::CameraFrame camera_frame(
      camera, std::move(position_calculator), lower, upper);
  camera_frame.RunCameraLoop();

  return 0;
}

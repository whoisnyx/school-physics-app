// Copyright 2026 NUX.

#include "colors/colors.h"

#include <string>

// Namespace for application color definitions.
namespace application::object::color {

// Initializes color properties with hue name and HSV thresholds.
Color::Color(const std::string& hue, const cv::Scalar& lower_bound,
             const cv::Scalar& upper_bound)
    : hue_(hue), lower_bound_(lower_bound), upper_bound_(upper_bound) {}

// Returns the color hue name.
const std::string& Color::GetHue() const { return hue_; }

// Returns the lower HSV boundary scalar.
const cv::Scalar& Color::GetLowerBound() const { return lower_bound_; }

// Returns the upper HSV boundary scalar.
const cv::Scalar& Color::GetUpperBound() const { return upper_bound_; }

// Configures Blue color HSV thresholds.
Blue::Blue()
    : Color("Blue", cv::Scalar(100, 150, 50), cv::Scalar(140, 255, 255)) {}

// Configures Green color HSV thresholds.
Green::Green()
    : Color("Green", cv::Scalar(40, 50, 50), cv::Scalar(80, 255, 255)) {}

// Configures Red color HSV thresholds.
Red::Red() : Color("Red", cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255)) {}

// Configures Pink color HSV thresholds.
Pink::Pink()
    : Color("Pink", cv::Scalar(140, 50, 50), cv::Scalar(170, 255, 255)) {}

// Configures Yellow color HSV thresholds.
Yellow::Yellow()
    : Color("Yellow", cv::Scalar(20, 100, 100), cv::Scalar(40, 255, 255)) {}

}  // namespace application::object::color

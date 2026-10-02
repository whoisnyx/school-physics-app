#include "colors/colors.h"

#include <string>

namespace application::object::color {

Color::Color(const std::string& hue, const cv::Scalar& lower_bound,
             const cv::Scalar& upper_bound)
    : hue_(hue), lower_bound_(lower_bound), upper_bound_(upper_bound) {}

const std::string& Color::GetHue() const { return hue_; }

const cv::Scalar& Color::GetLowerBound() const { return lower_bound_; }

const cv::Scalar& Color::GetUpperBound() const { return upper_bound_; }

Blue::Blue()
    : Color("Blue", cv::Scalar(100, 150, 50), cv::Scalar(140, 255, 255)) {}

Green::Green()
    : Color("Green", cv::Scalar(40, 50, 50), cv::Scalar(80, 255, 255)) {}

Red::Red() : Color("Red", cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255)) {}

Pink::Pink()
    : Color("Pink", cv::Scalar(140, 50, 50), cv::Scalar(170, 255, 255)) {}

Yellow::Yellow()
    : Color("Yellow", cv::Scalar(20, 100, 100), cv::Scalar(40, 255, 255)) {}
}  // namespace application::object::color

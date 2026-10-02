// Copyright 2026 NUX.

#ifndef SRC_COLORS_COLORS_H_
#define SRC_COLORS_COLORS_H_

#include <opencv2/opencv.hpp>
#include <string>

// Namespace for application color definitions.
namespace application::object::color {

// Base class representing color properties for object detection.
class Color {
 public:
  // Constructs a Color with a given hue name, lower bound, and upper bound.
  Color(const std::string& hue, const cv::Scalar& lower_bound,
        const cv::Scalar& upper_bound);

  // Virtual destructor for safe polymorphic cleanup.
  virtual ~Color() = default;

  // Returns the string name of the color hue.
  const std::string& GetHue() const;

  // Returns the lower bound scalar in HSV space.
  const cv::Scalar& GetLowerBound() const;

  // Returns the upper bound scalar in HSV space.
  const cv::Scalar& GetUpperBound() const;

 protected:
  std::string hue_;               // Name of the color hue.
  const cv::Scalar lower_bound_;  // Lower HSV boundary.
  const cv::Scalar upper_bound_;  // Upper HSV boundary.
};

// Represents blue color configuration.
class Blue : public Color {
 public:
  Blue();
};

// Represents green color configuration.
class Green : public Color {
 public:
  Green();
};

// Represents red color configuration.
class Red : public Color {
 public:
  Red();
};

// Represents pink color configuration.
class Pink : public Color {
 public:
  Pink();
};

// Represents yellow color configuration.
class Yellow : public Color {
 public:
  Yellow();
};

}  // namespace application::object::color

#endif  // SRC_COLORS_COLORS_H_

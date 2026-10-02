#ifndef SRC_COLORS_COLORS_H_
#define SRC_COLORS_COLORS_H_

#include <opencv2/opencv.hpp>

namespace application::object::color {

class Color {
 public:
  Color(const std::string& hue, const cv::Scalar& lower_bound,
        const cv::Scalar& upper_bound);

  virtual ~Color() = default;

  const std::string& GetHue() const;
  const cv::Scalar& GetLowerBound() const;
  const cv::Scalar& GetUpperBound() const;

 protected:
  std::string hue_;
  const cv::Scalar lower_bound_;
  const cv::Scalar upper_bound_;
};

class Blue : public Color {
 public:
  Blue();
};

class Green : public Color {
 public:
  Green();
};

class Red : public Color {
 public:
  Red();
};

class Pink : public Color {
 public:
  Pink();
};

class Yellow : public Color {
 public:
  Yellow();
};

}  // namespace application::object::color

#endif  // SRC_COLORS_COLORS_H_

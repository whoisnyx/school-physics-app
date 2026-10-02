#include "window/window.h"

#include <opencv2/opencv.hpp>

namespace application::window {

CameraFrame::CameraFrame(
    cv::VideoCapture& camera,
    std::unique_ptr<application::object::position::ObjectPositionCalculator>
        position_calculator,
    const cv::Scalar& lower_bound, const cv::Scalar& upper_bound)
    : camera_frame_(camera),
      position_calculator_(std::move(position_calculator)),
      lower_bound_(lower_bound),
      upper_bound_(upper_bound) {}

void CameraFrame::RunCameraLoop() {
  cv::Mat frame;
  cv::Mat hsv;
  cv::Mat mask;

  while (true) {
    camera_frame_ >> frame;

    if (frame.empty()) {
      break;
    }

    if (position_calculator_) {
      position_calculator_->TrackObject(mask, hsv, frame, lower_bound_,
                                        upper_bound_);
    }

    cv::imshow("Camera", frame);

    if (cv::waitKey(10) == 'q') {
      break;
    }
  }
  cv::destroyAllWindows();
}

}  // namespace application::window

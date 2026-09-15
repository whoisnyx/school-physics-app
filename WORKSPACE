workspace(name = "school-physics-app")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_cc",
    sha256 = "6571583d987a0b355886d34e9e04812f86ba52f75877f1e7d022c4a96b99446d",
    urls = ["https://github.com/bazelbuild/rules_cc/releases/download/0.0.17/rules_cc-0.0.17.tar.gz"],
)

# System GTK 3, used to enable the GTK highgui backend of the Bazel
# OpenCV build (cv::imshow etc.).
new_local_repository(
    name = "gtk3",
    path = "/usr",
    build_file = "//third_party/gtk3:BUILD",
)

# Google Test
http_archive(
    name = "com_google_googletest",
    sha256 = "8c253816223403a45c361952a26569107936a29f8a3ab75d81f21575882b0126",  # Update to a stable version
    strip_prefix = "googletest-1.15.2",
    urls = ["https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz"],
)

new_local_repository(
    name = "opencv_local",
    path = "/usr/local", # Adjust path as necessary
    build_file_content = """
cc_library(
    name = "opencv",
    srcs = glob(["lib/libopencv_*.so"]),
    hdrs = glob(["include/opencv5/**/*.h"]),
    includes = ["include/opencv5"],
    visibility = ["//visibility:public"],
    linkopts = ["-lopencv_highgui", "-lopencv_core", "-lopencv_imgcodecs", "-lopencv_imgproc"],
)
""",
)

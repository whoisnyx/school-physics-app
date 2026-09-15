load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_library(
    name = "logic_lib",
    visibility = ["//visibility:public"],
    srcs = [
        "window/window.cc",
        "position/position.cc",
    ],
    hdrs = [
        "window/window.h",
        "position/position.h",
    ],
    strip_include_prefix = ".",
    copts = ["-std=c++20", "-Wall", "-Wextra"],
    deps = ["@opencv_local//:opencv"],
)

cc_binary(
    name = "CVTest",
    srcs = ["main.cc"],
    copts = ["-std=c++20", "-Wall", "-Wextra"],
    deps = [":logic_lib"],
)

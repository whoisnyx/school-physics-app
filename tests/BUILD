load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_tests",
    srcs = ["position_calculator_test.cc"],
    copts = ["-std=c++20"],
    deps = [
        "//src:logic_lib",
        "@googletest//:gtest_main",
    ],
)

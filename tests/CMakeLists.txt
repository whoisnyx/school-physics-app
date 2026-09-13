find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(unit_tests position_calculator_test.cc)

target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(unit_tests PRIVATE GTest::gtest_main logic_lib)

gtest_discover_tests(unit_tests)

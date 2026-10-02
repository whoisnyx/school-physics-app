find_package(GTest CONFIG REQUIRED)

add_executable(unit_tests kinematics_calculate_test.cc)

target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(unit_tests PRIVATE GTest::gtest_main app)

add_test(NAME UnitTests COMMAND unit_tests)

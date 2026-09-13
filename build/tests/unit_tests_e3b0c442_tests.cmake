add_test([=[PositionCalculatorTest.BasicInitialization]=]  /home/nux/Developer/study/cpp/school-physics-app/build/tests/unit_tests [==[--gtest_filter=PositionCalculatorTest.BasicInitialization]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PositionCalculatorTest.BasicInitialization]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/nux/Developer/study/cpp/school-physics-app/tests/position_calculator_test.cc:11]==]
    WORKING_DIRECTORY [==[/home/nux/Developer/study/cpp/school-physics-app/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PositionCalculatorTest.TrackObjectWithValidFrame]=]  /home/nux/Developer/study/cpp/school-physics-app/build/tests/unit_tests [==[--gtest_filter=PositionCalculatorTest.TrackObjectWithValidFrame]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PositionCalculatorTest.TrackObjectWithValidFrame]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/nux/Developer/study/cpp/school-physics-app/tests/position_calculator_test.cc:17]==]
    WORKING_DIRECTORY [==[/home/nux/Developer/study/cpp/school-physics-app/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(unit_tests_TESTS [==[PositionCalculatorTest.BasicInitialization]==] [==[PositionCalculatorTest.TrackObjectWithValidFrame]==])

find_package( OpenCV REQUIRED )

add_library(logic_lib STATIC
  window/window.cc
  position/position.cc
)

target_include_directories(logic_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(logic_lib PUBLIC ${OpenCV_LIBS})

add_executable(CVTest main.cc)
target_link_libraries(CVTest PRIVATE logic_lib)

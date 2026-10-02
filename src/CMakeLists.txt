find_package(OpenCV CONFIG REQUIRED)

add_library(app STATIC
  window/window.cc
  position/position.cc
  movement/movement.cc
  kinematics/kinematics.cc
  colors/colors.cc
)

target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(app PUBLIC ${OpenCV_LIBS})

add_executable(SchoolPhysicsProject main.cc)

target_link_libraries(SchoolPhysicsProject PRIVATE
  app
)

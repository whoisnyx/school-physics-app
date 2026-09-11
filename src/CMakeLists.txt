add_executable(CVTest main.cc
  window/window.cc
  position/position.cc
)

target_include_directories(CVTest
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

target_link_libraries( CVTest ${OpenCV_LIBS} )

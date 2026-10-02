cmake_minimum_required(VERSION 4.4.0)
project(SchoolPhysicsProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Werror)
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

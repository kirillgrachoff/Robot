cmake_minimum_required(VERSION 3.5)
project(RobotProject)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(RobotProject main.cpp Constants.hpp Window.cpp Window.hpp Point.hpp Field.cpp Field.hpp Point.cpp)
target_link_libraries(RobotProject ${SDL2_LIBRARIES})

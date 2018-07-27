cmake_minimum_required(VERSION 3.5s)
project(RobotProject)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(RobotProject main.cpp Constants.h Window.cpp Window.h Point.h Field.cpp Field.h Point.cpp)
target_link_libraries(RobotProject ${SDL2_LIBRARIES})
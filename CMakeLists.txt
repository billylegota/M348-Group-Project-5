cmake_minimum_required(VERSION 3.17)
project(Chapter_6)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(Chapter6 src/Main.cpp src/BackwardEulerMethod.cpp src/TrapezoidalMethod.cpp src/Util.cpp)
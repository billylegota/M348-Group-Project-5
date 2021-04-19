cmake_minimum_required(VERSION 3.17)
project(Chapter_6)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(BackwardsEuler src/backEulerMethodMain.cpp src/backEulerMethod.cpp src/matlabPlot.cpp src/matrix.cpp)
add_executable(TrapezoidalMethod src/trapMethodMain.cpp src/matlabPlot.cpp src/matrix.cpp src/trapMethod.cpp)
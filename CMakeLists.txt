cmake_minimum_required(VERSION 3.15)
project(Chapter_6)

set(CMAKE_CXX_STANDARD 20)

# See: https://cliutils.gitlab.io/modern-cmake/chapters/projects/submodule.html
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMODULE_RESULT)
        if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update failed with ${GIT_SUBMODULE_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/exprtk/)

add_executable(Chapter6 src/Main.cpp src/BackwardEulerMethod.cpp src/TrapezoidalMethod.cpp src/Util.cpp)
add_executable(PredatorPrey src/PredatorPrey.cpp src/TrapezoidalMethod.cpp src/Util.cpp)
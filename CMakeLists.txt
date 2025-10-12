cmake_minimum_required(VERSION 3.10) # minimum version required

project(ToySim) # name of the project

set(CMAKE_CXX_STANDARD 20) # c++ standard

include_directories(include) # those are directories for include <><><><>

set(SOURCES
    src/interpreter.cpp
    src/commands.cpp)

add_executable(ToySim ${SOURCES})



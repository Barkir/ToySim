cmake_minimum_required(VERSION 3.10) # minimum version required

project(ToySim) # name of the project

set(CMAKE_CXX_STANDARD 20) # c++ standard

include_directories(include) # those are directories for include <><><><>

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})


set(INTERPRETER_SOURCES
    src/interpreter.cpp
    src/commands.cpp
    src/helper.cpp
)

set(JIT_SOURCES
    src/jit.cpp
    src/helper.cpp
)

add_executable(toy_interpreter ${INTERPRETER_SOURCES})
add_executable(toy_jit ${JIT_SOURCES})

target_link_libraries(toy_jit ${LLVM_LIBS})
target_compile_options(toy_jit PRIVATE ${LLVM_CXXFLAGS})



cmake_minimum_required(VERSION 3.10)
project(ToySim)

set(CMAKE_CXX_STANDARD 20)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS} include)
add_definitions(${LLVM_DEFINITIONS})


set(INTERPRETER_SOURCES
    src/interpreter.cpp
    src/commands.cpp
    src/helper.cpp
)

set(JIT_SOURCES
    src/commands_jit.cpp
    src/jit.cpp
    src/helper.cpp
)

add_executable(toy_interpreter ${INTERPRETER_SOURCES})
add_executable(toy_jit ${JIT_SOURCES})

# Link against the LLVM library
target_link_libraries(toy_jit LLVM-20)
target_compile_options(toy_jit PRIVATE ${LLVM_CXXFLAGS})

target_link_libraries(toy_interpreter LLVM-20)
target_compile_options(toy_interpreter PRIVATE ${LLVM_CXXFLAGS})

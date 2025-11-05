cmake_minimum_required(VERSION 3.10)
project(JIT)

# finding llvm...
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(jit main.c)
target_link_libraries(jit LLVM)

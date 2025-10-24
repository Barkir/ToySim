#!/bin/bash

mkdir -p benchmarks/hyperfine
mkdir -p benchmarks/perf
mkdir -p benchmarks/images
mkdir -p build
cd build
cmake ..
cmake --build .

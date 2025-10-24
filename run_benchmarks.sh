#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

BENCH_DIR="./benchmarks"
PERF_DIR="./benchmarks/perf"
HYPERFINE_DIR="./benchmarks/hyperfine"

echo -e "${YELLOW} Starting benchmarks from dir: ${BENCH_DIR} ${NC}"

bench_files=$(find "$BENCH_DIR" -name "bench*.rb" -type f | sort)

run_benchmarks() {
    local bench_file="$1"
    local bench_name=$(basename "$bench_file" .rb)
    echo -e "${GREEN} starting: ${YELLOW} $bench_name$ ${NC}"

    perf record -g -o "$PERF_DIR/${bench_name}.data" -- ruby "$bench_file"
    hyperfine -i "ruby $bench_file" > "$HYPERFINE_DIR/$bench_name.hpf"

}

for bench_file in $bench_files; do
    run_benchmarks "$bench_file"
done

cd ./benchmarks
python3 ./build_plot.py



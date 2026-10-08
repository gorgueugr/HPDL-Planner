#!/usr/bin/env bash
# Compila HPDL-Planner. Requiere: cmake (>=3.16), flex, libfl-dev, bison, g++.
set -euo pipefail
cd "$(dirname "$0")"
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j"$(nproc)"
echo
echo "Listo ->  ./build/planner --help"

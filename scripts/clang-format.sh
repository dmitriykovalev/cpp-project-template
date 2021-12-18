#!/bin/bash

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly PROJECT_DIR="${SCRIPT_DIR}/.."

find "${PROJECT_DIR}/src" \
     "${PROJECT_DIR}/tests" \
     "${PROJECT_DIR}/benchmarks" \
     \( -iname '*.cc' -o -iname '*.h' \) | xargs clang-format -i

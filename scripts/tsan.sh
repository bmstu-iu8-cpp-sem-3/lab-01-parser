#!/usr/bin/env bash

pushd $(git rev-parse --show-toplevel)

set -e

export CTEST_OUTPUT_ON_FAILURE=true

CMAKE_CONFIG_OPTS="-DHUNTER_CONFIGURATION_TYPES=Debug -DCMAKE_BUILD_TYPE=Debug"
CMAKE_SANITIZER_OPTS="-DCMAKE_CXX_FLAGS='-fsanitize=thread'"
CMAKE_OPTS="$CMAKE_LINKER_OPTS $CMAKE_CONFIG_OPTS $CMAKE_SANITIZER_OPTS"
cmake -H. -B_builds/sanitize-thread-cxx17 $CMAKE_OPTS
cmake --build _builds/sanitize-thread-cxx17
./_builds/sanitize-thread-cxx17/tests
rm -r ./_builds

popd

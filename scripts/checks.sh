#!/usr/bin/env bash

pushd $(git rev-parse --show-toplevel)

set -e

declare -r FILTER=-build/c++11,-runtime/references,\
-whitespace/braces,-whitespace/indent,-whitespace/comments,-build/include_order

find ./include/ ./scripts/ ./sources/ -name "*.cpp" -or -name "*.hpp" -or -name ".h" | xargs cpplint --filter=$FILTER

export CTEST_OUTPUT_ON_FAILURE=true
# address sanitizer
#CMAKE_LINKER_OPTS="-DCMAKE_EXE_LINKER='-fuse-ld=gold'"
CMAKE_CONFIG_OPTS="-DHUNTER_CONFIGURATION_TYPES=Debug -DCMAKE_BUILD_TYPE=Debug"
if [[ ! "$OSTYPE" == "darwin"* ]]; then
  CMAKE_TOOLCHAIN_OPTS="-DCMAKE_TOOLCHAIN_FILE='tools/polly/sanitize-address-cxx17-pic.cmake'"
fi
CMAKE_OPTS="$CMAKE_LINKER_OPTS $CMAKE_CONFIG_OPTS $CMAKE_TOOLCHAIN_OPTS"
cmake -H. -B_builds/sanitize-address-cxx17 $CMAKE_OPTS
cmake --build _builds/sanitize-address-cxx17
if [[ "$OSTYPE" == "darwin"* ]]; then
  source scripts/macos_leak_check.sh
  macos_leak_check ./_builds/sanitize-address-cxx17/tests ./_builds/sanitize-address-cxx17/tests.memgraph
  exit
fi
./_builds/sanitize-address-cxx17/tests
# thread sanitizer
CMAKE_TOOLCHAIN_OPTS="-DCMAKE_TOOLCHAIN_FILE='tools/polly/sanitize-thread-cxx17-pic.cmake'"
CMAKE_OPTS="$CMAKE_LINKER_OPTS $CMAKE_CONFIG_OPTS $CMAKE_TOOLCHAIN_OPTS"
cmake -H. -B_builds/sanitize-thread-cxx17 $CMAKE_OPTS
cmake --build _builds/sanitize-thread-cxx17
./_builds/sanitize-thread-cxx17/tests

rm -r ./_builds

popd

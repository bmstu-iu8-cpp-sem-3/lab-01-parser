#!/usr/bin/env bash

pushd $(git rev-parse --show-toplevel)

set -e

export CTEST_OUTPUT_ON_FAILURE=true

CMAKE_CONFIG_OPTS="-DHUNTER_CONFIGURATION_TYPES=Debug -DCMAKE_BUILD_TYPE=Debug"
if [[ ! "$OSTYPE" == "darwin"* ]]; then
  CMAKE_SANITIZER_OPTS="-DCMAKE_CXX_FLAGS='-fsanitize=address'"
fi
CMAKE_OPTS="$CMAKE_LINKER_OPTS $CMAKE_CONFIG_OPTS $CMAKE_SANITIZER_OPTS"
cmake -H. -B_builds/sanitize-address-cxx17 $CMAKE_OPTS
cmake --build _builds/sanitize-address-cxx17
if [[ "$OSTYPE" == "darwin"* ]]; then
  source scripts/macos_leak_check.sh
  macos_leak_check ./_builds/sanitize-address-cxx17/tests ./_builds/sanitize-address-cxx17/tests.memgraph
  exit
fi
./_builds/sanitize-address-cxx17/tests
rm -r ./_builds

popd

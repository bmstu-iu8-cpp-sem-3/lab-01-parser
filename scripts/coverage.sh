#!/usr/bin/env bash

pushd $(git rev-parse --show-toplevel)

set -e
export CTEST_OUTPUT_ON_FAILURE=true

CMAKE_CONFIG_OPTS="-DHUNTER_CONFIGURATION_TYPES=Debug -DCMAKE_BUILD_TYPE=Debug"
CMAKE_OPTS="$CMAKE_LINKER_OPTS $CMAKE_CONFIG_OPTS $CMAKE_TOOLCHAIN_OPTS"

cmake -H. -B_builds $CMAKE_OPTS -DBUILD_COVERAGE=ON
cmake --build _builds
cmake --build _builds --target test
cmake --build _builds --target gcov
gcovr -r  .

rm -r _builds

popd

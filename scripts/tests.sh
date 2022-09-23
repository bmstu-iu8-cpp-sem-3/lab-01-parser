#!/usr/bin/env bash

pushd $(git rev-parse --show-toplevel)

set -e
export GTEST_COLOR=1
CMAKE_LINKER_OPTS="-DCMAKE_EXE_LINKER='-fuse-ld=gold'"
CMAKE_CONFIG_OPTS="-DHUNTER_CONFIGURATION_TYPES=Debug -DCMAKE_BUILD_TYPE=Debug"
CMAKE_OPTS="$CMAKE_LINKER_OPTS $CMAKE_CONFIG_OPTS"
cmake -H. -B_builds $CMAKE_OPTS
cmake --build _builds
cmake --build _builds --target test -- ARGS="--verbose"

rm -r _builds

popd

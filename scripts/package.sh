#!/usr/bin/env bash

pushd $(git rev-parse --show-toplevel)

set -e
CMAKE_LINKER_OPTS="-DCMAKE_EXE_LINKER='-fuse-ld=gold'"
CPACK_CONFIG_OPTS="-DCPACK_OUTPUT_FILE_PREFIX=_artifacts -DCPACK_GENERATOR=DEB"
CMAKE_CONFIG_OPTS="-DHUNTER_CONFIGURATION_TYPES=Release -DCMAKE_BUILD_TYPE=Release -DBUILD_DOCS=ON"
CMAKE_OPTS="$CMAKE_LINKER_OPTS $CMAKE_CONFIG_OPTS $CPACK_CONFIG_OPTS"
cmake -H. -B_builds $CMAKE_OPTS
cmake --build _builds --target docs
cmake --build _builds --target package

CPACK_CONFIG_OPTS="-DCPACK_OUTPUT_FILE_PREFIX=_artifacts -DCPACK_GENERATOR=RPM"
CMAKE_OPTS="$CMAKE_LINKER_OPTS $CMAKE_CONFIG_OPTS $CMAKE_TOOLCHAIN_OPTS $CPACK_CONFIG_OPTS"
cmake -H. -B_builds $CMAKE_OPTS
cmake --build _builds --target package

# artifacts are left in _artifacts, and it should no be removed
rm -r _builds

popd

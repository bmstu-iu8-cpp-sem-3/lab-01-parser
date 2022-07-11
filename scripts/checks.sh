#!/usr/bin/env bash

pushd $(git rev-parse --show-toplevel)

set -e

export CTEST_OUTPUT_ON_FAILURE=true
# address sanitizer
./scripts/asan.sh

# thread sanitizer
./scripts/tsan.sh

popd

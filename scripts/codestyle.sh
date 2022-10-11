#!/usr/bin/env bash

pushd $(git rev-parse --show-toplevel)

set -e

declare -r FILTER=-build/c++11,-runtime/references,\
-whitespace/braces,-whitespace/indent,-whitespace/comments,-build/include_order,-build/include_subdir

find ./include/ ./scripts/ ./sources/ -name "*.cpp" -or -name "*.hpp" -or -name ".h" | xargs python3 -m cpplint --filter=$FILTER

popd

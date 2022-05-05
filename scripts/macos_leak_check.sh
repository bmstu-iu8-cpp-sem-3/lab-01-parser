# Run leaks util from Xcode on compiled binary
# We cannot just pass the binary to leaks, as it will not output graphs with that option
# instead, we start the binary and attach to it, take it's memory snapshot and output that as a graph
# It is also possible to attach a debugger at this point for any reason should it become necessary
# ARGUMENTS:
#     Path to binary
#     Output memgraph path
macos_leak_check() {
  MallocScribble=1 MallocStackLogging=1 MallocStackLoggingNoCompact=1 MallocStackLogging=1 MallocStackLoggingNoCompact=1 $1 --gtest_also_run_disabled_tests & TEST_PID=$!
  # wait for all the tests to finish and the code to get stuck in permaloop disabled test
  # is signaling this script possible from code somehow without busy waiting?
  sleep 1
  leaks --outputGraph $2 $TEST_PID
  kill $TEST_PID
}

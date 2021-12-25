# library_test
add_executable(library_test
  library_test.cc
)
target_link_libraries(library_test PRIVATE
  project_options
  project_warnings
  library
  glog::glog
  gmock
  gtest
  gtest_main
)

# library_fuzz_test
add_executable(library_fuzz_test
  library_fuzz_test.cc
)
target_link_libraries(library_fuzz_test PRIVATE
  project_options
  project_warnings
  library
  -fsanitize=fuzzer,undefined,address
)
target_compile_options(library_fuzz_test PRIVATE
  -fsanitize=fuzzer,undefined,address
)

include(GoogleTest)
gtest_discover_tests(library_test
  DISCOVERY_TIMEOUT 30
  PROPERTIES
    ENVIRONMENT TEST_SRCDIR=${CMAKE_CURRENT_SOURCE_DIR}
)

add_test(
  NAME library_fuzz_test
  COMMAND library_fuzz_test -max_total_time=10
)

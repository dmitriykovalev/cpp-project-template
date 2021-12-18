# library_test
add_executable(library_test
  library_test.cc
)
target_link_libraries(library_test
  library
  glog::glog
  gtest
  gmock
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(library_test
  DISCOVERY_TIMEOUT 30
  PROPERTIES
    ENVIRONMENT TEST_SRCDIR=${CMAKE_CURRENT_SOURCE_DIR}
)

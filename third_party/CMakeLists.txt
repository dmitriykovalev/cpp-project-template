set(BUILD_TESTING OFF)

# https://github.com/abseil/abseil-cpp
set(ABSL_PROPAGATE_CXX_STD ON CACHE BOOL "" FORCE)
add_subdirectory(abseil-cpp)

# https://github.com/google/benchmark
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(benchmark)

# https://github.com/google/glog
add_subdirectory(glog)

# https://github.com/google/googletest
add_subdirectory(googletest)

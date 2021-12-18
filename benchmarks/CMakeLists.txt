# library_benchmark
add_executable(library_benchmark
  library_benchmark.cc
)
target_link_libraries(library_benchmark
  library
  benchmark::benchmark
)

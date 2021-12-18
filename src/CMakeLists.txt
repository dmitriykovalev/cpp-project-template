# library
add_library(library
  library.h
  library.cc
)
target_include_directories(library PUBLIC .)
target_link_libraries(library PUBLIC
  absl::strings
  absl::statusor
  project_options
  project_warnings)

# hexdump
add_executable(hexdump
  hexdump.cc)
target_link_libraries(hexdump PRIVATE
  absl::flags
  absl::flags_parse
  glog::glog
  library
  project_options
  project_warnings)

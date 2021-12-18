cmake_minimum_required(VERSION 3.15)

project(CppProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# sanitizers
set(RUNTIME_SANITIZERS "" CACHE STRING "Comma-separated list of sanitizers (address|leak|undefined|thread|memory)")

if (RUNTIME_SANITIZERS)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    add_compile_options(-fsanitize=${RUNTIME_SANITIZERS})
    add_link_options(-fsanitize=${RUNTIME_SANITIZERS})
  else()
    message(WARNING "Sanitizers are only supported for Clang and GCC")
  endif()
endif()

# project_options
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# project_warnings
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# source
add_subdirectory(third_party)
add_subdirectory(src)

# tests
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

# benchmarks
option(BUILD_BENCHMARKS "Build benchmark binaries." ON)
if(BUILD_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()

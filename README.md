# CMake C++ Project Template

This is a template to start C++ project using common Google libraries.

* C++17 by default
* Formatting via [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
  (run `scripts/clang-format.sh` to reformat everything)
* Clang/GCC sanitizers
* Benchmarks via [Benchmark](https://github.com/google/benchmark) library
* Tests via [GoogleTest](https://github.com/google/googletest) library
* Logging via [Google Logging Library](https://github.com/google/glog) library
* [Abseil](https://github.com/abseil/abseil-cpp) library

## Install

### Linux

```bash
sudo apt-get install cmake
```

### macOS

```bash
# Using Homebrew
brew install --cask cmake
```

```bash
# Using MacPorts
sudo port install cmake +gui
```

## Build

There are several [build types](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html):

* `-DCMAKE_BUILD_TYPE=Debug`
* `-DCMAKE_BUILD_TYPE=Release`
* `-DCMAKE_BUILD_TYPE=RelWithDebInfo`
* `-DCMAKE_BUILD_TYPE=MinSizeRel`

There are multiple [generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)
including:

* `-G "Unix Makefiles"`
* `-G Ninja`

### Debug + Unix Makefiles

```bash
# Run cmake
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"

# Run make via cmake
cmake --build build

# Or run make directly
make -C build VERBOSE=1

# Run compiled binary
GLOG_logtostderr=1 build/src/hexdump --filename build/src/hexdump
```

### Release + Ninja

```bash
# Run cmake
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G Ninja

# Run ninja via cmake
cmake --build build

# Or run ninja directly
ninja -C build

# Run compiled binary
GLOG_logtostderr=1 build/src/hexdump --filename build/src/hexdump
```

## Test

Tests are enabled by default:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF -DRUNTIME_SANITIZERS=address,undefined -G Ninja
cmake --build build
ctest -V --test-dir build
```

Test receives `TEST_SRCDIR` environment variable which points to
`${CMAKE_SOURCE_DIR}/tests`. Specify it manually if running test
binary directly:
```bash
TEST_SRCDIR=$(pwd)/tests build/tests/library_test
```

Disable tests by passing `-DBUILD_TESTING=OFF` to `cmake` command.

Check more about writing tests in [GoogleTest Primer](https://google.github.io/googletest/primer.html).

## Benchmark

Benchmarks are enabled by default:
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G Ninja
cmake --build build
build/benchmarks/library_benchmark
```

Disable benchmarks by passing `-DBUILD_BENCHMARKS=OFF` to `cmake` command.

## Presets

[Presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html)
are defined in `CMakePresets.json`.

```bash
# debug-make
cmake --preset debug-make
cmake --build --preset debug-make
ctest --preset debug-make
```

```bash
# debug-ninja
cmake --preset debug-ninja
cmake --build --preset debug-ninja
ctest --preset debug-ninja
```

```bash
# release-make
cmake --preset release-make
cmake --build --preset release-make
```

```bash
# release-ninja
cmake --preset release-ninja
cmake --build --preset release-ninja
```

```bash
# check variables
cmake --preset release-ninja -N
```

## Resources

* https://github.com/cpp-best-practices/cpp_starter_project
* [CMake Documentation](https://cmake.org/cmake/help/latest/)
* [Professional CMake: A Practical Guide](https://crascit.com/professional-cmake/)

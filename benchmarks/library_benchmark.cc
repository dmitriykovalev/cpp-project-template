#include <iterator>
#include <sstream>

#include "benchmark/benchmark.h"
#include "library.h"

namespace {

void BM_Print(benchmark::State& state) {
  const uint8_t data[] = {'a', 'b', 'c'};

  std::ostringstream ss;
  for (auto _ : state) {
    hexdump::Print(ss, std::begin(data), std::end(data), 10);
    state.PauseTiming();
    ss.clear();
    state.ResumeTiming();
  }
}

BENCHMARK(BM_Print);
}  // namespace

BENCHMARK_MAIN();

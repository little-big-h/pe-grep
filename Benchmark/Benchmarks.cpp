#include "Implementation.hpp"
#include <benchmark/benchmark.h>
#include <iostream>
using namespace std;
auto const minimumInputSize = 64 * 1024;
auto const maximumInputSize = 64 * 1024;

static void toyBenchmark(benchmark::State& state) {
  for(auto _ : state) {
  }
}
BENCHMARK(toyBenchmark)->Range(minimumInputSize, maximumInputSize);

BENCHMARK_MAIN();

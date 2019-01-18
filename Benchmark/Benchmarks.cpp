#include "Implementation.hpp"
#include <benchmark/benchmark.h>
#include <iostream>
using namespace std;
auto const minimumInputSize = 64 * 1024;
auto const maximumInputSize = 64 * 1024;

static void selectionWithPrefixString(benchmark::State& state) {
  auto lines = make_unique<Input>();
  for(size_t i = 0; i < state.range(0); i++)
    lines->push_back("line " + to_string(i));
  for(auto _ : state) {
    auto s = Select(move(lines), [](string s) -> bool { return s.compare(0, 4, "line") == 0; });
    s.size();
    lines.reset((Input*)s.getChildWithOwnership().release());
    lines->reset();
  }
}
BENCHMARK(selectionWithPrefixString)
    ->Range(minimumInputSize, maximumInputSize)
    ->Unit(benchmark::kMicrosecond);

static void selectionWithPrefixIntLambda(benchmark::State& state) {
  auto lines = make_unique<Input>();
  for(size_t i = 0; i < state.range(0); i++)
    lines->push_back("line " + to_string(i));
  for(auto _ : state) {
    auto s = Select(move(lines), [](string s) -> bool {
      int line = *(int*)"line";
      return *((int*)s.c_str()) == line;
    });
    s.size();
    lines.reset((Input*)s.getChildWithOwnership().release());
    lines->reset();
  }
}
BENCHMARK(selectionWithPrefixIntLambda)
    ->Range(minimumInputSize, maximumInputSize)
    ->Unit(benchmark::kMicrosecond);

static void selectionWithPrefixInt(benchmark::State& state) {
  auto lines = make_unique<Input>();
  for(size_t i = 0; i < state.range(0); i++)
    lines->push_back("line " + to_string(i));
  for(auto _ : state) {
    int const line = *(int*)"line";
    auto s = SelectWithPrefixInt(move(lines), line);
    s.size();
    lines.reset((Input*)s.getChildWithOwnership().release());
    lines->reset();
  }
}
BENCHMARK(selectionWithPrefixInt)
    ->Range(minimumInputSize, maximumInputSize)
    ->Unit(benchmark::kMicrosecond);

static void bulkSelectionWithPrefixInt(benchmark::State& state) {
  auto lines = make_unique<Input>();
  for(size_t i = 0; i < state.range(0); i++)
    lines->push_back("line " + to_string(i));
  for(auto _ : state) {
    int const line = *(int*)"line";
    auto s = BulkSelectWithPrefixInt(move(lines), line);
    s.size();
    lines.reset((Input*)s.getChildWithOwnership().release());
    lines->reset();
  }
}
BENCHMARK(bulkSelectionWithPrefixInt)
    ->Range(minimumInputSize, maximumInputSize)
    ->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();

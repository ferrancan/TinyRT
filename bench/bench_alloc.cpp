#include <benchmark/benchmark.h>
#include <cstdlib>

static void BM_Malloc64(benchmark::State& state) {
    for (auto _ : state) {
        void* p = std::malloc(64);
        benchmark::DoNotOptimize(p);
        std::free(p);
    }
}
BENCHMARK(BM_Malloc64);

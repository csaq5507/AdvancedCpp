#ifndef CUSTOM_BENCHMARK_H
#define CUSTOM_BENCHMARK_H

#include "benchmark/benchmark.h"
#include "../src/vcs_utility.h"

#define CUSTOM_BENCHMARK(f) BENCHMARK(f) \
->RangeMultiplier(2) \
->Range(16, 8 << 3) \
->ReportAggregatesOnly() \
->Repetitions(5) \
->Complexity() \

static void commit(benchmark::State& state)
{
  const auto n = state.range(0);

  state.SetComplexityN(n);

    Vcs init = Vcs();
    if(!init.is_vcs_initialized())
        init.init_vcs();
    Vcs bench = Vcs();

  while (state.KeepRunning())
  {
      for(int i=0;i<n;i++)
      try{
          bench.commit("benchcommit");
      } catch(const std::exception& e){
          state.SkipWithError(e.what());
      }
  }
}

#endif // CUSTOM_BENCHMARK_H

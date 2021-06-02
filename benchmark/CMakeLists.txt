add_executable(benchmarks
  benchmark_visit.cpp
)

target_link_libraries(benchmarks
  PRIVATE
    variant_visit
    benchmark::benchmark
)

#include <array>
#include <random>
#include <variant>

#include <benchmark/benchmark.h>

#include "zob/variant_visit.h"

namespace {
  struct Foo {
    int f = 3;
  };

  struct Bar {
    int b = 5;
  };

  using FooBar = std::variant<Foo, Bar>;

  struct FooBarVisitor {
    int counter = 0;

    void operator()(const Foo& foo) {
      counter += foo.f;
    }
    void operator()(const Bar& bar) {
      counter += bar.b;
    }
  };

  const size_t N = 10000;
  static std::array<FooBar, N> foobar_array;

  void init_foobar_array() {
    // Only initialised once, so array has same contents for all tests
    static bool initialized = false;
    if (initialized) {
      return;
    } else {
      initialized = true;
    }

    // Random number generator for 0 or 1
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    // Propagate variant array with random Foo and Bar instances
    for (size_t i = 0; i < N; ++i) {
      if (dist(gen) == 0) {
        foobar_array[i] = Foo{};
      } else {
        foobar_array[i] = Bar{};
      }
    }
  }

  bool run_zob_visit() {
    FooBarVisitor fbvisit;
    for (const auto& foobar : foobar_array) {
      zob::visit(fbvisit, foobar);
    }

    return true; // Return value for compiling with DoNotOptimize
  }

  bool run_std_visit() {
    FooBarVisitor fbvisit;
    for (const auto& foobar : foobar_array) {
      std::visit(fbvisit, foobar);
    }

    return true; // Return value for compiling with DoNotOptimize
  }
} // local namespace

static void benchmark_zob_visit(benchmark::State& state) {
  init_foobar_array();

  for (auto _ : state) {
    benchmark::DoNotOptimize(run_zob_visit());
  }
}
BENCHMARK(benchmark_zob_visit);

static void benchmark_std_visit(benchmark::State& state) {
  init_foobar_array();

  for (auto _ : state) {
    benchmark::DoNotOptimize(run_std_visit());
  }
}
BENCHMARK(benchmark_std_visit);

BENCHMARK_MAIN();
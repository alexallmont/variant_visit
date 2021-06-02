#include <array>
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
} // local namespace

//! Return an array of random FooBar values that is static, so the same values can be reused in multiple benchmarks
//!
auto generate_identical_foobar_array() {
  const size_t N = 100000;
  static std::array<FooBar, N> result;

  bool generated = false;
  if (!generated) {
    for (size_t i = 0; i < N; ++i) {
      if (i & 1) {
        result[i] = Foo{};
      } else {
        result[i] = Bar{};
      }
    }
  }

  return result;
}

static void benchmark_zob_visit(benchmark::State& state) {
  FooBarVisitor fbvisit;
  auto arr = generate_identical_foobar_array();

  for (auto _ : state) {
    for (const auto& a : arr) {
        zob::visit(a, fbvisit);
    }
  }
}
BENCHMARK(benchmark_zob_visit);

static void benchmark_std_visit(benchmark::State& state) {
  FooBarVisitor fbvisit;
  auto arr = generate_identical_foobar_array();

  for (auto _ : state) {
    for (const auto& a : arr) {
        std::visit(fbvisit, a);
    }
  }
}
BENCHMARK(benchmark_std_visit);

BENCHMARK_MAIN();
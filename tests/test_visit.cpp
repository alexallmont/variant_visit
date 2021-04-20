#include <array>
#include <catch2/catch.hpp>

#include "variant_visit.h"

namespace {
  struct Foo {
    int f = 1;
  };

  struct Bar {
    int b = 2;
  };

  using FooBar = std::variant<Foo, Bar>;

  struct FooBarVisitor {
    int counter = 0;

    void operator()(const Foo& foo) {
      counter += foo.f;
    }
    void operator()(const Bar& bar) {
      counter *= bar.b;
    }
  };
} // namespace

// This is not a well-defined test, for now I'm just testing that
// visitation broadly works as expected
TEST_CASE("Variant Visitor Experiment", "[variant_visit]" ) {
  std::array<FooBar, 4> arr = {Foo{}, Bar{}, Bar{}, Foo{}};

  // Test visiting vanilla array
  {
    FooBarVisitor fbvisit;
    for (const auto& a : arr) {
        zob::visit(a, fbvisit);
    }
    // Expected value as if right-folded
    const int expected = (((((0) + 1) * 2) * 2) + 1);
    REQUIRE(fbvisit.counter == expected);
  }

  // Test visiting mutated array
  // (FIXME add docs on benefit here of reduced generated assembly)
  {
    arr[1] = Foo{};

    FooBarVisitor fbvisit;
    for (const auto& a : arr) {
        zob::visit(a, fbvisit);
    }
    // Expected value as if right-folded
    const int expected = (((((0) + 1) + 1) * 2) + 1);
    REQUIRE(fbvisit.counter == expected);
  }
}

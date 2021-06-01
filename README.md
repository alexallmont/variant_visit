# variant_visit

More docs to follow, but in short I found that std::visit generated very noisy code when used with std::variant in Clang, GCC and MSVC. In all cases there were many more calls than expected, and some vtables were generated in places where I thought things should be statically inferred. This class uses compile-time type information to generate more optimal assembly code.

## Example

This was my starting point on Godbolt <https://godbolt.org/z/fv8z9Yr6Y>. A variant of types Foo and Bar is stored in an array. If the `if (argc == 1)` condition is left out then Clang can reduce this to a move operation, but other compilers add a lot of noise, and when the conditional is introduced, all compilers don't seem to be able to reduce the visit gracefully:

    struct Foo {};
    struct Bar {};
    using FooBar = std::variant<Foo, Bar>;

    struct FooBarVisitor {
      int acc = 1;
      void operator()(const Foo&) { acc += 1; }
      void operator()(const Bar&) { acc *= 2; }
    };

    int main(int argc, char*[]) {
      std::array<FooBar, 4> arr = {Foo(), Bar(), Bar(), Foo()};
      if (argc == 1) {
        arr[1] = Foo();
      }

      FooBarVisitor sv;
      for (const auto& a : arr) {
         zob::visit(a, sv);
         //std::visit(sv, a);
      }

      return sv.acc;
    }

Clang 12.0.0 generated the following assembly using zob::visit:

![zob::visit example](/images/zob-visit.png)

Whilst std::visit generated:

![std::visit example](/images/std-visit.png)

For now this is parked as an idea, if it's useful please let me know and I'll revisit it. Please pardon the visitor and variant args being swapped between zob::visit and std::visit. There are other things to address if this is useful, for example it currently only works with const references and the call operator cannot take a variable number of args.

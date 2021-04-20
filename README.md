# variant_visit

More docs to follow, but in short I found that std::visit generated very noisy code when used with std::variant in Clang, GCC and MSVC. In all cases there were many more calls than expected, and some vtables were generated in places where I thought things should be statically inferred. This class uses compile-time type information to generate more optimal assembly code.

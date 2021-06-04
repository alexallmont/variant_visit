#pragma once

//! /author Alex Allmont
//! /brief Method for visiting std::variant without vtable generation
//!
//! Using std::visit on a std::variant does not seem to compile well
//! in GCC, Clang or MSVC, generating excessing calls and vtables.
//! This code attempts to mitigate that by unrolling the known type
//! information in a variadic, and unrolling the potential calls
//!
//! Note at present, this only supports call operators that take
//! no arguments, and where the variant is const.

#include <variant>

namespace zob {
  namespace detail {

    // Struct that wraps calls to a visitor containing call operator
    // given a paricular set of variant arguments. VariantArgs is
    // generated by the visit() method matching a std::variant<...>
    template <
      typename Visitor,
      typename... VariantArgs
    >
    struct ConstVariantCallVisitor {

      // Attempt to match and call last argument in VariantArgs.
      template <
        typename Last
      >
      void call_first_match(
        const std::variant<VariantArgs...>& inst,
        Visitor& visitor
      ) {
        if (const auto value_ptr = std::get_if<Last>(&inst)) {
          visitor(*value_ptr);
        } else {
          // FIXME possible to static assert?
        }
      }

      // Attempt to match and call first argument in VariantArgs,
      // and if not found then recurse to process next argument.
      template <
        typename First,
        typename Second,
        typename... Rest
      >
      void call_first_match(
        const std::variant<VariantArgs...>& inst,
        Visitor& visitor
      ) {
        if (const auto value_ptr = std::get_if<First>(&inst)) {
          visitor(*value_ptr);
        } else {
          call_first_match<Second, Rest...>(inst, visitor);
        }
      }
    };
  }
}

namespace zob {

  //! \brief Visit a std::vector
  //!
  //! For all the types in a visitor, the visitor is expected to
  //! provide a call operator that processes that type
  //!
  //! \example
  //!   struct Foo {};
  //!   struct Bar {};
  //!   using FooBar = std::variant<Foo, Bar>;
  //!   struct VisitFooBar {
  //!     int counter = 0;
  //!     void operator(const Foo&) { ++counter; }
  //!     void operator(const Bar&) { --counter; }
  //!   };
  //!   ...
  //!   visit(VisitFooBar{}, FooBar);

  template <
    typename Visitor,
    typename... VariantArgs
  >
  constexpr void visit(
    Visitor& visitor,
    const std::variant<VariantArgs...>& inst
  ) {
    // Generate a caller typed on variant arguments
    auto caller = detail::ConstVariantCallVisitor<
      Visitor,
      VariantArgs...
    >();

    // Instigate the first variadic call using the full list
    // of variant args to process recursively
    caller.template call_first_match<
      VariantArgs...
    >(
      inst,
      visitor
    );
  };
}

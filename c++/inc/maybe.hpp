#ifndef _HSCPP_MAYBE
#define _HSCPP_MAYBE

#include "monad.hpp"
#include <optional>
#include <functional>

namespace hscpp {
  template <typename a>
  class Maybe : public Monad<Maybe, a> {
  public:
    Maybe() : value{std::nullopt} {}
    Maybe(const a value) : value{value} {}

    template <typename b>
    Maybe<b> fmap_impl(const std::function<b(a)> f) const {
      return value ? Maybe<b>(f(value.value())) : Maybe<b>();
    }

    template <typename b>
    Maybe<b> ap_impl(const Maybe<std::function<b(a)>> &func) const {
      return func.value ? fmap_impl(func.value.value()) : Maybe<b>();
    }

    template <typename b>
    Maybe<b> bind_impl(const std::function<Maybe<b>(a)> f) const {
      return value ? f(value.value()) : Maybe<b>();
    }

    static Maybe<a> pure(a val) { return Maybe<a>(val); }

    operator bool() { return (bool)value; }

    const std::optional<a> value;
  };
}

#endif

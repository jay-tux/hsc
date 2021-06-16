#ifndef _HSCPP_EITHER
#define _HSCPP_EITHER

#include "monad.hpp"
#include <functional>

namespace hscpp {
  template <typename a, typename e>
  class Either : public Monad<Either, a, e> {
  public:
    Either(a value) : value{value}, isError{false} {}
    Either(e error) : value{error}, isError{true} {}

    Either(const Either<a, e> &other) : value{other.value}, isError{other.isError} {}
    Either<a, e> &operator=(Either<a, e> &other) = delete;

    template <typename b>
    Either<b, e> fmap_impl(const std::function<b(a)> f) const {
      return isError ? Either<b, e>(value.err) : Either<b, e>(f(value.val));
    }

    template <typename b>
    Either<b, e> ap_impl(const Either<std::function<b(a)>, e> &func) const {
      return func.isError ? Either<b, e>(func.value.err) : Either<b, e>(fmap(func.value.val));
    }

    template <typename b>
    Either<b, e> bind_impl(const std::function<Either<b, e>(a)> f) const {
      return isError ? Either<b, e>(value.err) : f(value.val);
    }

    static Either<a, e> pure(a val) { return Either<a, e>(val); }

    ~Either() {
      if(isError) value.err.~e();
      else value.val.~a();
    }

    const union v_type {
      v_type(a val) : val{val} {}
      v_type(e err) : err{err} {}
      const a val;
      const e err;

      ~v_type(){}
    } value;
    const bool isError;
  };
}

#endif

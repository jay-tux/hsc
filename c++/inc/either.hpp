#ifndef _HSCPP_EITHER
#define _HSCPP_EITHER

#include "monad.hpp"
#include <functional>

namespace hscpp {
  template <typename a, typename e, typename = void>
  class Either : public Monad<Either, a, e> {
  public:
    Either(const Either<a, e> &other) : value{other.value}, isError{other.isError} {}
    Either<a, e> &operator=(Either<a, e> &other) = delete;

    static Either<a, e> left(const e left)   { return Either<a, e>(left, true);  }
    static Either<a, e> right(const a right) { return Either<a, e>(right); }

    template <typename b>
    Either<b, e> fmap_impl(const std::function<b(a)> f) const {
      return isError ? Either<b, e>(value.err, true) : Either<b, e>(f(value.val));
    }

    template <typename b>
    Either<b, e> ap_impl(const Either<std::function<b(a)>, e> &func) const {
      return func.isError ? Either<b, e>::left(func.value.err) : Either<b, e>::right(fmap(func.value.val));
    }

    template <typename b>
    Either<b, e> bind_impl(const std::function<Either<b, e>(a)> f) const {
      return isError ? Either<b, e>::left(value.err) : f(value.val);
    }

    //template <typename a_, typename e_>
    static Either<a, e> pure(a val) { return Either<a, e>::right(val); }

    ~Either() {
      if(isError) value.err.~e();
      else value.val.~a();
    }

    const union v_type {
      v_type(a val) : val{val} {}
      v_type(e err, bool _) : err{err} {}
      const a val;
      const e err;

      ~v_type(){}
    } value;
    const bool isError;

  //private:
    Either(a value) : value{value}, isError{false} {}
    Either(e error, bool isError) : value{error, isError}, isError{true} {}
  };

  template<typename a, typename e>
  class Either<a, e,
    std::enable_if_t<std::conjunction_v<std::is_base_of<Show, a>, std::is_base_of<Show, e>>>
    > : public Show {
  public:
    hsString show() const override {
      return (isError) ?
        (hsString::fromString("Error: ") + value.err.show()) :
        (hsString::fromString("Value: ") + value.val.show());
    }

    ~Either() {
      if(isError) value.err.~e();
      else value.val.~a();
    }

    const union v_type {
      v_type(a val) : val{val} {}
      v_type(e err, bool _) : err{err} {}
      const a val;
      const e err;

      ~v_type() {}
    } value;
    const bool isError;

  //private:
    Either(a value) : value{value}, isError{false} {}
    Either(e error, bool err) : value{error, err}, isError{true} {}
  };
}

#endif

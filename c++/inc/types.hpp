#ifndef _HSCPP_TYPES
#define _HSCPP_TYPES

#include "fwdecl_types.hpp"
#include <functional>
#include "prelude_typeclasses.hpp"

namespace hscpp {
  struct hsInt : Eq<hsInt> {
    const int value;
    hsInt(int value);
    operator int() const { return value; }
    bool eq(const hsInt other) const;
    hsInt operator+(const hsInt other) const;
    hsInt operator-(const hsInt other) const;
    hsInt operator*(const hsInt other) const;
    hsInt operator/(const hsInt other) const;
  };

  struct hsInteger : Eq<hsInteger> {
    const long value;
    hsInteger(long value);
    operator long() const { return value; }
    bool eq(const hsInteger other) const;
    hsInteger operator+(const hsInteger other) const;
    hsInteger operator-(const hsInteger other) const;
    hsInteger operator*(const hsInteger other) const;
    hsInteger operator/(const hsInteger other) const;
  };

  struct hsBool : Eq<hsBool> {
    const bool value;
    hsBool(bool value);
    operator bool() const { return value; }
    hsBool operator!() const { return hsBool(!value); }
    bool eq(const hsBool other) const;
  };

  struct hsFloat : Eq<hsFloat> {
    const float value;
    hsFloat(float value);
    operator float() const { return value; }
    bool eq(const hsFloat other) const;
    hsFloat operator+(const hsFloat other) const;
    hsFloat operator-(const hsFloat other) const;
    hsFloat operator*(const hsFloat other) const;
    hsFloat operator/(const hsFloat other) const;
  };

  struct hsDouble : Eq<hsDouble> {
    const double value;
    hsDouble(double value);
    operator double() const { return value; }
    bool eq(const hsDouble other) const;
    hsDouble operator+(const hsDouble other) const;
    hsDouble operator-(const hsDouble other) const;
    hsDouble operator*(const hsDouble other) const;
    hsDouble operator/(const hsDouble other) const;
  };

  struct hsChar : Eq<hsChar> {
    const char value;
    hsChar(char value);
    operator char() const { return value; }
    bool eq(const hsChar other) const;
  };

  template <typename TOut, typename TIn0, typename ... TIn>
  std::function<TOut(TIn ...)> curry(const std::function<TOut(TIn0, TIn ...)> f, const TIn0 val) {
    return [f, val](TIn ... args) {
      return f(val, args ...);
    };
  }
}

#endif

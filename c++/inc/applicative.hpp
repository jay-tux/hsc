#ifndef _HSCPP_APPLICATIVE
#define _HSCPP_APPLICATIVE

#include "types.hpp"
#include "functor.hpp"
#include <functional>

namespace hscpp {
  template <template <typename, typename ...> typename Self, typename a, typename ... rest>
  class Applicative : public Functor<Self, a> {
  public:
    static Self<a, rest ...> pure(a val) { return Self<a, rest ...>::pure(val); }

    template <typename b>
    Self<b, rest ...> ap(const Self<std::function<b(a)>, rest ...> func) {
      return (static_cast<Self<a, rest ...> &>(*this)).ap_impl(func);
    }
  };
}

#endif

/*
class (Functor f) => Applicative f where
  pure :: a -> f a
  ap :: f a -> f (a -> b) -> f b
*/

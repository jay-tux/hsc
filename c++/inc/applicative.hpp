#ifndef _HSCPP_APPLICATIVE
#define _HSCPP_APPLICATIVE

#include "types.hpp"
#include "functor.hpp"
#include <functional>

namespace hscpp {
  template <template <typename> typename Self, typename a>
  class Applicative : public Functor<Self, a> {
  public:
    static Self<a> pure(a val) { return Self<a>::pure(val); }

    template <typename b>
    Self<b> ap(const Self<std::function<b(a)>> func) {
      return (static_cast<Self<a> &>(*this)).ap_impl(func);
    }
  };
}

#endif

/*
class (Functor f) => Applicative f where
  pure :: a -> f a
  ap :: f a -> f (a -> b) -> f b
*/

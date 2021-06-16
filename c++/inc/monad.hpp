#ifndef _HSCPP_MONAD
#define _HSCPP_MONAD

#include "applicative.hpp"
#include <functional>

namespace hscpp {
  template <template <typename, typename ...> typename Self, typename a, typename ... rest>
  class Monad : public Applicative<Self, a> {
  public:
    Self<a, rest ...> ret(a val) { return Self<a, rest ...>::pure(val); }

    template <typename b>
    Self<b, rest ...> bind(const std::function<Self<b, rest ...>(a)> f) {
      return (static_cast<Self<a, rest ...> &>(*this)).bind_impl(f);
    }
  };
}

#endif

/*
class (Applicative m) => Monad m where
  return :: a -> m a
  bind :: m a -> (a -> m b) -> m b
*/

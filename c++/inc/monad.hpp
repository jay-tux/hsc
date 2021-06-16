#ifndef _HSCPP_MONAD
#define _HSCPP_MONAD

#include "applicative.hpp"
#include <functional>

namespace hscpp {
  template <template <typename> typename Self, typename a>
  class Monad : public Applicative<Self, a> {
  public:
    Self<a> ret(a val) { return Self<a>::pure(val); }

    template <typename b>
    Self<b> bind(const std::function<Self<b>(a)> f) {
      return (static_cast<Self<a> &>(*this)).bind_impl(f);
    }
  };
}

#endif

/*
class (Applicative m) => Monad m where
  return :: a -> m a
  bind :: m a -> (a -> m b) -> m b
*/

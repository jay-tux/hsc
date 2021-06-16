#ifndef _HSCPP_FUNCTOR
#define _HSCPP_FUNCTOR

#include "types.hpp"
#include <functional>

namespace hscpp {
  template <template <typename> typename Self, typename a>
  class Functor {
  public:
    template <typename b>
    Self<b> fmap(const std::function<b(a)> f) {
      return (static_cast<Self<a> &>(*this)).fmap_impl(f);
    }
  };
}

#endif

/*
class Functor f where
  fmap :: (a -> b) -> f a -> f b
*/

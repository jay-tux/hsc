#ifndef _HSCPP_FUNCTOR
#define _HSCPP_FUNCTOR

#include "types.hpp"
#include <functional>

namespace hscpp {
  template <template <typename, typename ...> typename Self, typename a, typename ... rest>
  class Functor {
  public:
    template <typename b>
    Self<b, rest ...> fmap(const std::function<b(a)> f) {
      return (static_cast<Self<a, rest ...> &>(*this)).fmap_impl(f);
    }
  };
}

#endif

/*
class Functor f where
  fmap :: (a -> b) -> f a -> f b
*/

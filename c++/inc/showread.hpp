#ifndef _HSCPP_SHOW
#define _HSCPP_SHOW

#include "string.hpp"

namespace hscpp {
  class Show {
    virtual hsString show() const = 0;
  };

  template <typename Self>
  class Read {
    static Self read(const hsString &value) { return Self::read(value); }
  };
}

#endif

/*
class Show a where
  show :: a -> String

class Read a where
  read :: String -> a
*/

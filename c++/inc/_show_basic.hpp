#ifndef _HSCPP__SHOW_BASIC
#define _HSCPP__SHOW_BASIC

#include "string.hpp"

namespace hscpp {
  hsString show(hsInt val);
  hsString show(hsInteger val);
  hsString show(hsBool val);
  hsString show(hsFloat val);
  hsString show(hsDouble val);
  hsString show(hsChar val);
}

#endif

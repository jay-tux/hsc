#ifndef _HSCPP_TYPES
#define _HSCPP_TYPES

//forward-declare
namespace hscpp {
  struct hsInt; struct hsInteger; struct hsBool; struct hsFloat; struct hsDouble;
  struct hsChar;
}

#include <functional>

#define hsWrapType(NAME, OGTYPE) struct NAME {\
  OGTYPE value;\
  NAME(OGTYPE value);\
  NAME &operator=(OGTYPE v);\
  operator OGTYPE() const { return value; };\
}

namespace hscpp {
  hsWrapType(hsInt, int);
  hsWrapType(hsInteger, long);
  hsWrapType(hsBool, bool);
  hsWrapType(hsFloat, float);
  hsWrapType(hsDouble, double);
  hsWrapType(hsChar, char);

  template <typename TOut, typename TIn0, typename ... TIn>
  std::function<TOut(TIn ...)> curry(const std::function<TOut(TIn0, TIn ...)> f, const TIn0 val) {
    return [f, val](TIn ... args) {
      return f(val, args ...);
    };
  }
}

#undef hsWrapType

#endif

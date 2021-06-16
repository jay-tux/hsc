#ifndef _HSCPP_TYPES
#define _HSCPP_TYPES

//forward-declare
namespace hscpp {
  struct hsInt; struct hsInteger; struct hsBool; struct hsFloat; struct hsDouble;
  struct hsChar;
}

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
}

#undef hsWrapType

#endif

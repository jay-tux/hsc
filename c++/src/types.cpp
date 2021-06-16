#include "types.hpp"
#include <string>

using namespace hscpp;

#define constructor(NAME, OGTYPE) NAME::NAME(OGTYPE value) : value{value} {}
#define operator(NAME, OGTYPE) NAME &NAME::operator=(OGTYPE v) { value = v; return *this; }

#define IMPLEMENT(NAME, OGTYPE) \
constructor(NAME, OGTYPE)\
operator(NAME, OGTYPE)

IMPLEMENT(hsInt, int)
IMPLEMENT(hsInteger, long)
IMPLEMENT(hsBool, bool)
IMPLEMENT(hsFloat, float)
IMPLEMENT(hsDouble, double)
IMPLEMENT(hsChar, char)

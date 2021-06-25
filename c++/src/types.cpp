#include "types.hpp"
#include <string>

using namespace hscpp;

#define constructor(NAME, OGTYPE) NAME::NAME(OGTYPE value) : value{value} {}
#define eq(NAME) bool NAME::eq(const NAME other) const { return (value == other.value); }
#define add(NAME) NAME NAME::operator+(const NAME other) const { return NAME(value + other.value); }
#define sub(NAME) NAME NAME::operator-(const NAME other) const { return NAME(value - other.value); }
#define mul(NAME) NAME NAME::operator*(const NAME other) const { return NAME(value * other.value); }
#define div(NAME) NAME NAME::operator/(const NAME other) const { return NAME(value / other.value); }

#define IMPLEMENT(NAME, OGTYPE) constructor(NAME, OGTYPE) eq(NAME)
#define OPS(NAME) add(NAME) sub(NAME) mul(NAME) div(NAME)

IMPLEMENT(hsInt,     int)
IMPLEMENT(hsInteger, long)
IMPLEMENT(hsBool,    bool)
IMPLEMENT(hsFloat,   float)
IMPLEMENT(hsDouble,  double)
IMPLEMENT(hsChar,    char)

OPS(hsInt)
OPS(hsInteger)
OPS(hsFloat)
OPS(hsDouble)

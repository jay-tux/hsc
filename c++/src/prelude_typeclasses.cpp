#include "prelude_typeclasses.hpp"
#include <stdexcept>

using namespace hscpp;

const Ordering Ordering::LT(order_t::LT);
const Ordering Ordering::EQ(order_t::EQ);
const Ordering Ordering::GT(order_t::GT);

bool Ordering::eq(const Ordering &other) const { return (value == other.value); }
Ordering Ordering::cmp(const Ordering &other) const {
  if(eq(other)) return order_t::EQ; //LT==LT, EQ==EQ, GT==GT
  if(value == order_t::LT) return order_t::LT; //LT<EQ, LT<GT
  if(value == order_t::GT) return order_t::GT; //GT>EQ, GT>LT
  if(other.value == order_t::LT) return order_t::GT; //EQ>LT
  return order_t::LT; //EQ<GT
}

Ordering Ordering::minBound() { return Ordering::LT; }
Ordering Ordering::maxBound() { return Ordering::GT; }

Ordering Ordering::to(const hsInt &value) {
  if(value > hsInt(1) || value < hsInt(-1)) throw std::runtime_error("toEnum: invalid argument");
  return (value == hsInt(1)) ? Ordering::GT : (value == hsInt(0)) ? Ordering::EQ : Ordering::LT;
}

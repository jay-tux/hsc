#ifndef _HSCPP_PRELUDE
#define _HSCPP_PRELUDE

//forward declares
namespace hscpp {
  template <typename Self> class Eq;
  template <typename Self> class Bounded;
  template <typename Self> class Ord;

  struct Ordering;
  enum order_t { LT, EQ, GT };
}

#include "fwdecl_types.hpp"
#include "crtp.hpp"

namespace hscpp {
  template <typename Self>
  class Eq : public CRTP<Self> {};

  template <typename Self>
  bool operator==(const Eq<Self> one, const Eq<Self> other) {
    return one.cast().eq(other);
  }

  template <typename Self>
  bool operator!=(const Eq<Self> one, const Eq<Self> other) {
    return !one.cast().eq(other);
  }

  template <typename Self>
  class Ord : Eq<Self> {
    static const Ordering &compare(const Self one, const Self other) { return one.cmp(other); }
    static const Self min(const Self one, const Self other) { return (one < other) ? one : other; }
    static const Self max(const Self one, const Self other) { return (one < other) ? other : one; }
  };

  template <typename Self>
  bool operator<(const Ord<Self> one, const Ord<Self> other) { return Ord<Self>::compare(one, other) == order_t::LT; }

  template <typename Self>
  bool operator>(const Ord<Self> one, const Ord<Self> other) { return Ord<Self>::compare(one, other) == order_t::GT; }

  template <typename Self>
  bool operator<=(const Ord<Self> one, const Ord<Self> other) { return Ord<Self>::compare(one, other) != order_t::GT; }

  template <typename Self>
  bool operator>=(const Ord<Self> one, const Ord<Self> other) { return Ord<Self>::compare(one, other) != order_t::LT; }

  template <typename Self>
  class Bounded : public CRTP<Self> {
  public:
    static Self minBound() { return Self::minBound(); }
    static Self maxBound() { return Self::maxBound(); }
  };

  template <typename Self>
  class Enum : public CRTP<Self> {
  public:
    static Self toEnum(const hsInt &value) { return Self::to(value); }
    const hsInt &fromEnum() const { return Self::from(*this); }
    const Self succ() const { return Enum<Self>::toEnum(fromEnum() + hsInt(1)); }
    const Self pred() const { return Enum<Self>::toEnum(fromEnum() - hsInt(1)); }
  };

  struct Ordering : public Ord<Ordering>, public Bounded<Ordering>, public Enum<Ordering> {
  public:
    const order_t value;
    Ordering(const order_t v) : value{v} {}

    static const Ordering LT;
    static const Ordering EQ;
    static const Ordering GT;

    operator order_t() const { return value; }
    bool eq(const Ordering &other) const;
    Ordering cmp(const Ordering &other) const;

    static Ordering minBound();
    static Ordering maxBound();

    static Ordering to(const hsInt &value);
    static hsInt from(const Ordering &value);
  };
}

#include "types.hpp"

#endif

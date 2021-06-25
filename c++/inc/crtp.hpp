#ifndef _HSCPP_CRTP
#define _HSCPP_CRTP

namespace hscpp {
  template <typename Self>
  class CRTP {
  public:
    operator Self() const { return static_cast<const Self &>(*this); }
    Self cast() const { return static_cast<const Self &>(*this); }
  };
}

#endif

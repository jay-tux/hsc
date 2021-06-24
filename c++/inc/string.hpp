#ifndef _HSCPP_STRING
#define _HSCPP_STRING

namespace hscpp {
  class hsString;
}

#include "types.hpp"
#include "list.hpp"
#include "showread.hpp"
#include <iostream>

namespace hscpp {
  class hsString : public List<hsChar>, public Show {
  public:
    hsString();
    hsString(const hsChar chr, const List<hsChar> next);

    static hsString fromString(const std::string str);
    static hsString fromList(const List<hsChar> lst);
    hsString show() const override;
  };

  class cppString : public Show {
  public:
    cppString();
    cppString(std::string s);

    hsString show() const override;

    const std::string value;
  };
}

hscpp::hsString operator+(const hscpp::hsString s1, const hscpp::hsString s2);
hscpp::hsString operator+(const hscpp::hsString s1, const std::string s2);
hscpp::hsString operator+(const std::string s1, const hscpp::hsString s2);
std::ostream &operator<<(std::ostream &strm, const hscpp::hsString string);

hscpp::cppString operator+(const hscpp::cppString s1, const hscpp::cppString s2);
std::ostream &operator<<(std::ostream &strm, const hscpp::cppString string);
#endif

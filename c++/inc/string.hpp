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

    static hsString fromString(std::string str);
    static hsString fromList(const List<hsChar> lst);
    hsString show() const override;
  };
}

std::ostream &operator<<(std::ostream &strm, const hscpp::hsString string);

#endif

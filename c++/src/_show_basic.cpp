#include "_show_basic.hpp"
#include <string>

using namespace hscpp;

template <typename t>
hsString showSimple(t val) {
  return hsString::fromString(std::to_string(val));
}

hsString hscpp::show(hsInt val) { return showSimple(val); }
hsString hscpp::show(hsInteger val) { return showSimple(val); }
hsString hscpp::show(hsBool val) { return showSimple(val); }
hsString hscpp::show(hsFloat val) { return showSimple(val); }
hsString hscpp::show(hsDouble val) { return showSimple(val); }
hsString hscpp::show(hsChar val) { return showSimple(val); }

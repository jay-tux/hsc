#include "string.hpp"

using namespace hscpp;

hsString::hsString() : List<hsChar>{} {}
hsString::hsString(const hsChar chr, const List<hsChar> next) : List<hsChar>{chr, next} {}

hsString hsString::fromString(std::string str) {
  if(str.length() == 0) return hsString();
  return hsString(hsChar(str[0]), fromString(str.substr(1)));
}

hsString hsString::fromList(const List<hsChar> lst) {
  return lst.value ? hsString(lst.value.value(), *lst.next) : hsString();
}

hsString hsString::show() const { return *this; }

std::ostream &operator<<(std::ostream &strm, const hscpp::hsString string) {
  if(!string.value) return strm;

  strm << (char)string.value.value();
  const hscpp::List<hscpp::hsChar> *curr = string.next;
  while(curr->value) {
    strm << curr->value.value();
    curr = curr->next;
  }
  return strm;
}

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

hsString operator+(const hsString s1, const hsString s2) {
  return hsString::fromList(List<hsChar>::append(s1, s2));
}

hsString operator+(const hsString s1, const std::string s2) {
  return hsString::fromList(List<hsChar>::append(s1, hsString::fromString(s2)));
}

hsString operator+(const std::string s1, const hsString s2) {
  return hsString::fromList(List<hsChar>::append(hsString::fromString(s1), s2));
}

cppString::cppString() : value{""} {}
cppString::cppString(std::string s) : value{s} {}
hsString cppString::show() const { return hsString::fromString(value); }

cppString operator+(const cppString s1, const cppString s2) { return cppString(s1.value + s2.value); }
cppString operator+(const cppString s1, const std::string s2) { return cppString(s1.value + s2); }
cppString operator+(const std::string s1, const cppString s2) { return cppString(s1 + s2.value); }
std::ostream &operator<<(std::ostream &strm, const cppString string) { return strm << string; }

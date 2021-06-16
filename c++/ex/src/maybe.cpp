#include "hscpp.hpp"
#include <iostream>

using namespace hscpp;

int main() {
  std::function<Maybe<hsInt>(hsInt, hsInt)> saveDiv = [](hsInt a, hsInt b) {
    return b == 0 ? Maybe<hsInt>() : Maybe<hsInt>(hsInt((int)a / (int)b));
  };

  std::function<hsInt(hsInt)> writer = [](hsInt a) {
    std::cout << "Result: " << show(a);
    return a;
  };

  std::function<Maybe<hsInt>(hsInt)> div12 = curry<Maybe<hsInt>, hsInt, hsInt>(saveDiv, hsInt(12));

  auto chain = [div12, writer](hsInt a) {
    std::cout << "Dividing 12 by " << show(a) << std::endl;
    std::cout << (Maybe<hsInt>(a).bind(div12).fmap(writer) ? "" : "No result") << std::endl;
  };

  hsInt num1(6), num2(18), num3(0);

  chain(num1);
  chain(num2);
  chain(num3);
}

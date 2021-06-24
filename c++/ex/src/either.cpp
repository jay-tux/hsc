#include "hscpp.hpp"
#include <iostream>

using namespace hscpp;

int main() {
  std::function<Either<hsChar, cppString>(hsInt)> nthCharacter = [](hsInt v) {
    return (int)v < 26 ? Either<hsChar, cppString>::right(hsChar('a' + (int)v)) :
      Either<hsChar, cppString>::left(cppString("Character should be < 26"));
  };

  std::function<hsString(hsChar)> conv = [](hsChar chr) { return show(chr); };

  auto chain = [nthCharacter, conv](hsInt a) {
    std::cout << "Getting n-th character: " << show(a) << std::endl;
    std::cout << Either<hsInt, cppString>::pure(a)
      .bind(nthCharacter).fmap(conv).show() << std::endl;;
  };

  hsInt num1(6), num2(0), num3(33);

  chain(num1);
  chain(num2);
  chain(num3);
}

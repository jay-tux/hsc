#include "hscpp.hpp"
#include <iostream>

using namespace hscpp;

int main() {
  hsInt a(1), b(2), c(3), d(4), e(5);

  auto addX = [](int x, hsInt a) -> hsInt { return hsInt(x + (int)a); };
  auto addOne = [addX](hsInt a) { return addX(1, a); };
  auto toChar = [](hsInt a) { return hsChar('0' + (int)a); };
  auto twice = [](hsInt a) {
    return List<hsInt>(a, List<hsInt>(a, List<hsInt>()));
  };

  List<hsInt> base(a, List<hsInt>(b, List<hsInt>(c, List<hsInt>(d, List<hsInt>(e, List<hsInt>())))));

  std::cout << hsString::fromList(
    base.fmap<hsInt>(addOne).bind<hsInt>(twice).fmap<hsChar>(toChar)
  ) << std::endl;
}

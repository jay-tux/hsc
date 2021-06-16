#include "hscpp.hpp"
#include <iostream>

using namespace hscpp;

int main() {
  std::function<Either<hsInt, hsString>(hsInt, hsInt)> saveDiv = [](hsInt a, hsInt b) {
    return b == 0 ? Either<hsInt, hsString>(hsString::fromString("Divide by 0")) :
                    Either<hsInt, hsString>(hsInt((int)a / (int)b));
  };

  std::function<hsInt(hsInt)> writer = [](hsInt a) {
    std::cout << "Result: " << show(a) << std::endl;
    return a;
  };
  std::function<Either<hsInt, hsString>(hsInt)> div12 = curry(saveDiv, hsInt(12));

  auto chain = [div12, writer](hsInt a) {
    std::cout << "Dividing 12 by " << show(a) << std::endl;
    Either<hsInt, hsString> res = Either<hsInt, hsString>(a).bind(div12).fmap(writer);
    if(res.isError) std::cout << res.value.err << std::endl;
  };

  hsInt num1(6), num2(18), num3(0);

  chain(num1);
  chain(num2);
  chain(num3);
}

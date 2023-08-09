// #include "include/functions.hpp"
#include "../include/cyfre.hpp"

using namespace cyfre;

int main() {
  constexpr size_t SIDE = 7;

  dynamic::allocate<int, 0, 0> f1(SIDE, SIDE);
  fixed<SIDE, SIDE>::allocate<int, SIDE, SIDE> d1;

  dynamic::allocate<int, 0, 0> d2(SIDE, SIDE);
  fixed<SIDE, SIDE>::allocate<int, SIDE, SIDE> f2;

  for (size_t i = 0; i < SIDE * SIDE; ++i) {
    f1[i] = f2[i] = d1[i] = d2[i] = 0;
  }

  f2[6 * 6] = 999;

  f1[0] = 888;
  d1 = f1;

  d1[2] = 777;
  f1 = d1;

  f1[4] = 111;
  f2 = f1;

  d1[5] = 333;
  d2 = d1;

  f1 = f1;
  d1 = d1;

  std::cout << "\nTests : PASSED - Allocators\n";
  return 0;
}
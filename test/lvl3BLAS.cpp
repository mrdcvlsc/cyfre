#include "include/functions.hpp"

using namespace cyfre;

int main() {
  std::mt19937 rng_engine(std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<unsigned int> rng(0, std::numeric_limits<unsigned char>::max());

  constexpr size_t ROWS = 5;
  constexpr size_t COLS = 6;

  cyfre::mat<unsigned int, fixed<ROWS, COLS>, order_t::row_major> AMFR;
  cyfre::mat<unsigned int, fixed<ROWS, COLS>, order_t::col_major> BMFC;
  cyfre::mat<unsigned int, dynamic, order_t::row_major> CMDR(ROWS, COLS);
  cyfre::mat<unsigned int, dynamic, order_t::col_major> CMDC(ROWS, COLS);

  for (size_t i = 0; i < ROWS; ++i) {
    for (size_t j = 0; j < COLS; ++j) {
      AMFR(i, j) = BMFC(i, j) = CMDR(i, j) = CMDC(i, j) = rng(rng_engine);
    }
  }

  // AMFR = BMFC + CMDC;

  std::cout << "Tests : PASSED - BLAS level 3\n";
  return 0;
}
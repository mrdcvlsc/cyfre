#include <cassert>
#include <iostream>
#include <chrono>
#include <limits>
#include <random>

#include "../include/cyfre.hpp"

using namespace cyfre;

int main() {
  {
    unsigned int seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937_64 engine(seed);
    std::uniform_int_distribution<int> rng(0, std::numeric_limits<int>::max());

    mat<int, fixed<7, 3>, order_t::row_major> matf7x3rmo;
    mat<int, dynamic, order_t::row_major> matd7x3rmo(7, 3);

    mat<int, fixed<7, 3>, order_t::col_major> matf7x3cmo;
    mat<int, dynamic, order_t::col_major> matd7x3cmo(7, 3);

    for (size_t i = 0; i < 7; ++i) {
      for (size_t j = 0; j < 3; ++j) {
        matf7x3rmo(i, j) = matd7x3rmo(i, j) = matf7x3cmo(i, j) = matd7x3cmo(i, j) = rng(engine);
      }
    }

    assert(matf7x3rmo == matd7x3rmo);
    assert(matf7x3rmo == matf7x3cmo);
    assert(matf7x3rmo == matd7x3cmo);

    assert(matd7x3rmo == matf7x3cmo);
    assert(matd7x3rmo == matd7x3cmo);

    assert(matf7x3cmo == matd7x3cmo);

    assert(matd7x3rmo == matf7x3rmo);
    assert(matf7x3cmo == matf7x3rmo);
    assert(matd7x3cmo == matf7x3rmo);

    assert(matf7x3cmo == matd7x3rmo);
    assert(matd7x3cmo == matd7x3rmo);

    assert(matd7x3cmo == matf7x3cmo);
  }

  {
    unsigned int seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937_64 engine(seed);
    std::uniform_int_distribution<int> rng(0, std::numeric_limits<int>::max());

    constexpr mat<int, fixed<7, 3>, order_t::row_major> matf7x3rmo = {
      {-111, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 1826382}, {13, 14, 15}, {16, 17, 18}, {19, 20, 21},
    };

    constexpr mat<int, fixed<7, 3>, order_t::col_major> matf7x3cmo = {
      {-111, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 1826382}, {13, 14, 15}, {16, 17, 18}, {19, 20, 21},
    };

    assert(matf7x3rmo == matf7x3cmo);
    assert(matf7x3cmo == matf7x3rmo);
  }
  std::cout << "Tests : PASSED - Matrix Major Order\n";
  return 0;
}
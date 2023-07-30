#include <cassert>
#include <iostream>
#include <chrono>
#include <limits>
#include <random>

#include "../include/cyfre.hpp"

using namespace cyfre;

int main() {
  {
    std::mt19937 rng_engine(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> rng(0, std::numeric_limits<int>::max());

    constexpr static size_t ROWS = 1;
    constexpr static size_t COLS = 2;

    vec<int, fixed<COLS>, axis_t::x> vec_faxis_x;
    vec<int, dynamic, axis_t::x> vec_daxis_x(COLS);
    mat<int, fixed<ROWS, COLS>, order_t::row_major> mat_faxis_x_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_x_rmo(ROWS, COLS);
    mat<int, fixed<ROWS, COLS>, order_t::col_major> mat_faxis_x_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_x_cmo(ROWS, COLS);

    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        vec_faxis_x(i, j) = vec_daxis_x(i, j) = mat_faxis_x_rmo(i, j) = mat_daxis_x_rmo(i, j) = mat_faxis_x_cmo(i, j) =
          mat_daxis_x_cmo(i, j) = rng(rng_engine);
      }
    }

    assert(vec_faxis_x == vec_faxis_x);
    assert(vec_faxis_x == vec_daxis_x);
    assert(vec_faxis_x == mat_faxis_x_rmo);
    assert(vec_faxis_x == mat_daxis_x_rmo);
    assert(vec_faxis_x == mat_faxis_x_cmo);
    assert(vec_faxis_x == mat_daxis_x_cmo);

    assert(vec_daxis_x == vec_daxis_x);
    assert(vec_daxis_x == mat_faxis_x_rmo);
    assert(vec_daxis_x == mat_daxis_x_rmo);
    assert(vec_daxis_x == mat_faxis_x_cmo);
    assert(vec_daxis_x == mat_daxis_x_cmo);

    assert(mat_faxis_x_rmo == mat_faxis_x_rmo);
    assert(mat_faxis_x_rmo == mat_daxis_x_rmo);
    assert(mat_faxis_x_rmo == mat_faxis_x_cmo);
    assert(mat_faxis_x_rmo == mat_daxis_x_cmo);

    assert(mat_daxis_x_rmo == mat_daxis_x_rmo);
    assert(mat_daxis_x_rmo == mat_faxis_x_cmo);
    assert(mat_daxis_x_rmo == mat_daxis_x_cmo);

    assert(mat_faxis_x_cmo == mat_faxis_x_cmo);
    assert(mat_faxis_x_cmo == mat_daxis_x_cmo);

    assert(mat_daxis_x_cmo == mat_daxis_x_cmo);

    assert(vec_faxis_x == vec_faxis_x);
    assert(vec_daxis_x == vec_faxis_x);
    assert(mat_faxis_x_rmo == vec_faxis_x);
    assert(mat_daxis_x_rmo == vec_faxis_x);
    assert(mat_faxis_x_cmo == vec_faxis_x);
    assert(mat_daxis_x_cmo == vec_faxis_x);

    assert(vec_daxis_x == vec_daxis_x);
    assert(mat_faxis_x_rmo == vec_daxis_x);
    assert(mat_daxis_x_rmo == vec_daxis_x);
    assert(mat_faxis_x_cmo == vec_daxis_x);
    assert(mat_daxis_x_cmo == vec_daxis_x);

    assert(mat_faxis_x_rmo == mat_faxis_x_rmo);
    assert(mat_daxis_x_rmo == mat_faxis_x_rmo);
    assert(mat_faxis_x_cmo == mat_faxis_x_rmo);
    assert(mat_daxis_x_cmo == mat_faxis_x_rmo);

    assert(mat_daxis_x_rmo == mat_daxis_x_rmo);
    assert(mat_faxis_x_cmo == mat_daxis_x_rmo);
    assert(mat_daxis_x_cmo == mat_daxis_x_rmo);

    assert(mat_faxis_x_cmo == mat_faxis_x_cmo);
    assert(mat_daxis_x_cmo == mat_faxis_x_cmo);

    assert(mat_daxis_x_cmo == mat_daxis_x_cmo);

    vec<int, fixed<COLS>, axis_t::y> vec_faxis_y;
    vec<int, dynamic, axis_t::y> vec_daxis_y(COLS);
    mat<int, fixed<COLS, ROWS>, order_t::row_major> mat_faxis_y_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_y_rmo(COLS, ROWS);
    mat<int, fixed<COLS, ROWS>, order_t::col_major> mat_faxis_y_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_y_cmo(COLS, ROWS);

    for (size_t i = 0; i < COLS; ++i) {
      for (size_t j = 0; j < ROWS; ++j) {
        vec_faxis_y(i, j) = vec_daxis_y(i, j) = mat_faxis_y_rmo(i, j) = mat_daxis_y_rmo(i, j) = mat_faxis_y_cmo(i, j) =
          mat_daxis_y_cmo(i, j) = rng(rng_engine);
      }
    }

    assert(vec_faxis_y == vec_faxis_y);
    assert(vec_faxis_y == vec_daxis_y);
    assert(vec_faxis_y == mat_faxis_y_rmo);
    assert(vec_faxis_y == mat_daxis_y_rmo);
    assert(vec_faxis_y == mat_faxis_y_cmo);
    assert(vec_faxis_y == mat_daxis_y_cmo);

    assert(vec_daxis_y == vec_daxis_y);
    assert(vec_daxis_y == mat_faxis_y_rmo);
    assert(vec_daxis_y == mat_daxis_y_rmo);
    assert(vec_daxis_y == mat_faxis_y_cmo);
    assert(vec_daxis_y == mat_daxis_y_cmo);

    assert(mat_faxis_y_rmo == mat_faxis_y_rmo);
    assert(mat_faxis_y_rmo == mat_daxis_y_rmo);
    assert(mat_faxis_y_rmo == mat_faxis_y_cmo);
    assert(mat_faxis_y_rmo == mat_daxis_y_cmo);

    assert(mat_daxis_y_rmo == mat_daxis_y_rmo);
    assert(mat_daxis_y_rmo == mat_faxis_y_cmo);
    assert(mat_daxis_y_rmo == mat_daxis_y_cmo);

    assert(mat_faxis_y_cmo == mat_faxis_y_cmo);
    assert(mat_faxis_y_cmo == mat_daxis_y_cmo);

    assert(mat_daxis_y_cmo == mat_daxis_y_cmo);

    assert(vec_faxis_y == vec_faxis_y);
    assert(vec_daxis_y == vec_faxis_y);
    assert(mat_faxis_y_rmo == vec_faxis_y);
    assert(mat_daxis_y_rmo == vec_faxis_y);
    assert(mat_faxis_y_cmo == vec_faxis_y);
    assert(mat_daxis_y_cmo == vec_faxis_y);

    assert(vec_daxis_y == vec_daxis_y);
    assert(mat_faxis_y_rmo == vec_daxis_y);
    assert(mat_daxis_y_rmo == vec_daxis_y);
    assert(mat_faxis_y_cmo == vec_daxis_y);
    assert(mat_daxis_y_cmo == vec_daxis_y);

    assert(mat_faxis_y_rmo == mat_faxis_y_rmo);
    assert(mat_daxis_y_rmo == mat_faxis_y_rmo);
    assert(mat_faxis_y_cmo == mat_faxis_y_rmo);
    assert(mat_daxis_y_cmo == mat_faxis_y_rmo);

    assert(mat_daxis_y_rmo == mat_daxis_y_rmo);
    assert(mat_faxis_y_cmo == mat_daxis_y_rmo);
    assert(mat_daxis_y_cmo == mat_daxis_y_rmo);

    assert(mat_faxis_y_cmo == mat_faxis_y_cmo);
    assert(mat_daxis_y_cmo == mat_faxis_y_cmo);

    assert(mat_daxis_y_cmo == mat_daxis_y_cmo);
  }

  {
    std::mt19937 rng_engine(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> rng(0, std::numeric_limits<int>::max());

    constexpr static size_t ROWS = 1;
    constexpr static size_t COLS = 3;

    vec<int, fixed<COLS>, axis_t::x> vec_faxis_x;
    vec<int, dynamic, axis_t::x> vec_daxis_x(COLS);
    mat<int, fixed<ROWS, COLS>, order_t::row_major> mat_faxis_x_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_x_rmo(ROWS, COLS);
    mat<int, fixed<ROWS, COLS>, order_t::col_major> mat_faxis_x_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_x_cmo(ROWS, COLS);

    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        vec_faxis_x(i, j) = vec_daxis_x(i, j) = mat_faxis_x_rmo(i, j) = mat_daxis_x_rmo(i, j) = mat_faxis_x_cmo(i, j) =
          mat_daxis_x_cmo(i, j) = rng(rng_engine);
      }
    }

    assert(vec_faxis_x == vec_faxis_x);
    assert(vec_faxis_x == vec_daxis_x);
    assert(vec_faxis_x == mat_faxis_x_rmo);
    assert(vec_faxis_x == mat_daxis_x_rmo);
    assert(vec_faxis_x == mat_faxis_x_cmo);
    assert(vec_faxis_x == mat_daxis_x_cmo);

    assert(vec_daxis_x == vec_daxis_x);
    assert(vec_daxis_x == mat_faxis_x_rmo);
    assert(vec_daxis_x == mat_daxis_x_rmo);
    assert(vec_daxis_x == mat_faxis_x_cmo);
    assert(vec_daxis_x == mat_daxis_x_cmo);

    assert(mat_faxis_x_rmo == mat_faxis_x_rmo);
    assert(mat_faxis_x_rmo == mat_daxis_x_rmo);
    assert(mat_faxis_x_rmo == mat_faxis_x_cmo);
    assert(mat_faxis_x_rmo == mat_daxis_x_cmo);

    assert(mat_daxis_x_rmo == mat_daxis_x_rmo);
    assert(mat_daxis_x_rmo == mat_faxis_x_cmo);
    assert(mat_daxis_x_rmo == mat_daxis_x_cmo);

    assert(mat_faxis_x_cmo == mat_faxis_x_cmo);
    assert(mat_faxis_x_cmo == mat_daxis_x_cmo);

    assert(mat_daxis_x_cmo == mat_daxis_x_cmo);

    assert(vec_faxis_x == vec_faxis_x);
    assert(vec_daxis_x == vec_faxis_x);
    assert(mat_faxis_x_rmo == vec_faxis_x);
    assert(mat_daxis_x_rmo == vec_faxis_x);
    assert(mat_faxis_x_cmo == vec_faxis_x);
    assert(mat_daxis_x_cmo == vec_faxis_x);

    assert(vec_daxis_x == vec_daxis_x);
    assert(mat_faxis_x_rmo == vec_daxis_x);
    assert(mat_daxis_x_rmo == vec_daxis_x);
    assert(mat_faxis_x_cmo == vec_daxis_x);
    assert(mat_daxis_x_cmo == vec_daxis_x);

    assert(mat_faxis_x_rmo == mat_faxis_x_rmo);
    assert(mat_daxis_x_rmo == mat_faxis_x_rmo);
    assert(mat_faxis_x_cmo == mat_faxis_x_rmo);
    assert(mat_daxis_x_cmo == mat_faxis_x_rmo);

    assert(mat_daxis_x_rmo == mat_daxis_x_rmo);
    assert(mat_faxis_x_cmo == mat_daxis_x_rmo);
    assert(mat_daxis_x_cmo == mat_daxis_x_rmo);

    assert(mat_faxis_x_cmo == mat_faxis_x_cmo);
    assert(mat_daxis_x_cmo == mat_faxis_x_cmo);

    assert(mat_daxis_x_cmo == mat_daxis_x_cmo);

    vec<int, fixed<COLS>, axis_t::y> vec_faxis_y;
    vec<int, dynamic, axis_t::y> vec_daxis_y(COLS);
    mat<int, fixed<COLS, ROWS>, order_t::row_major> mat_faxis_y_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_y_rmo(COLS, ROWS);
    mat<int, fixed<COLS, ROWS>, order_t::col_major> mat_faxis_y_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_y_cmo(COLS, ROWS);

    for (size_t i = 0; i < COLS; ++i) {
      for (size_t j = 0; j < ROWS; ++j) {
        vec_faxis_y(i, j) = vec_daxis_y(i, j) = mat_faxis_y_rmo(i, j) = mat_daxis_y_rmo(i, j) = mat_faxis_y_cmo(i, j) =
          mat_daxis_y_cmo(i, j) = rng(rng_engine);
      }
    }

    assert(vec_faxis_y == vec_faxis_y);
    assert(vec_faxis_y == vec_daxis_y);
    assert(vec_faxis_y == mat_faxis_y_rmo);
    assert(vec_faxis_y == mat_daxis_y_rmo);
    assert(vec_faxis_y == mat_faxis_y_cmo);
    assert(vec_faxis_y == mat_daxis_y_cmo);

    assert(vec_daxis_y == vec_daxis_y);
    assert(vec_daxis_y == mat_faxis_y_rmo);
    assert(vec_daxis_y == mat_daxis_y_rmo);
    assert(vec_daxis_y == mat_faxis_y_cmo);
    assert(vec_daxis_y == mat_daxis_y_cmo);

    assert(mat_faxis_y_rmo == mat_faxis_y_rmo);
    assert(mat_faxis_y_rmo == mat_daxis_y_rmo);
    assert(mat_faxis_y_rmo == mat_faxis_y_cmo);
    assert(mat_faxis_y_rmo == mat_daxis_y_cmo);

    assert(mat_daxis_y_rmo == mat_daxis_y_rmo);
    assert(mat_daxis_y_rmo == mat_faxis_y_cmo);
    assert(mat_daxis_y_rmo == mat_daxis_y_cmo);

    assert(mat_faxis_y_cmo == mat_faxis_y_cmo);
    assert(mat_faxis_y_cmo == mat_daxis_y_cmo);

    assert(mat_daxis_y_cmo == mat_daxis_y_cmo);

    assert(vec_faxis_y == vec_faxis_y);
    assert(vec_daxis_y == vec_faxis_y);
    assert(mat_faxis_y_rmo == vec_faxis_y);
    assert(mat_daxis_y_rmo == vec_faxis_y);
    assert(mat_faxis_y_cmo == vec_faxis_y);
    assert(mat_daxis_y_cmo == vec_faxis_y);

    assert(vec_daxis_y == vec_daxis_y);
    assert(mat_faxis_y_rmo == vec_daxis_y);
    assert(mat_daxis_y_rmo == vec_daxis_y);
    assert(mat_faxis_y_cmo == vec_daxis_y);
    assert(mat_daxis_y_cmo == vec_daxis_y);

    assert(mat_faxis_y_rmo == mat_faxis_y_rmo);
    assert(mat_daxis_y_rmo == mat_faxis_y_rmo);
    assert(mat_faxis_y_cmo == mat_faxis_y_rmo);
    assert(mat_daxis_y_cmo == mat_faxis_y_rmo);

    assert(mat_daxis_y_rmo == mat_daxis_y_rmo);
    assert(mat_faxis_y_cmo == mat_daxis_y_rmo);
    assert(mat_daxis_y_cmo == mat_daxis_y_rmo);

    assert(mat_faxis_y_cmo == mat_faxis_y_cmo);
    assert(mat_daxis_y_cmo == mat_faxis_y_cmo);

    assert(mat_daxis_y_cmo == mat_daxis_y_cmo);
  }

  {
    std::mt19937 rng_engine(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> rng(0, std::numeric_limits<int>::max());

    constexpr static size_t ROWS = 1;
    constexpr static size_t COLS = 50;

    vec<int, fixed<COLS>, axis_t::x> vec_faxis_x;
    vec<int, dynamic, axis_t::x> vec_daxis_x(COLS);
    mat<int, fixed<ROWS, COLS>, order_t::row_major> mat_faxis_x_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_x_rmo(ROWS, COLS);
    mat<int, fixed<ROWS, COLS>, order_t::col_major> mat_faxis_x_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_x_cmo(ROWS, COLS);

    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        vec_faxis_x(i, j) = vec_daxis_x(i, j) = mat_faxis_x_rmo(i, j) = mat_daxis_x_rmo(i, j) = mat_faxis_x_cmo(i, j) =
          mat_daxis_x_cmo(i, j) = rng(rng_engine);
      }
    }

    assert(vec_faxis_x == vec_faxis_x);
    assert(vec_faxis_x == vec_daxis_x);
    assert(vec_faxis_x == mat_faxis_x_rmo);
    assert(vec_faxis_x == mat_daxis_x_rmo);
    assert(vec_faxis_x == mat_faxis_x_cmo);
    assert(vec_faxis_x == mat_daxis_x_cmo);

    assert(vec_daxis_x == vec_daxis_x);
    assert(vec_daxis_x == mat_faxis_x_rmo);
    assert(vec_daxis_x == mat_daxis_x_rmo);
    assert(vec_daxis_x == mat_faxis_x_cmo);
    assert(vec_daxis_x == mat_daxis_x_cmo);

    assert(mat_faxis_x_rmo == mat_faxis_x_rmo);
    assert(mat_faxis_x_rmo == mat_daxis_x_rmo);
    assert(mat_faxis_x_rmo == mat_faxis_x_cmo);
    assert(mat_faxis_x_rmo == mat_daxis_x_cmo);

    assert(mat_daxis_x_rmo == mat_daxis_x_rmo);
    assert(mat_daxis_x_rmo == mat_faxis_x_cmo);
    assert(mat_daxis_x_rmo == mat_daxis_x_cmo);

    assert(mat_faxis_x_cmo == mat_faxis_x_cmo);
    assert(mat_faxis_x_cmo == mat_daxis_x_cmo);

    assert(mat_daxis_x_cmo == mat_daxis_x_cmo);

    assert(vec_faxis_x == vec_faxis_x);
    assert(vec_daxis_x == vec_faxis_x);
    assert(mat_faxis_x_rmo == vec_faxis_x);
    assert(mat_daxis_x_rmo == vec_faxis_x);
    assert(mat_faxis_x_cmo == vec_faxis_x);
    assert(mat_daxis_x_cmo == vec_faxis_x);

    assert(vec_daxis_x == vec_daxis_x);
    assert(mat_faxis_x_rmo == vec_daxis_x);
    assert(mat_daxis_x_rmo == vec_daxis_x);
    assert(mat_faxis_x_cmo == vec_daxis_x);
    assert(mat_daxis_x_cmo == vec_daxis_x);

    assert(mat_faxis_x_rmo == mat_faxis_x_rmo);
    assert(mat_daxis_x_rmo == mat_faxis_x_rmo);
    assert(mat_faxis_x_cmo == mat_faxis_x_rmo);
    assert(mat_daxis_x_cmo == mat_faxis_x_rmo);

    assert(mat_daxis_x_rmo == mat_daxis_x_rmo);
    assert(mat_faxis_x_cmo == mat_daxis_x_rmo);
    assert(mat_daxis_x_cmo == mat_daxis_x_rmo);

    assert(mat_faxis_x_cmo == mat_faxis_x_cmo);
    assert(mat_daxis_x_cmo == mat_faxis_x_cmo);

    assert(mat_daxis_x_cmo == mat_daxis_x_cmo);

    vec<int, fixed<COLS>, axis_t::y> vec_faxis_y;
    vec<int, dynamic, axis_t::y> vec_daxis_y(COLS);
    mat<int, fixed<COLS, ROWS>, order_t::row_major> mat_faxis_y_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_y_rmo(COLS, ROWS);
    mat<int, fixed<COLS, ROWS>, order_t::col_major> mat_faxis_y_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_y_cmo(COLS, ROWS);

    for (size_t i = 0; i < COLS; ++i) {
      for (size_t j = 0; j < ROWS; ++j) {
        vec_faxis_y(i, j) = vec_daxis_y(i, j) = mat_faxis_y_rmo(i, j) = mat_daxis_y_rmo(i, j) = mat_faxis_y_cmo(i, j) =
          mat_daxis_y_cmo(i, j) = rng(rng_engine);
      }
    }

    assert(vec_faxis_y == vec_faxis_y);
    assert(vec_faxis_y == vec_daxis_y);
    assert(vec_faxis_y == mat_faxis_y_rmo);
    assert(vec_faxis_y == mat_daxis_y_rmo);
    assert(vec_faxis_y == mat_faxis_y_cmo);
    assert(vec_faxis_y == mat_daxis_y_cmo);

    assert(vec_daxis_y == vec_daxis_y);
    assert(vec_daxis_y == mat_faxis_y_rmo);
    assert(vec_daxis_y == mat_daxis_y_rmo);
    assert(vec_daxis_y == mat_faxis_y_cmo);
    assert(vec_daxis_y == mat_daxis_y_cmo);

    assert(mat_faxis_y_rmo == mat_faxis_y_rmo);
    assert(mat_faxis_y_rmo == mat_daxis_y_rmo);
    assert(mat_faxis_y_rmo == mat_faxis_y_cmo);
    assert(mat_faxis_y_rmo == mat_daxis_y_cmo);

    assert(mat_daxis_y_rmo == mat_daxis_y_rmo);
    assert(mat_daxis_y_rmo == mat_faxis_y_cmo);
    assert(mat_daxis_y_rmo == mat_daxis_y_cmo);

    assert(mat_faxis_y_cmo == mat_faxis_y_cmo);
    assert(mat_faxis_y_cmo == mat_daxis_y_cmo);

    assert(mat_daxis_y_cmo == mat_daxis_y_cmo);

    assert(vec_faxis_y == vec_faxis_y);
    assert(vec_daxis_y == vec_faxis_y);
    assert(mat_faxis_y_rmo == vec_faxis_y);
    assert(mat_daxis_y_rmo == vec_faxis_y);
    assert(mat_faxis_y_cmo == vec_faxis_y);
    assert(mat_daxis_y_cmo == vec_faxis_y);

    assert(vec_daxis_y == vec_daxis_y);
    assert(mat_faxis_y_rmo == vec_daxis_y);
    assert(mat_daxis_y_rmo == vec_daxis_y);
    assert(mat_faxis_y_cmo == vec_daxis_y);
    assert(mat_daxis_y_cmo == vec_daxis_y);

    assert(mat_faxis_y_rmo == mat_faxis_y_rmo);
    assert(mat_daxis_y_rmo == mat_faxis_y_rmo);
    assert(mat_faxis_y_cmo == mat_faxis_y_rmo);
    assert(mat_daxis_y_cmo == mat_faxis_y_rmo);

    assert(mat_daxis_y_rmo == mat_daxis_y_rmo);
    assert(mat_faxis_y_cmo == mat_daxis_y_rmo);
    assert(mat_daxis_y_cmo == mat_daxis_y_rmo);

    assert(mat_faxis_y_cmo == mat_faxis_y_cmo);
    assert(mat_daxis_y_cmo == mat_faxis_y_cmo);

    assert(mat_daxis_y_cmo == mat_daxis_y_cmo);
  }

  std::cout << "\nTests : PASSED - Vector Initializations\n";
  return 0;
}
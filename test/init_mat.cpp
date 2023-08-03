#include "include/functions.hpp"

using namespace cyfre;

int main() {
  {
    std::mt19937 rng_engine(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> rng(0, std::numeric_limits<int>::max());

    constexpr static size_t ROWS = 2;
    constexpr static size_t COLS = 2;

    mat<int, fixed<ROWS, COLS>, order_t::row_major> mat_faxis_x_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_x_rmo(ROWS, COLS);
    mat<int, fixed<ROWS, COLS>, order_t::col_major> mat_faxis_x_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_x_cmo(ROWS, COLS);

    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        mat_faxis_x_rmo(i, j) = mat_daxis_x_rmo(i, j) = mat_faxis_x_cmo(i, j) = mat_daxis_x_cmo(i, j) = rng(rng_engine);
      }
    }

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

    mat<int, fixed<COLS, ROWS>, order_t::row_major> mat_faxis_y_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_y_rmo(COLS, ROWS);
    mat<int, fixed<COLS, ROWS>, order_t::col_major> mat_faxis_y_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_y_cmo(COLS, ROWS);

    for (size_t i = 0; i < COLS; ++i) {
      for (size_t j = 0; j < ROWS; ++j) {
        mat_faxis_y_rmo(i, j) = mat_daxis_y_rmo(i, j) = mat_faxis_y_cmo(i, j) = mat_daxis_y_cmo(i, j) = rng(rng_engine);
      }
    }

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

    constexpr static size_t ROWS = 3;
    constexpr static size_t COLS = 3;

    mat<int, fixed<ROWS, COLS>, order_t::row_major> mat_faxis_x_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_x_rmo(ROWS, COLS);
    mat<int, fixed<ROWS, COLS>, order_t::col_major> mat_faxis_x_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_x_cmo(ROWS, COLS);

    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        mat_faxis_x_rmo(i, j) = mat_daxis_x_rmo(i, j) = mat_faxis_x_cmo(i, j) = mat_daxis_x_cmo(i, j) = rng(rng_engine);
      }
    }

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

    mat<int, fixed<COLS, ROWS>, order_t::row_major> mat_faxis_y_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_y_rmo(COLS, ROWS);
    mat<int, fixed<COLS, ROWS>, order_t::col_major> mat_faxis_y_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_y_cmo(COLS, ROWS);

    for (size_t i = 0; i < COLS; ++i) {
      for (size_t j = 0; j < ROWS; ++j) {
        mat_faxis_y_rmo(i, j) = mat_daxis_y_rmo(i, j) = mat_faxis_y_cmo(i, j) = mat_daxis_y_cmo(i, j) = rng(rng_engine);
      }
    }

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

    constexpr static size_t ROWS = 4;
    constexpr static size_t COLS = 7;

    mat<int, fixed<ROWS, COLS>, order_t::row_major> mat_faxis_x_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_x_rmo(ROWS, COLS);
    mat<int, fixed<ROWS, COLS>, order_t::col_major> mat_faxis_x_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_x_cmo(ROWS, COLS);

    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        mat_faxis_x_rmo(i, j) = mat_daxis_x_rmo(i, j) = mat_faxis_x_cmo(i, j) = mat_daxis_x_cmo(i, j) = rng(rng_engine);
      }
    }

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

    mat<int, fixed<COLS, ROWS>, order_t::row_major> mat_faxis_y_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_y_rmo(COLS, ROWS);
    mat<int, fixed<COLS, ROWS>, order_t::col_major> mat_faxis_y_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_y_cmo(COLS, ROWS);

    for (size_t i = 0; i < COLS; ++i) {
      for (size_t j = 0; j < ROWS; ++j) {
        mat_faxis_y_rmo(i, j) = mat_daxis_y_rmo(i, j) = mat_faxis_y_cmo(i, j) = mat_daxis_y_cmo(i, j) = rng(rng_engine);
      }
    }

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

    constexpr static size_t ROWS = 310;
    constexpr static size_t COLS = 50;

    mat<int, fixed<ROWS, COLS>, order_t::row_major> mat_faxis_x_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_x_rmo(ROWS, COLS);
    mat<int, fixed<ROWS, COLS>, order_t::col_major> mat_faxis_x_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_x_cmo(ROWS, COLS);

    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        mat_faxis_x_rmo(i, j) = mat_daxis_x_rmo(i, j) = mat_faxis_x_cmo(i, j) = mat_daxis_x_cmo(i, j) = rng(rng_engine);
      }
    }

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

    mat<int, fixed<COLS, ROWS>, order_t::row_major> mat_faxis_y_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_y_rmo(COLS, ROWS);
    mat<int, fixed<COLS, ROWS>, order_t::col_major> mat_faxis_y_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_y_cmo(COLS, ROWS);

    for (size_t i = 0; i < COLS; ++i) {
      for (size_t j = 0; j < ROWS; ++j) {
        mat_faxis_y_rmo(i, j) = mat_daxis_y_rmo(i, j) = mat_faxis_y_cmo(i, j) = mat_daxis_y_cmo(i, j) = rng(rng_engine);
      }
    }

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

    constexpr static size_t ROWS = 6;
    constexpr static size_t COLS = 71;

    mat<int, fixed<ROWS, COLS>, order_t::row_major> mat_faxis_x_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_x_rmo(ROWS, COLS);
    mat<int, fixed<ROWS, COLS>, order_t::col_major> mat_faxis_x_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_x_cmo(ROWS, COLS);

    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        mat_faxis_x_rmo(i, j) = mat_daxis_x_rmo(i, j) = mat_faxis_x_cmo(i, j) = mat_daxis_x_cmo(i, j) = rng(rng_engine);
      }
    }

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

    mat<int, fixed<COLS, ROWS>, order_t::row_major> mat_faxis_y_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_y_rmo(COLS, ROWS);
    mat<int, fixed<COLS, ROWS>, order_t::col_major> mat_faxis_y_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_y_cmo(COLS, ROWS);

    for (size_t i = 0; i < COLS; ++i) {
      for (size_t j = 0; j < ROWS; ++j) {
        mat_faxis_y_rmo(i, j) = mat_daxis_y_rmo(i, j) = mat_faxis_y_cmo(i, j) = mat_daxis_y_cmo(i, j) = rng(rng_engine);
      }
    }

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

    constexpr static size_t ROWS = 100;
    constexpr static size_t COLS = 100;

    mat<int, fixed<ROWS, COLS>, order_t::row_major> mat_faxis_x_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_x_rmo(ROWS, COLS);
    mat<int, fixed<ROWS, COLS>, order_t::col_major> mat_faxis_x_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_x_cmo(ROWS, COLS);

    for (size_t i = 0; i < ROWS; ++i) {
      for (size_t j = 0; j < COLS; ++j) {
        mat_faxis_x_rmo(i, j) = mat_daxis_x_rmo(i, j) = mat_faxis_x_cmo(i, j) = mat_daxis_x_cmo(i, j) = rng(rng_engine);
      }
    }

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

    mat<int, fixed<COLS, ROWS>, order_t::row_major> mat_faxis_y_rmo;
    mat<int, dynamic, order_t::row_major> mat_daxis_y_rmo(COLS, ROWS);
    mat<int, fixed<COLS, ROWS>, order_t::col_major> mat_faxis_y_cmo;
    mat<int, dynamic, order_t::col_major> mat_daxis_y_cmo(COLS, ROWS);

    for (size_t i = 0; i < COLS; ++i) {
      for (size_t j = 0; j < ROWS; ++j) {
        mat_faxis_y_rmo(i, j) = mat_daxis_y_rmo(i, j) = mat_faxis_y_cmo(i, j) = mat_daxis_y_cmo(i, j) = rng(rng_engine);
      }
    }

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

  std::cout << "\nTests : PASSED - Matrix Initializations\n";
  return 0;
}
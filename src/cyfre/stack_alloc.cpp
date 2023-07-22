#ifndef MRDCVLSC_STACK_ALLOCATION_CPP
#define MRDCVLSC_STACK_ALLOCATION_CPP

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "../../include/cyfre/stack_alloc.hpp"

namespace cyfre {
  template <typename T, size_t ROWS, size_t COLS>
  fixed<T, ROWS, COLS>::fixed() : matrix() {
  }

  /// @brief Copy Constructor.
  template <typename T, size_t ROWS, size_t COLS>
  fixed<T, ROWS, COLS>::fixed(fixed<T, ROWS, COLS> const &that) : matrix(new T[that.rows * that.cols]) {
    memcpy(matrix, that.matrix, that.rows * that.cols);
  }

  /// @brief Move Constructor.
  template <typename T, size_t ROWS, size_t COLS>
  fixed<T, ROWS, COLS>::fixed(fixed<T, ROWS, COLS> &&that) : matrix(that.matrix) {
    memcpy(matrix, that.matrix, that.rows * that.cols);
  }

  /// @brief Copy Assignment
  template <typename T, size_t ROWS, size_t COLS>
  fixed<T, ROWS, COLS> &fixed<T, ROWS, COLS>::operator=(fixed<T, ROWS, COLS> const &that) {
    if (this != &that) {
      memcpy(matrix, that.matrix, that.rows * that.cols);
    }
    return *this;
  }

  /// @brief Move Assignment
  template <typename T, size_t ROWS, size_t COLS>
  fixed<T, ROWS, COLS> &fixed<T, ROWS, COLS>::operator=(fixed<T, ROWS, COLS> &&that) {
    if (this != &that) {
      memcpy(matrix, that.matrix, that.rows * that.cols);
    }
    return *this;
  }
} // namespace cyfre

#endif
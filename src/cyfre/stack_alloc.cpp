#ifndef MRDCVLSC_STACK_ALLOCATION_CPP
#define MRDCVLSC_STACK_ALLOCATION_CPP

#include <stddef.h>
#include <assert.h>

#include "../../include/cyfre/stack_alloc.hpp"
#include "../../include/cyfre/type_checks.hpp"

namespace cyfre {
  template <size_t ROWS, size_t COLS>
  template <typename T, size_t Rows, size_t Cols>
  fixed<ROWS, COLS>::allocate<T, Rows, Cols>::allocate() : matrix() {
  }

  template <size_t ROWS, size_t COLS>
  template <typename T, size_t Rows, size_t Cols>
  fixed<ROWS, COLS>::allocate<T, Rows, Cols>::allocate(fixed<ROWS, COLS>::allocate<T, Rows, Cols> const &that)
      : allocate(that.rows, that.cols) { // or even better try this
    memcpy(matrix, that.matrix, sizeof(T) * that.rows * that.cols);
  }

  template <size_t ROWS, size_t COLS>
  template <typename T, size_t Rows, size_t Cols>
  typename fixed<ROWS, COLS>::template allocate<T, Rows, Cols> &fixed<ROWS, COLS>::allocate<T, Rows, Cols>::operator=(
    const fixed<ROWS, COLS>::allocate<T, Rows, Cols> &that
  ) {
    if (this != &that) {
      memcpy(matrix, that.matrix, sizeof(T) * that.rows * that.cols);
    }
    return *this;
  }

  template <size_t ROWS, size_t COLS>
  template <typename T, size_t Rows, size_t Cols>
  constexpr T &fixed<ROWS, COLS>::allocate<T, Rows, Cols>::operator[](size_t i) {
    return matrix[i];
  }

  template <size_t ROWS, size_t COLS>
  template <typename T, size_t Rows, size_t Cols>
  constexpr const T &fixed<ROWS, COLS>::allocate<T, Rows, Cols>::operator[](size_t i) const {
    return matrix[i];
  }
} // namespace cyfre

#endif
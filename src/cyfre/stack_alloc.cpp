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
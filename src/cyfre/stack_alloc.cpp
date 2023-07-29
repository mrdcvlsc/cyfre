#ifndef MRDCVLSC_STACK_ALLOCATION_CPP
#define MRDCVLSC_STACK_ALLOCATION_CPP

#include "../../include/cyfre/stack_alloc.hpp"
#include <cstddef>

namespace cyfre {
  template <size_t Rows, size_t Cols>
  template <typename _T, size_t _Rows, size_t _Cols>
  constexpr fixed<Rows, Cols>::allocate<_T, _Rows, _Cols>::allocate() : matrix() {}

  template <size_t Rows, size_t Cols>
  template <typename _T, size_t _Rows, size_t _Cols>
  constexpr fixed<Rows, Cols>::allocate<_T, _Rows, _Cols>::allocate(size_t, size_t) : matrix() {}

  template <size_t Rows, size_t Cols>
  template <typename _T, size_t _Rows, size_t _Cols>
  constexpr fixed<Rows, Cols>::allocate<_T, _Rows, _Cols>::allocate(
    fixed<Rows, Cols>::allocate<_T, _Rows, _Cols> const &that
  )
      : allocate() { // or even better try this
    // maintain this comment for the future, still finding a way to enable memcpy if the call is not constexpr.
    // memcpy(matrix, that.matrix, sizeof(T) * that.rows * that.cols);
    for (size_t i = 0; i < _Rows * _Cols; ++i) {
      matrix[i] = that.matrix[i];
    }
  }

  template <size_t Rows, size_t Cols>
  template <typename _T, size_t _Rows, size_t _Cols>
  constexpr typename fixed<Rows, Cols>::template allocate<_T, _Rows, _Cols>
    &fixed<Rows, Cols>::allocate<_T, _Rows, _Cols>::operator=(const fixed<Rows, Cols>::allocate<_T, _Rows, _Cols> &that
    ) {
    if (this != &that) {
      // maintain this comment for the future, still finding a way to enable memcpy if the call is not constexpr.
      // memcpy(matrix, that.matrix, sizeof(T) * that.rows * that.cols);
      for (size_t i = 0; i < _Rows * _Cols; ++i) {
        matrix[i] = that.matrix[i];
      }
    }
    return *this;
  }

  template <size_t Rows, size_t Cols>
  template <typename _T, size_t _Rows, size_t _Cols>
  constexpr _T &fixed<Rows, Cols>::allocate<_T, _Rows, _Cols>::operator[](size_t i) {
    return matrix[i];
  }

  template <size_t Rows, size_t Cols>
  template <typename _T, size_t _Rows, size_t _Cols>
  constexpr const _T &fixed<Rows, Cols>::allocate<_T, _Rows, _Cols>::operator[](size_t i) const {
    return matrix[i];
  }
} // namespace cyfre

#endif
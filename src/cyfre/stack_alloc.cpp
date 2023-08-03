#ifndef MRDCVLSC_STACK_ALLOCATION_CPP
#define MRDCVLSC_STACK_ALLOCATION_CPP

#ifndef CYFRE_ALLOC_TEMP
  #define CYFRE_ALLOC_TEMP                                                                                             \
    template <size_t Rows, size_t Cols>                                                                                \
    template <typename _T, size_t _Rows, size_t _Cols>
#endif
#define CYFRE_FIXED fixed<Rows, Cols>::allocate<_T, _Rows, _Cols>
#define CYFRE_FIXED_ALLOC typename fixed<Rows, Cols>::template allocate<_T, _Rows, _Cols>

#include "../../include/cyfre/stack_alloc.hpp"

#include <cstddef>

namespace cyfre {

  CYFRE_ALLOC_TEMP constexpr CYFRE_FIXED::allocate() : matrix() {}

  CYFRE_ALLOC_TEMP constexpr CYFRE_FIXED::allocate(size_t, size_t) : matrix() {}

  CYFRE_ALLOC_TEMP constexpr CYFRE_FIXED::allocate(CYFRE_FIXED const &that) : allocate() {
    for (size_t i = 0; i < _Rows * _Cols; ++i) {
      matrix[i] = that.matrix[i];
    }
  }

  CYFRE_ALLOC_TEMP constexpr CYFRE_FIXED_ALLOC &CYFRE_FIXED::operator=(const CYFRE_FIXED &that) {
    if (this != &that) {
      for (size_t i = 0; i < _Rows * _Cols; ++i) {
        matrix[i] = that.matrix[i];
      }
    }
    return *this;
  }

  CYFRE_ALLOC_TEMP constexpr _T &CYFRE_FIXED::operator[](size_t i) { return matrix[i]; }

  CYFRE_ALLOC_TEMP constexpr const _T &CYFRE_FIXED::operator[](size_t i) const { return matrix[i]; }
} // namespace cyfre

#endif
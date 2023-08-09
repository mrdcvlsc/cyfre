#ifndef MRDCVLSC_STACK_ALLOCATION_CPP
#define MRDCVLSC_STACK_ALLOCATION_CPP

#include "../../include/cyfre/heap_alloc.hpp"
#include "../../include/cyfre/stack_alloc.hpp"

#include <cstddef>
#include <cassert>
#include <stdexcept>
#include <type_traits>

#define CYFRE_FIXED_CHECK_DYNAMIC dynamic::allocate<_T, 0, 0>

#ifndef CYFRE_ALLOC_TEMP
  #define CYFRE_ALLOC_TEMP                                                                                             \
    template <size_t Rows, size_t Cols>                                                                                \
    template <typename _T, size_t _Rows, size_t _Cols>
#endif

#ifndef CYFRE_ALLOC_TEMP_AllocatorT
  #define CYFRE_ALLOC_TEMP_AllocatorT CYFRE_ALLOC_TEMP template <concepts::allocators AllocatorT>
#endif

#define CYFRE_FIXED fixed<Rows, Cols>::allocate<_T, _Rows, _Cols>
#define CYFRE_FIXED_ALLOC typename fixed<Rows, Cols>::template allocate<_T, _Rows, _Cols>

namespace cyfre {

  /// Stack Alloc Constructor.
  CYFRE_ALLOC_TEMP constexpr CYFRE_FIXED::allocate() : matrix() {}

  /// Stack Alloc Constructor, function arguments has not effect to dimension, implemented only for completion.
  CYFRE_ALLOC_TEMP constexpr CYFRE_FIXED::allocate(size_t, size_t) : matrix() {}

  /// @brief Copy Constructor.
  CYFRE_ALLOC_TEMP constexpr CYFRE_FIXED::allocate(allocate const &that) : allocate() {
    for (size_t i = 0; i < _Rows * _Cols; ++i) {
      matrix[i] = that.matrix[i];
    }
  }

  /// @brief Move Constructor.
  CYFRE_ALLOC_TEMP CYFRE_FIXED::allocate(allocate &&that) : allocate() {
    for (size_t i = 0; i < _Rows * _Cols; ++i) {
      matrix[i] = std::move(that.matrix[i]);
    }
  }

  /// @brief Copy Assignment.
  CYFRE_ALLOC_TEMP constexpr CYFRE_FIXED_ALLOC &CYFRE_FIXED::operator=(allocate const &that) {
    if (this != &that) {
      for (size_t i = 0; i < _Rows * _Cols; ++i) {
        matrix[i] = that.matrix[i];
      }
    }

    return *this;
  }

  /// @brief Move Assignment.
  CYFRE_ALLOC_TEMP CYFRE_FIXED_ALLOC &CYFRE_FIXED::operator=(allocate &&that) {
    if (this != &that) {
      for (size_t i = 0; i < _Rows * _Cols; ++i) {
        matrix[i] = std::move(that.matrix[i]);
      }
    }

    return *this;
  }

  /// @brief Copy Constructor For Other Types.
  CYFRE_ALLOC_TEMP_AllocatorT constexpr CYFRE_FIXED::allocate(AllocatorT const &that) : allocate() {
    for (size_t i = 0; i < _Rows * _Cols; ++i) {
      matrix[i] = that.matrix[i];
    }
  }

  /// @brief Move Constructor For Other Types.
  CYFRE_ALLOC_TEMP_AllocatorT CYFRE_FIXED::allocate(AllocatorT &&that) : allocate() {
    for (size_t i = 0; i < that.rows * that.cols; ++i) {
      matrix[i] = std::move(that.matrix[i]);
    }
  }

  /// @brief Copy Assignment For Other Types.
  CYFRE_ALLOC_TEMP_AllocatorT constexpr CYFRE_FIXED_ALLOC &CYFRE_FIXED::operator=(AllocatorT const &that) {
    for (size_t i = 0; i < _Rows * _Cols; ++i) {
      matrix[i] = that.matrix[i];
    }

    return *this;
  }

  /// @brief Move Assignment For Other Types.
  CYFRE_ALLOC_TEMP_AllocatorT CYFRE_FIXED_ALLOC &CYFRE_FIXED::operator=(AllocatorT &&that) {
    for (size_t i = 0; i < _Rows * _Cols; ++i) {
      matrix[i] = std::move(that.matrix[i]);
    }

    return *this;
  }

  CYFRE_ALLOC_TEMP constexpr _T &CYFRE_FIXED::operator[](size_t i) { return matrix[i]; }

  CYFRE_ALLOC_TEMP constexpr const _T &CYFRE_FIXED::operator[](size_t i) const { return matrix[i]; }
} // namespace cyfre

#endif
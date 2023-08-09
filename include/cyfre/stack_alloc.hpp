/**
 *  @file   stack_alloc.hpp
 *  @brief  Stack Allocator Meta Functions and Class.
 *  @author mrdcvlsc
 ***********************************************/

#ifndef MRDCVLSC_STACK_ALLOC_HPP
#define MRDCVLSC_STACK_ALLOC_HPP

#include <stddef.h>
#include "concepts.hpp"

namespace cyfre {

  /// @brief stack allocator meta-function for the matrix class.
  /// @tparam ROWS fixed height of the matrix.
  /// @tparam COLS fixed width of the matrix - defaults to 1 if not specified to enable 1 argument pass in the vec<>
  /// class.
  template <size_t Rows, size_t Cols = 1>
  struct fixed {
    static constexpr size_t rows = Rows;
    static constexpr size_t cols = Cols;

    /// @brief stack allocator type for the matrix class.
    /// @tparam T the type of the scalar values/elements of the matrix.
    /// @tparam Rows fixed height of the matrix.
    /// @tparam Cols fixed width of the matrix.
    template <typename _T, size_t _Rows, size_t _Cols>
    struct allocate {
      static constexpr size_t rows = _Rows;
      static constexpr size_t cols = _Cols;

      _T matrix[_Rows * _Cols];

      constexpr allocate();

      /// @note This constructor is only implemented for the sake of completion,
      /// the constructor parameter rows and cols has no effect to the actual
      /// size of the fixed matrix on stack.
      constexpr allocate(size_t, size_t);

      /// @brief Copy Constructor.
      constexpr allocate(const allocate &that);

      /// @brief Move Constructor.
      allocate(allocate &&that);

      /// @brief Copy Assignment.
      constexpr allocate &operator=(const allocate &that);

      /// @brief Move Assignment.
      allocate &operator=(allocate &&that);

      /// @brief Copy Constructor For Other Types.
      template <concepts::allocators AllocatorT>
      constexpr allocate(const AllocatorT &that);

      /// @brief Move Constructor For Other Types.
      template <concepts::allocators AllocatorT>
      allocate(AllocatorT &&that);

      /// @brief Copy Assignment For Other Types.
      template <concepts::allocators AllocatorT>
      constexpr allocate &operator=(const AllocatorT &that);

      /// @brief Move Assignment For Other Types.
      template <concepts::allocators AllocatorT>
      allocate &operator=(AllocatorT &&that);

      constexpr _T &operator[](size_t i);
      constexpr const _T &operator[](size_t i) const;
    };
  };
} // namespace cyfre

#endif
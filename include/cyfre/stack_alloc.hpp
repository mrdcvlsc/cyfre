/**
 *  @file   stack_alloc.hpp
 *  @brief  Stack Allocator Meta Functions and Class.
 *  @author mrdcvlsc
 ***********************************************/

#ifndef MRDCVLSC_STACK_ALLOC_HPP
#define MRDCVLSC_STACK_ALLOC_HPP

#include <stddef.h>

namespace cyfre {

  /// @brief stack allocator meta-function for the matrix class.
  /// @tparam ROWS fixed height of the matrix.
  /// @tparam COLS fixed width of the matrix.
  template <size_t Rows, size_t Cols>
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

      /// @brief Copy Constructor.
      constexpr allocate(const allocate &that);

      /// @brief Copy Assignment.
      constexpr allocate &operator=(const allocate &that);

      constexpr _T &operator[](size_t i);
      constexpr const _T &operator[](size_t i) const;
    };
  };

} // namespace cyfre

#endif
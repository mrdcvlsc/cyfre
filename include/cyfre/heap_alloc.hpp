/**
 *  @file   heap_alloc.hpp
 *  @brief  Heap Allocator Meta Functions and Class.
 *  @author mrdcvlsc
 ***********************************************/

#ifndef MRDCVLSC_HEAP_ALLOC_HPP
#define MRDCVLSC_HEAP_ALLOC_HPP

#include <stddef.h>

namespace cyfre {

  namespace backend {
    /// @brief heap allocator meta-function for the matrix class (raw no typedef).
    template <size_t Rows = 0, size_t Cols = 0>
    struct dynamic {
      static constexpr size_t rows = Rows;
      static constexpr size_t cols = Cols;

      /// @brief stack allocator type for the matrix class.
      /// @tparam T the type of the scalar values/elements of the matrix.
      /// @tparam Rows fixed height of the matrix.
      /// @tparam Cols fixed width of the matrix.
      template <typename _T, size_t _Rows, size_t _Cols>
      struct allocate {
        _T *matrix;
        size_t rows;
        size_t cols;

        allocate(size_t rows, size_t cols);

        ~allocate();

        /// @brief Copy Constructor.
        allocate(const allocate &that);

        /// @brief Move Constructor.
        allocate(allocate &&that);

        /// @brief Copy Assignment.
        allocate &operator=(const allocate &that);

        /// @brief Move Assignment.
        allocate &operator=(allocate &&that);

        inline _T &operator[](size_t i);
        inline const _T &operator[](size_t i) const;
      };
    };
  } // namespace backend

  /// @brief heap allocator meta-function for the matrix class.
  typedef backend::dynamic<0, 0> dynamic;
} // namespace cyfre

#endif
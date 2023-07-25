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
    template <size_t ROWS = 0, size_t COLS = 0>
    struct dynamic {
      static constexpr size_t rows = ROWS;
      static constexpr size_t cols = COLS;

      /// @brief stack allocator type for the matrix class.
      /// @tparam T the type of the scalar values/elements of the matrix.
      /// @tparam Rows fixed height of the matrix.
      /// @tparam Cols fixed width of the matrix.
      template <typename T, size_t Rows, size_t Cols>
      struct allocate {
        T *matrix;
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

        inline T &operator[](size_t i);
        inline const T &operator[](size_t i) const;
      };
    };
  } // namespace backend

  /// @brief heap allocator meta-function for the matrix class.
  typedef backend::dynamic<0, 0> dynamic;
} // namespace cyfre

#endif
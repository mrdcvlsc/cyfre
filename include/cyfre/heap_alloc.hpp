#ifndef MRDCVLSC_HEAP_ALLOC_HPP
#define MRDCVLSC_HEAP_ALLOC_HPP

#include <stddef.h>

namespace cyfre {

  template <typename T>
  struct dynamic {
    T *matrix;
    size_t rows;
    size_t cols;

    dynamic(size_t rows, size_t cols);

    ~dynamic();

    /// @brief Copy Constructor.
    dynamic(const dynamic &that);

    /// @brief Move Constructor.
    dynamic(dynamic &&that);

    /// @brief Copy Assignment.
    dynamic &operator=(const dynamic &that);

    /// @brief Move Assignment.
    dynamic &operator=(dynamic &&that);
  };

} // namespace cyfre

#endif
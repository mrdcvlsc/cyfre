#ifndef MRDCVLSC_STACK_ALLOC_HPP
#define MRDCVLSC_STACK_ALLOC_HPP

#include <stddef.h>

namespace cyfre {

  template <typename T, size_t ROWS, size_t COLS>
  class fixed {
    private:

    T matrix[COLS * ROWS];

    public:

    fixed();

    /// @brief Copy Constructor.
    fixed(const fixed &that);

    /// @brief Move Constructor.
    fixed(fixed &&that);

    /// @brief Copy Assignment.
    fixed &operator=(const fixed &that);

    /// @brief Move Assignment.
    fixed &operator=(fixed &&that);
  };

} // namespace cyfre

#endif
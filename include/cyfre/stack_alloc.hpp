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
  };

} // namespace cyfre

#endif
#ifndef MRDCVLSC_STACK_ALLOCATION_CPP
#define MRDCVLSC_STACK_ALLOCATION_CPP

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <type_traits>

#include "../../include/cyfre/check_operators.hpp"
#include "../../include/cyfre/stack_alloc.hpp"

namespace cyfre {
  template <typename T, size_t ROWS, size_t COLS>
  fixed<T, ROWS, COLS>::fixed() : matrix() {
    static_assert(!valid_operators<T>::value, "mat<T,...> type 'T' does not support the necessary operators");
  }
} // namespace cyfre

#endif
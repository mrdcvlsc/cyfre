#ifndef MRDCVLSC_MATRIX_CLASS_CPP
#define MRDCVLSC_MATRIX_CLASS_CPP

#include "../../include/cyfre/type_checks.hpp"
#include "../../include/cyfre/matrix.hpp"
// #include <iostream> // remove all iostream class and function to minimize executable and compile time in the future.

namespace cyfre {
  template <typename T, typename dim, mem_layout mem_layout_t>
  mat<T, dim, mem_layout_t>::mat() : matrix() {
  }

  template <typename T, typename dim, mem_layout mem_layout_t>
  mat<T, dim, mem_layout_t>::mat(size_t rows, size_t cols)
      : matrix(rows, cols) {
  }

  template <typename T, typename dim, mem_layout mem_layout_t>
  constexpr size_t mat<T, dim, mem_layout_t>::rows() const {
    return matrix.rows;
  }

  template <typename T, typename dim, mem_layout mem_layout_t>
  constexpr size_t mat<T, dim, mem_layout_t>::cols() const {
    return matrix.cols;
  }

} // namespace cyfre

#endif
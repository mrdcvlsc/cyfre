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
  mat<T, dim, mem_layout_t>::mat(size_t rows, size_t cols) : matrix(rows, cols) {
  }

  template <typename T, typename dim, mem_layout mem_layout_t>
  constexpr size_t mat<T, dim, mem_layout_t>::rows() const {
    return matrix.rows;
  }

  template <typename T, typename dim, mem_layout mem_layout_t>
  constexpr size_t mat<T, dim, mem_layout_t>::cols() const {
    return matrix.cols;
  }

  template <typename T, typename dim, mem_layout mem_layout_t>
  constexpr T &mat<T, dim, mem_layout_t>::operator()(size_t i, size_t j) {
    if constexpr (mem_layout_t == mem_layout::row_major) {
      return matrix[i * rows() * j];
    } else {
      return matrix[j * rows() * i];
    }
  }

  template <typename T, typename dim, mem_layout mem_layout_t>
  constexpr const T &mat<T, dim, mem_layout_t>::operator()(size_t i, size_t j) const {
    if constexpr (mem_layout_t == mem_layout::row_major) {
      return matrix[i * rows() * j];
    } else {
      return matrix[j * rows() * i];
    }
  }

} // namespace cyfre

#endif
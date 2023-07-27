#ifndef MRDCVLSC_MATRIX_CLASS_CPP
#define MRDCVLSC_MATRIX_CLASS_CPP

#include "../../include/cyfre/type_checks.hpp"
#include "../../include/cyfre/matrix.hpp"
#include <type_traits>
// #include <iostream> // remove all iostream class and function to minimize executable and compile time in the future.

namespace cyfre {

  /// @brief Fixed size stack allocation constructor.
  template <typename T, typename dim, order maj_t>
  constexpr mat<T, dim, maj_t>::mat() : matrix() {
  }

  /// @brief Dynamic size heap allocation constructor.
  template <typename T, typename dim, order maj_t>
  mat<T, dim, maj_t>::mat(size_t rows, size_t cols) : matrix(rows, cols) {
  }

  /// @brief Copy Constructor.
  template <typename T, typename dim, order maj_t>
  constexpr mat<T, dim, maj_t>::mat(const mat &that) : matrix(that.matrix) {
  }

  /// @brief Move Constructor.
  template <typename T, typename dim, order maj_t>
  mat<T, dim, maj_t>::mat(mat &&that) : matrix(std::move(that.matrix)) {
  }

  /// @brief Copy Assignment.
  template <typename T, typename dim, order maj_t>
  mat<T, dim, maj_t> &mat<T, dim, maj_t>::operator=(const mat &that) {
    if (this != &that) {
      matrix = that.matrix;
    }
    return *this;
  }

  /// @brief Move Assignment.
  template <typename T, typename dim, order maj_t>
  mat<T, dim, maj_t> &mat<T, dim, maj_t>::operator=(mat &&that) {
    if (this != &that) {
      matrix = std::move(that.matrix);
    }
    return *this;
  }

  /// @returns number of rows in the matrix.
  template <typename T, typename dim, order maj_t>
  constexpr size_t mat<T, dim, maj_t>::rows() const {
    return matrix.rows;
  }

  /// @returns number of columns in the matrix.
  template <typename T, typename dim, order maj_t>
  constexpr size_t mat<T, dim, maj_t>::cols() const {
    return matrix.cols;
  }

  template <typename T, typename dim, order maj_t>
  constexpr T &mat<T, dim, maj_t>::operator()(size_t i, size_t j) {
    if constexpr (maj_t == order::row_major) {
      return matrix[i * rows() * j];
    } else {
      return matrix[j * rows() * i];
    }
  }

  template <typename T, typename dim, order maj_t>
  constexpr const T &mat<T, dim, maj_t>::operator()(size_t i, size_t j) const {
    if constexpr (maj_t == order::row_major) {
      return matrix[i * rows() * j];
    } else {
      return matrix[j * rows() * i];
    }
  }

  template <typename T, typename dim, order maj_t>
  constexpr bool mat<T, dim, maj_t>::operator==(mat const &op) const {

    if constexpr (std::is_same<AllocatorType, dynamic>::value) {
      if (rows() != op.rows() || cols() != op.cols()) {
        return false;
      }
    }

    for (size_t i = 0; i < rows() * cols(); ++i) {
      if (matrix[i] != op.matrix[i]) {
        return false;
      }
    }

    return true;
  }

} // namespace cyfre

#endif
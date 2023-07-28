#ifndef MRDCVLSC_MATRIX_CLASS_CPP
#define MRDCVLSC_MATRIX_CLASS_CPP

#include "../../include/cyfre/matrix.hpp"

// #include <iostream> // remove all iostream class and function to minimize executable and compile time in the future.

namespace cyfre {

  /// @brief Fixed size stack allocation constructor.
  template <concepts::scalars T, typename Dim, order_t Order>
  constexpr mat<T, Dim, Order>::mat() : matrix() {}

  /// @brief Dynamic size heap allocation constructor.
  template <concepts::scalars T, typename Dim, order_t Order>
  mat<T, Dim, Order>::mat(size_t rows, size_t cols) : matrix(rows, cols) {}

  /// @brief Copy Constructor.
  template <concepts::scalars T, typename Dim, order_t Order>
  constexpr mat<T, Dim, Order>::mat(const mat &that) : matrix(that.matrix) {}

  /// @brief Move Constructor.
  template <concepts::scalars T, typename Dim, order_t Order>
  mat<T, Dim, Order>::mat(mat &&that) : matrix(std::move(that.matrix)) {}

  /// @brief Copy Assignment.
  template <concepts::scalars T, typename Dim, order_t Order>
  mat<T, Dim, Order> &mat<T, Dim, Order>::operator=(const mat &that) {
    if (this != &that) {
      matrix = that.matrix;
    }
    return *this;
  }

  /// @brief Move Assignment.
  template <concepts::scalars T, typename Dim, order_t Order>
  mat<T, Dim, Order> &mat<T, Dim, Order>::operator=(mat &&that) {
    if (this != &that) {
      matrix = std::move(that.matrix);
    }
    return *this;
  }

  /// @returns number of rows in the matrix.
  template <concepts::scalars T, typename Dim, order_t Order>
  constexpr size_t mat<T, Dim, Order>::rows() const {
    return matrix.rows;
  }

  /// @returns number of columns in the matrix.
  template <concepts::scalars T, typename Dim, order_t Order>
  constexpr size_t mat<T, Dim, Order>::cols() const {
    return matrix.cols;
  }

  /// @brief Fill the matrix with the given value.
  template <concepts::scalars T, typename Dim, order_t Order>
  constexpr void mat<T, Dim, Order>::fill(T value) {
    for (size_t i = 0; i < rows() * cols(); ++i) {
      matrix[i] = value;
    }
  }

  /////////////////////// OPERATORS ///////////////////

  template <concepts::scalars T, typename Dim, order_t Order>
  constexpr T &mat<T, Dim, Order>::operator()(size_t i, size_t j) {
    if constexpr (Order == order_t::row_major) {
      return matrix[i * rows() + j];
    } else {
      return matrix[j * rows() + i];
    }
  }

  template <concepts::scalars T, typename Dim, order_t Order>
  constexpr const T &mat<T, Dim, Order>::operator()(size_t i, size_t j) const {
    if constexpr (Order == order_t::row_major) {
      return matrix[i * rows() + j];
    } else {
      return matrix[j * rows() + i];
    }
  }

  template <concepts::scalars T, typename Dim, order_t Order>
  template <concepts::matrices Matrix>
  constexpr bool mat<T, Dim, Order>::operator==(Matrix const &op) const {
    if (rows() != op.rows() || cols() != op.cols()) {
      return false;
    }

    for (size_t i = 0; i < rows(); ++i) {
      for (size_t j = 0; j < cols(); ++j) {
        if (this->operator()(i, j) != op(i, j)) {
          return false;
        }
      }
    }

    return true;
  }

} // namespace cyfre

#endif
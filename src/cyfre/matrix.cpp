#ifndef MRDCVLSC_MATRIX_CLASS_CPP
#define MRDCVLSC_MATRIX_CLASS_CPP

#include <iostream>
#include <iomanip>
#include <sstream>

#include "../../include/cyfre/matrix.hpp"

// #include <iostream> // remove all iostream class and function to minimize executable and compile time in the future.

namespace cyfre {

  /// @brief Fixed size stack allocation constructor.
  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  constexpr mat<T, Dim, Order, Blas>::mat() : matrix() {}

  /// @brief Dynamic size heap allocation constructor.
  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  mat<T, Dim, Order, Blas>::mat(size_t rows, size_t cols) : matrix(rows, cols) {}

  /// @brief Copy Constructor.
  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  constexpr mat<T, Dim, Order, Blas>::mat(const mat &that) : matrix(that.matrix) {}

  /// @brief Move Constructor.
  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  mat<T, Dim, Order, Blas>::mat(mat &&that) : matrix(std::move(that.matrix)) {}

  /// @brief Copy Assignment.
  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  mat<T, Dim, Order, Blas> &mat<T, Dim, Order, Blas>::operator=(const mat &that) {
    if (this != &that) {
      matrix = that.matrix;
    }
    return *this;
  }

  /// @brief Move Assignment.
  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  mat<T, Dim, Order, Blas> &mat<T, Dim, Order, Blas>::operator=(mat &&that) {
    if (this != &that) {
      matrix = std::move(that.matrix);
    }
    return *this;
  }

  /// @brief initializer list constructor.
  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  constexpr mat<T, Dim, Order, Blas>::mat(std::initializer_list<std::initializer_list<T>> sequence)
      : mat(sequence.size(), (sequence.begin())[0].size()) {
    if (sequence.size() > rows() * cols()) {
      throw std::invalid_argument("initializer list total elements should be <= (rows * cols)");
    }

    size_t initial_row_width = cols();
    size_t i = 0;
    for (auto initalizer_list_row: sequence) {
      size_t j = 0;
      if (initial_row_width != initalizer_list_row.size()) {
        throw std::invalid_argument("initializer list elements rows should have the same lengths");
      }

      for (T initalizer_list_col: initalizer_list_row) {
        this->operator()(i, j++) = initalizer_list_col;
      }
      i++;
    }
  }

  /////////////////////// METHODS ///////////////////

  /// @returns number of rows in the matrix.
  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  constexpr size_t mat<T, Dim, Order, Blas>::rows() const {
    return matrix.rows;
  }

  /// @returns number of columns in the matrix.
  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  constexpr size_t mat<T, Dim, Order, Blas>::cols() const {
    return matrix.cols;
  }

  /// @brief Fill the matrix with the given value.
  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  constexpr void mat<T, Dim, Order, Blas>::fill(T value) {
    for (size_t i = 0; i < rows() * cols(); ++i) {
      matrix[i] = value;
    }
  }

  /// @brief Resizes the the matrix (only for dynamic).
  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  void mat<T, Dim, Order, Blas>::resize(size_t rows, size_t cols) {
    static_assert(std::is_same_v<AllocatorType, dynamic>, "fixed size matrices cannot be resized");
    matrix.resize(rows, cols);
  }

  /// @brief Print the matrix.
  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  void mat<T, Dim, Order, Blas>::print() const {
    // Calculate the maximum width of each column
    std::vector<size_t> widths(cols(), 0);
    for (size_t i = 0; i < rows(); ++i) {
      for (size_t j = 0; j < cols(); ++j) {
        std::stringstream ss;
        ss << this->operator()(i, j);
        widths[i] = std::max(widths[i], ss.str().length());
      }
    }

    for (size_t i = 0; i < rows(); ++i) {
      for (size_t j = 0; j < cols(); ++j) {
        std::cout << std::setw(widths[i]) << this->operator()(i, j) << " ";
      }
      std::cout << '\n';
    }

    // std::cout << std::setw(0) << '\n';
    std::cout << '\n';
  }

  /////////////////////// OPERATORS ///////////////////

  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  constexpr T &mat<T, Dim, Order, Blas>::operator()(size_t i, size_t j) {
    if constexpr (Order == order_t::row_major) {
      return matrix[i * rows() + j];
    } else {
      return matrix[j * rows() + i];
    }
  }

  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  constexpr const T &mat<T, Dim, Order, Blas>::operator()(size_t i, size_t j) const {
    if constexpr (Order == order_t::row_major) {
      return matrix[i * rows() + j];
    } else {
      return matrix[j * rows() + i];
    }
  }

  template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
  template <concepts::matrices Matrix>
  constexpr bool mat<T, Dim, Order, Blas>::operator==(Matrix const &op) const {
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
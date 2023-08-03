#ifndef MRDCVLSC_MATRIX_CLASS_CPP
#define MRDCVLSC_MATRIX_CLASS_CPP

#define CYFRE_MAT_TARGS template <concepts::scalars T, typename Dim, order_t Order, typename Blas>
#define CYFRE_MAT_TARGS_MatrixT CYFRE_MAT_TARGS template <concepts::matrices MatrixT>
#define CYFRE_MAT mat<T, Dim, Order, Blas>

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "../../include/cyfre/matrix.hpp"

// #include <iostream> // remove all iostream class and function to minimize executable and compile time in the future.

namespace cyfre {

  /// @brief Fixed size stack allocation constructor.
  CYFRE_MAT_TARGS constexpr CYFRE_MAT::mat() : matrix() {}

  /// @brief Dynamic size heap allocation constructor.
  CYFRE_MAT_TARGS CYFRE_MAT::mat(size_t rows, size_t cols) : matrix(rows, cols) {}

  /// @brief Copy Constructor.
  CYFRE_MAT_TARGS constexpr CYFRE_MAT::mat(const mat &that) : matrix(that.matrix) {}

  /// @brief Move Constructor.
  CYFRE_MAT_TARGS CYFRE_MAT::mat(mat &&that) : matrix(std::move(that.matrix)) {}

  /// @brief Copy Assignment.
  CYFRE_MAT_TARGS CYFRE_MAT &CYFRE_MAT::operator=(const mat &that) {
    if (this != &that) {
      matrix = that.matrix;
    }
    return *this;
  }

  /// @brief Move Assignment.
  CYFRE_MAT_TARGS CYFRE_MAT &CYFRE_MAT::operator=(mat &&that) {
    if (this != &that) {
      matrix = std::move(that.matrix);
    }
    return *this;
  }

  /// @brief initializer list constructor.
  CYFRE_MAT_TARGS constexpr CYFRE_MAT::mat(std::initializer_list<std::initializer_list<T>> sequence) : mat() {
    if constexpr (std::is_same<AllocatorType, dynamic>::value) {
      this->resize(sequence.size(), sequence.begin()[0].size());
    }

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
  CYFRE_MAT_TARGS constexpr size_t CYFRE_MAT::rows() const { return matrix.rows; }

  /// @returns number of columns in the matrix.
  CYFRE_MAT_TARGS constexpr size_t CYFRE_MAT::cols() const { return matrix.cols; }

  /// @brief Fill the matrix with the given value.
  CYFRE_MAT_TARGS constexpr void CYFRE_MAT::fill(T value) {
    for (size_t i = 0; i < rows() * cols(); ++i) {
      matrix[i] = value;
    }
  }

  /// @brief Resizes the the matrix (only for dynamic).
  CYFRE_MAT_TARGS void CYFRE_MAT::resize(size_t rows, size_t cols) {
    static_assert(std::is_same_v<AllocatorType, dynamic>, "fixed size matrices cannot be resized");
    matrix.resize(rows, cols);
  }

  /// @brief Print the matrix.
  CYFRE_MAT_TARGS void CYFRE_MAT::print() const {
    // Calculate the maximum width of each column

    std::vector<size_t> widths(cols(), 0);

    for (size_t i = 0; i < rows(); ++i) {
      for (size_t j = 0; j < cols(); ++j) {
        std::stringstream ss;
        ss << this->operator()(i, j);
        widths[j] = std::max(widths[j], ss.str().length());
      }
    }

    for (size_t i = 0; i < rows(); ++i) {
      for (size_t j = 0; j < cols(); ++j) {
        std::cout << std::setw(widths[j]) << this->operator()(i, j) << " ";
      }
      std::cout << '\n';
    }

    // std::cout << std::setw(0) << '\n';
    std::cout << '\n';
  }

  /////////////////////// OPERATORS ///////////////////

  CYFRE_MAT_TARGS constexpr T &CYFRE_MAT::operator()(size_t i, size_t j) {
    if constexpr (Order == order_t::row_major) {
      return matrix[i * cols() + j];
    } else {
      return matrix[j * rows() + i];
    }
  }

  CYFRE_MAT_TARGS constexpr const T &CYFRE_MAT::operator()(size_t i, size_t j) const {
    if constexpr (Order == order_t::row_major) {
      return matrix[i * cols() + j];
    } else {
      return matrix[j * rows() + i];
    }
  }

  CYFRE_MAT_TARGS constexpr bool CYFRE_MAT::operator==(mat const &op) const {
    if (rows() != op.rows() || cols() != op.cols()) {
      return false;
    }

    // TODO: Optimize indexing access for different memory layout order.

    for (size_t i = 0; i < rows(); ++i) {
      for (size_t j = 0; j < cols(); ++j) {
        if (this->operator()(i, j) != op(i, j)) {
          return false;
        }
      }
    }

    return true;
  }

  CYFRE_MAT_TARGS_MatrixT constexpr bool CYFRE_MAT::operator==(MatrixT const &op) const {
    if (rows() != op.rows() || cols() != op.cols()) {
      return false;
    }

    // TODO: Optimize indexing access for different memory layout order.

    for (size_t i = 0; i < rows(); ++i) {
      for (size_t j = 0; j < cols(); ++j) {
        if (this->operator()(i, j) != op(i, j)) {
          return false;
        }
      }
    }

    return true;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////

  CYFRE_MAT_TARGS constexpr CYFRE_MAT &CYFRE_MAT::operator+=(T scalar) {
    for (size_t i = 0; i < rows() * cols(); ++i) {
      matrix[i] += scalar;
    }
    return *this;
  }

  CYFRE_MAT_TARGS constexpr CYFRE_MAT CYFRE_MAT::operator+(T scalar) const {
    mat answer(rows(), cols());
    for (size_t i = 0; i < rows() * cols(); ++i) {
      answer.matrix[i] = matrix[i] + scalar;
    }
    return answer;
  }

  CYFRE_MAT_TARGS constexpr CYFRE_MAT &CYFRE_MAT::operator-=(T scalar) {
    for (size_t i = 0; i < rows() * cols(); ++i) {
      matrix[i] -= scalar;
    }
    return *this;
  }

  CYFRE_MAT_TARGS constexpr CYFRE_MAT CYFRE_MAT::operator-(T scalar) const {
    mat answer(rows(), cols());
    for (size_t i = 0; i < rows() * cols(); ++i) {
      answer.matrix[i] = matrix[i] - scalar;
    }
    return answer;
  }

  CYFRE_MAT_TARGS constexpr CYFRE_MAT &CYFRE_MAT::operator*=(T scalar) {
    for (size_t i = 0; i < rows() * cols(); ++i) {
      matrix[i] *= scalar;
    }
    return *this;
  }

  CYFRE_MAT_TARGS constexpr CYFRE_MAT CYFRE_MAT::operator*(T scalar) const {
    mat answer(rows(), cols());
    for (size_t i = 0; i < rows() * cols(); ++i) {
      answer.matrix[i] = matrix[i] * scalar;
    }
    return answer;
  }

  CYFRE_MAT_TARGS constexpr CYFRE_MAT &CYFRE_MAT::operator/=(T scalar) {
    for (size_t i = 0; i < rows() * cols(); ++i) {
      matrix[i] /= scalar;
    }
    return *this;
  }

  CYFRE_MAT_TARGS constexpr CYFRE_MAT CYFRE_MAT::operator/(T scalar) const {
    mat answer(rows(), cols());
    for (size_t i = 0; i < rows() * cols(); ++i) {
      answer.matrix[i] = matrix[i] / scalar;
    }
    return answer;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////

  CYFRE_MAT_TARGS_MatrixT constexpr CYFRE_MAT &CYFRE_MAT::operator+=(MatrixT const &op) {
    Blas::add(*this, op);
    return *this;
  }

  CYFRE_MAT_TARGS_MatrixT constexpr CYFRE_MAT CYFRE_MAT::operator+(MatrixT const &op) const {
    mat answer;
    Blas::add(answer, *this, op);
    return answer;
  }

  CYFRE_MAT_TARGS_MatrixT constexpr CYFRE_MAT &CYFRE_MAT::operator-=(MatrixT const &op) {
    Blas::sub(*this, op);
    return *this;
  }

  CYFRE_MAT_TARGS_MatrixT constexpr CYFRE_MAT CYFRE_MAT::operator-(MatrixT const &op) const {
    mat answer;
    Blas::sub(answer, *this, op);
    return answer;
  }

  CYFRE_MAT_TARGS_MatrixT constexpr CYFRE_MAT &CYFRE_MAT::operator*=(MatrixT const &op) {
    Blas::mul(*this, op);
    return *this;
  }

  CYFRE_MAT_TARGS_MatrixT constexpr CYFRE_MAT CYFRE_MAT::operator*(MatrixT const &op) const {
    mat answer;
    Blas::mul(answer, *this, op);
    return answer;
  }

  CYFRE_MAT_TARGS_MatrixT constexpr CYFRE_MAT &CYFRE_MAT::operator/=(MatrixT const &op) {
    Blas::div(*this, op);
    return *this;
  }

  CYFRE_MAT_TARGS_MatrixT constexpr CYFRE_MAT CYFRE_MAT::operator/(MatrixT const &op) const {
    mat answer;
    Blas::div(answer, *this, op);
    return answer;
  }
} // namespace cyfre

#endif
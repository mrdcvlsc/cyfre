#ifndef MRDCVLSC_HEAP_ALLOCATION_CPP
#define MRDCVLSC_HEAP_ALLOCATION_CPP

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "../../include/cyfre/check_operators.hpp"
#include "../../include/cyfre/heap_alloc.hpp"

namespace cyfre {

  // =================== BASIC CONSTRUCTORS ===================

  template <typename T>
  dynamic<T>::dynamic(size_t rows, size_t cols) : matrix(new T[rows * cols]), rows(rows), cols(cols) {
    static_assert(!valid_operators<T>::value, "mat<T,...> type 'T' does not support the necessary operators");
  }

  // =================== DESTRUCTOR ===================

  template <typename T>
  dynamic<T>::~dynamic() {
    delete[] matrix;
  }

  // =================== SPECIAL CONSTRUCTORS ===================

  /// @brief Copy Constructor.
  template <typename T>
  dynamic<T>::dynamic(dynamic<T> const &that) : dynamic<T>::dynamic(that.rows, that.cols) {
    memcpy(matrix, that.matrix, that.rows * that.cols);
  }

  /// @brief Move Constructor.
  template <typename T>
  dynamic<T>::dynamic(dynamic<T> &&that) : matrix(that.matrix), rows(that.rows), cols(that.cols) {
    that.matrix = NULL;
  }

  /// @brief Copy Assignment
  template <typename T>
  dynamic<T> &dynamic<T>::operator=(dynamic<T> const &that) {
    if (this != &that) {
      rows = that.rows;
      cols = that.cols;

      if (matrix) {
        delete[] matrix;
      }

      size_t n = that.rows * that.cols;
      matrix = new T[n];
      memcpy(matrix, that.matrix, sizeof(T) * n);
    }
    return *this;
  }

  /// @brief Move Assignment
  template <typename T>
  dynamic<T> &dynamic<T>::operator=(dynamic<T> &&that) {
    if (this != &that) {
      if (matrix) {
        delete[] matrix;
      }

      rows = that.rows;
      cols = that.cols;
      matrix = that.matrix;

      that.rows = 0;
      that.cols = 0;
      that.matrix = NULL;
    }
    return *this;
  }
} // namespace cyfre

#endif
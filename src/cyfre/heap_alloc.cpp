#ifndef MRDCVLSC_HEAP_ALLOCATION_CPP
#define MRDCVLSC_HEAP_ALLOCATION_CPP

#include <stddef.h>
#include <assert.h>
#include <string.h>

#include "../../include/cyfre/heap_alloc.hpp"
#include "../../include/cyfre/type_checks.hpp"

namespace cyfre {
  namespace backend {
    // =================== BASIC CONSTRUCTORS ===================

    template <size_t ROWS, size_t COLS>
    template <typename T, size_t Rows, size_t Cols>
    dynamic<ROWS, COLS>::allocate<T, Rows, Cols>::allocate(size_t rows, size_t cols)
        : matrix(new T[rows * cols]), rows(rows), cols(cols) {
    }

    // =================== DESTRUCTOR ===================

    template <size_t ROWS, size_t COLS>
    template <typename T, size_t Rows, size_t Cols>
    dynamic<ROWS, COLS>::allocate<T, Rows, Cols>::~allocate() {
      delete[] matrix;
    }

    // =================== SPECIAL CONSTRUCTORS ===================

    template <size_t ROWS, size_t COLS>
    template <typename T, size_t Rows, size_t Cols>
    dynamic<ROWS, COLS>::allocate<T, Rows, Cols>::allocate(dynamic<ROWS, COLS>::allocate<T, Rows, Cols> const &that)
        : allocate(that.rows, that.cols) { // or even better try this
      memcpy(matrix, that.matrix, sizeof(T) * that.rows * that.cols);
    }

    template <size_t ROWS, size_t COLS>
    template <typename T, size_t Rows, size_t Cols>
    dynamic<ROWS, COLS>::allocate<T, Rows, Cols>::allocate(dynamic<ROWS, COLS>::allocate<T, Rows, Cols> &&that)
        : matrix(that.matrix), rows(that.rows), cols(that.cols) {
      that.matrix = NULL;
    }

    template <size_t ROWS, size_t COLS>
    template <typename T, size_t Rows, size_t Cols>
    typename dynamic<ROWS, COLS>::template allocate<T, Rows, Cols>
      &dynamic<ROWS, COLS>::allocate<T, Rows, Cols>::operator=(const dynamic<ROWS, COLS>::allocate<T, Rows, Cols> &that
      ) {
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

    template <size_t ROWS, size_t COLS>
    template <typename T, size_t Rows, size_t Cols>
    typename dynamic<ROWS, COLS>::template allocate<T, Rows, Cols>
      &dynamic<ROWS, COLS>::allocate<T, Rows, Cols>::operator=(dynamic<ROWS, COLS>::allocate<T, Rows, Cols> &&that) {
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

    // =================== INDEXING OPERATOR ===================

    template <size_t ROWS, size_t COLS>
    template <typename T, size_t Rows, size_t Cols>
    inline T &dynamic<ROWS, COLS>::allocate<T, Rows, Cols>::operator[](size_t i) {
      return matrix[i];
    }

    template <size_t ROWS, size_t COLS>
    template <typename T, size_t Rows, size_t Cols>
    inline const T &dynamic<ROWS, COLS>::allocate<T, Rows, Cols>::operator[](size_t i) const {
      return matrix[i];
    }
  } // namespace backend
} // namespace cyfre

#endif
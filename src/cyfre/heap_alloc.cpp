#ifndef MRDCVLSC_HEAP_ALLOCATION_CPP
#define MRDCVLSC_HEAP_ALLOCATION_CPP

#include <string.h>

#include "../../include/cyfre/heap_alloc.hpp"

namespace cyfre {
  namespace backend {
    // =================== BASIC CONSTRUCTORS ===================

    template <size_t Rows, size_t Cols>
    template <typename _T, size_t _Rows, size_t _Cols>
    dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols>::allocate(size_t rows, size_t cols)
        : matrix(new _T[rows * cols]), rows(rows), cols(cols) {}

    // =================== DESTRUCTOR ===================

    template <size_t Rows, size_t Cols>
    template <typename _T, size_t _Rows, size_t _Cols>
    dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols>::~allocate() {
      delete[] matrix;
    }

    // =================== SPECIAL CONSTRUCTORS ===================

    template <size_t Rows, size_t Cols>
    template <typename _T, size_t _Rows, size_t _Cols>
    dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols>::allocate(
      dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols> const &that
    )
        : allocate(that.rows, that.cols) { // or even better try this
      memcpy(matrix, that.matrix, sizeof(_T) * that.rows * that.cols);
    }

    template <size_t Rows, size_t Cols>
    template <typename _T, size_t _Rows, size_t _Cols>
    dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols>::allocate(dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols> &&that)
        : matrix(that.matrix), rows(that.rows), cols(that.cols) {
      that.matrix = NULL;
    }

    template <size_t Rows, size_t Cols>
    template <typename _T, size_t _Rows, size_t _Cols>
    typename dynamic<Rows, Cols>::template allocate<_T, _Rows, _Cols> &dynamic<Rows, Cols>::allocate<
      _T, _Rows, _Cols>::operator=(const dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols> &that) {
      if (this != &that) {
        rows = that.rows;
        cols = that.cols;

        if (matrix) {
          delete[] matrix;
        }

        size_t n = that.rows * that.cols;
        matrix = new _T[n];
        memcpy(matrix, that.matrix, sizeof(_T) * n);
      }
      return *this;
    }

    template <size_t Rows, size_t Cols>
    template <typename _T, size_t _Rows, size_t _Cols>
    typename dynamic<Rows, Cols>::template allocate<_T, _Rows, _Cols>
      &dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols>::operator=(dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols> &&that
      ) {
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

    template <size_t Rows, size_t Cols>
    template <typename _T, size_t _Rows, size_t _Cols>
    inline _T &dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols>::operator[](size_t i) {
      return matrix[i];
    }

    template <size_t Rows, size_t Cols>
    template <typename _T, size_t _Rows, size_t _Cols>
    inline const _T &dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols>::operator[](size_t i) const {
      return matrix[i];
    }
  } // namespace backend
} // namespace cyfre

#endif
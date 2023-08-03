#ifndef MRDCVLSC_HEAP_ALLOCATION_CPP
#define MRDCVLSC_HEAP_ALLOCATION_CPP

#ifndef CYFRE_ALLOC_TEMP
  #define CYFRE_ALLOC_TEMP                                                                                             \
    template <size_t Rows, size_t Cols>                                                                                \
    template <typename _T, size_t _Rows, size_t _Cols>
#endif
#define CYFRE_DYNAMIC dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols>
#define CYFRE_DYNAMIC_ALLOC typename dynamic<Rows, Cols>::template allocate<_T, _Rows, _Cols>

#include <cstdlib>
#include <stdlib.h>
#include <string.h>

#include "../../include/cyfre/heap_alloc.hpp"

namespace cyfre {
  namespace backend {
    // =================== BASIC CONSTRUCTORS ===================

    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC::allocate() : matrix(reinterpret_cast<_T *>(malloc(0))), rows(0), cols(0) {}

    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC::allocate(size_t rows, size_t cols)
        : matrix(reinterpret_cast<_T *>(malloc(sizeof(_T) * rows * cols))), rows(rows), cols(cols) {}

    // =================== DESTRUCTOR ===================

    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC::~allocate() {
      if (matrix)
        free(matrix);
    }

    // =================== SPECIAL CONSTRUCTORS ===================

    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC::allocate(CYFRE_DYNAMIC const &that)
        : allocate(that.rows, that.cols) { // or even better try this
      memcpy(matrix, that.matrix, sizeof(_T) * that.rows * that.cols);
    }

    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC::allocate(CYFRE_DYNAMIC &&that)
        : matrix(that.matrix), rows(that.rows), cols(that.cols) {
      that.matrix = NULL;
    }

    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC_ALLOC &CYFRE_DYNAMIC::operator=(const CYFRE_DYNAMIC &that) {
      if (this != &that) {
        rows = that.rows;
        cols = that.cols;

        if (matrix) {
          free(matrix);
        }

        size_t n = that.rows * that.cols;
        matrix = reinterpret_cast<_T *>(malloc(sizeof(_T) * that.rows * that.cols));
        memcpy(matrix, that.matrix, sizeof(_T) * n);
      }
      return *this;
    }

    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC_ALLOC &CYFRE_DYNAMIC::operator=(CYFRE_DYNAMIC &&that) {
      if (this != &that) {
        if (matrix) {
          free(matrix);
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

    CYFRE_ALLOC_TEMP inline _T &CYFRE_DYNAMIC::operator[](size_t i) { return matrix[i]; }

    CYFRE_ALLOC_TEMP inline const _T &CYFRE_DYNAMIC::operator[](size_t i) const { return matrix[i]; }

    CYFRE_ALLOC_TEMP void CYFRE_DYNAMIC::resize(size_t rows, size_t cols) {
      matrix = reinterpret_cast<_T *>(realloc(matrix, sizeof(_T) * rows * cols));
      this->rows = rows;
      this->cols = cols;
    }
  } // namespace backend
} // namespace cyfre

#endif
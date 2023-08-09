#ifndef MRDCVLSC_HEAP_ALLOCATION_CPP
#define MRDCVLSC_HEAP_ALLOCATION_CPP

#include "../../include/cyfre/heap_alloc.hpp"

#include <cstdlib>
#include <type_traits>
#include <utility>

#include <stdlib.h>
#include <string.h>

#ifndef CYFRE_ALLOC_TEMP
  #define CYFRE_ALLOC_TEMP                                                                                             \
    template <size_t Rows, size_t Cols>                                                                                \
    template <typename _T, size_t _Rows, size_t _Cols>
#endif

#ifndef CYFRE_ALLOC_TEMP_AllocatorT
  #define CYFRE_ALLOC_TEMP_AllocatorT CYFRE_ALLOC_TEMP template <concepts::allocators AllocatorT>
#endif

#define CYFRE_DYNAMIC dynamic<Rows, Cols>::allocate<_T, _Rows, _Cols>
#define CYFRE_DYNAMIC_ALLOC typename dynamic<Rows, Cols>::template allocate<_T, _Rows, _Cols>

namespace cyfre {
  namespace backend {
    // =================== BASIC CONSTRUCTORS ===================

    /// Heap Alloc Constructor - 0 x 0 dimension.
    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC::allocate() : matrix(reinterpret_cast<_T *>(malloc(0))), rows(0), cols(0) {}

    /// Heap Alloc Constructor - rows x cols dimension.
    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC::allocate(size_t rows, size_t cols)
        : matrix(reinterpret_cast<_T *>(malloc(sizeof(_T) * rows * cols))), rows(rows), cols(cols) {}

    // =================== DESTRUCTOR ===================

    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC::~allocate() { free(matrix); }

    // =================== SPECIAL CONSTRUCTORS ===================

    /// @brief Copy Constructor.
    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC::allocate(allocate const &that)
        : allocate(that.rows, that.cols) { // or even better try this
      memcpy(matrix, that.matrix, sizeof(_T) * that.rows * that.cols);
    }

    /// @brief Move Constructor.
    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC::allocate(allocate &&that) : allocate() {
      free(matrix);
      matrix = that.matrix;
      that.matrix = NULL;

      rows = that.rows;
      cols = that.cols;
    }

    /// @brief Copy Assignment.
    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC_ALLOC &CYFRE_DYNAMIC::operator=(const allocate &that) {
      if (this != &that) {
        resize(that.rows, that.cols);
        memcpy(matrix, that.matrix, sizeof(_T) * that.rows * that.cols);
      }

      return *this;
    }

    /// @brief Move Assignment.
    CYFRE_ALLOC_TEMP CYFRE_DYNAMIC_ALLOC &CYFRE_DYNAMIC::operator=(allocate &&that) {
      if (this != &that) {
        free(matrix);

        matrix = that.matrix;
        that.matrix = NULL;

        rows = that.rows;
        cols = that.cols;
      }

      return *this;
    }

    /// @brief Copy Constructor For Other Types.
    CYFRE_ALLOC_TEMP_AllocatorT CYFRE_DYNAMIC::allocate(AllocatorT const &that)
        : allocate(that.rows, that.cols) { // or even better try this
      memcpy(matrix, that.matrix, sizeof(_T) * that.rows * that.cols);
    }

    /// @brief Move Constructor For Other Types.
    CYFRE_ALLOC_TEMP_AllocatorT CYFRE_DYNAMIC::allocate(AllocatorT &&that) : allocate() {
      if constexpr (std::is_same<AllocatorT, decltype(*this)>::value) {
        free(matrix);
        matrix = that.matrix;
        that.matrix = NULL;

        rows = that.rows;
        cols = that.cols;
      } else {
        resize(that.rows, that.cols);
        for (size_t i = 0; i < that.rows * that.cols; ++i) {
          matrix[i] = std::move(that.matrix[i]);
        }
      }
    }

    /// @brief Copy Assignment For Other Types.
    CYFRE_ALLOC_TEMP_AllocatorT CYFRE_DYNAMIC_ALLOC &CYFRE_DYNAMIC::operator=(const AllocatorT &that) {
      resize(that.rows, that.cols);
      memcpy(matrix, that.matrix, sizeof(_T) * that.rows * that.cols);

      return *this;
    }

    /// @brief Move Assignment For Other Types.
    CYFRE_ALLOC_TEMP_AllocatorT CYFRE_DYNAMIC_ALLOC &CYFRE_DYNAMIC::operator=(AllocatorT &&that) {
      if constexpr (std::is_same<AllocatorT, decltype(*this)>::value) {
        free(matrix);

        matrix = that.matrix;
        that.matrix = NULL;

        rows = that.rows;
        cols = that.cols;
      } else {
        resize(that.rows, that.cols);
        for (size_t i = 0; i < that.rows * that.cols; ++i) {
          matrix[i] = std::move(that.matrix[i]);
        }
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
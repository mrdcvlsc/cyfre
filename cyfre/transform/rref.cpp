#ifndef CYFRE_RREF_CPP
#define CYFRE_RREF_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
  /// converts matrix to reduced row echelon form of a matrix
  template <class T>
  void mat<T>::rref() {
    auto nonzrow = [](const mat<T> &input, size_t i, size_t j) -> long long int {
      for (size_t r = i; r < input.height; ++r) {
        if (input.matrix[r * input.width + j] != 0) {
          return r;
        }
      }
      return -1;
    };

    auto fix_pivot = [](mat<T> &input, size_t pi, size_t pj) {
      for (size_t i = 0; i < input.height; ++i) {
        if (i != pi) {
          input.row_scale(-input.matrix[i * input.width + pj], pi, i);
        }
      }
    };

    auto make_pivot = [](mat<T> &input, size_t pi, size_t pj) {
      input.scale_row(pi, DIV, input.matrix[pi * input.width + pj]);
    };

    size_t cpi = 0;
    size_t cpj = 0;

    while (cpi < height && cpj < width) {
      long long int nonzerorow = nonzrow(*this, cpi, cpj);

      if (nonzerorow < 0) {
        cpj++;
        continue;
      }

      if (nonzerorow != (long long int) cpi)
        this->row_swap(cpi, nonzerorow);
      if (matrix[cpi * width + cpj] != 1)
        make_pivot(*this, cpi, cpj);
      fix_pivot(*this, cpi, cpj);
      cpi++;
      cpj++;
    }
  }

  /// @returns reduced row echelon form of a matrix
  template <typename T>
  mat<T> rref(mat<T> input) {
    input.rref();
    return input;
  }
} // namespace cyfre

#endif
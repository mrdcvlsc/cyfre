#ifndef CYFRE_SUM_CPP
#define CYFRE_SUM_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
  /// @returns T sum, the total sum of all the elements of the matrix
  template <class T>
  T mat<T>::sum() const {
    T sum = 0;

    for (size_t i = 0; i < height; ++i) {
      for (size_t j = 0; j < width; ++j) {
        sum += matrix[i * width + j];
      }
    }

    return sum;
  }

  /// @arg accepts a cyfre::mat<T> objects
  /// @returns T sum, the total sum of all the elements of the matrix
  template <typename T>
  T sum(const mat<T> &input) {
    T sum = 0, zero = 0;
    for (auto row: input.matrix)
      sum += std::accumulate(row.begin(), row.end(), zero);
    return sum;
  }
} // namespace cyfre

#endif
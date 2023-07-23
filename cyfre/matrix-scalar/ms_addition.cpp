#ifndef CYFRE_MS_ADDITION_CPP
#define CYFRE_MS_ADDITION_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
  template <class T>
  inline mat<T> mat<T>::operator+(const T scalar) const {
    size_t n = height * width;

    mat<T> scaled_sum;
    scaled_sum.height = height;
    scaled_sum.width = width;
    scaled_sum.matrix = new T[n];

    for (size_t i = 0; i < n; ++i) {
      scaled_sum.matrix[i] = matrix[i] + scalar;
    }

    return scaled_sum;
  }

  template <class T>
  inline void mat<T>::operator+=(const T scalar) {
    size_t n = height * width;

    for (size_t i = 0; i < n; ++i) {
      matrix[i] += scalar;
    }
  }

  template <class T>
  inline mat<T> operator+(const T scalar, const mat<T> &that) {
    size_t n = that.height * that.width;

    mat<T> scaled_sum;
    scaled_sum.height = that.height;
    scaled_sum.width = that.width;
    scaled_sum.matrix = new T[n];

    for (size_t i = 0; i < n; ++i) {
      scaled_sum.matrix[i] = scalar + that.matrix[i];
    }

    return scaled_sum;
  }
} // namespace cyfre

#endif
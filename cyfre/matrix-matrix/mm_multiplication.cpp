#ifndef CYFRE_MM_MULTIPLICATION_CPP
#define CYFRE_MM_MULTIPLICATION_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
  /// ---------------------- Multiplication -----------------------------

  /// @returns matrix multiplication / dot product
  template <class T>
  inline mat<T> mat<T>::operator*(const mat<T> &that) const {
#ifndef CHECK_SHAPE_DISABLE
    if (this->width != that.height) {
      throw std::length_error(
        "\n\nERROR w: mat operator*(const mat& that) const\n"
        "\tmultiplication of incompatible matrix shapes\n"
        "\tmat_a columns is not equal to the mat_b rows\n"
      );
    }
#endif

    mat product;
    product.height = height;
    product.width = that.width;
    product.matrix = new T[height * that.width];

    // naive_mmul
    for (size_t i = 0; i < height; ++i) {
      for (size_t j = 0; j < that.width; ++j) {
        product.matrix[i * height + j] = 0;
        for (size_t k = 0; k < width; ++k) {
          product.matrix[i * height + j] += matrix[i * height + k] * that.matrix[k * that.width + j];
        }
      }
    }

    return product;
  }

  template <class T>
  inline void mat<T>::operator*=(const mat<T> &that) {
#ifndef CHECK_SHAPE_DISABLE
    if (width != height) {
      throw std::length_error(
        "\n\nERROR : mat operator*=(const mat& that) const\n"
        "\tmultiplication of incompatible matrix shapes\n"
        "\twhen multiplying matricies with the *= operator\n"
        "\tthe two matrix involved should be a square matrix\n"
        "\tlefthand matrix is not square\n"
      );
    }

    if (that.width != that.height) {
      throw std::length_error(
        "\n\nERROR : mat operator*=(const mat& that) const\n"
        "\tmultiplication of incompatible matrix shapes\n"
        "\twhen multiplying matricies with the *= operator\n"
        "\tthe two matrix involved should be a square matrix\n"
        "\trighthand matrix is not square\n"
      );
    }
#endif

    *this = *this * that;
  }
} // namespace cyfre

#endif

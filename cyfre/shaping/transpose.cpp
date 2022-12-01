#ifndef CYFRE_TRANSPOSE_CPP
#define CYFRE_TRANSPOSE_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
    /// transpose self
    template <class T>
    void mat<T>::transpose() {
        size_t i, j, k = 0;

        T *rht = new T[width * height];

        for (j = 0; j < width; ++j) {
            for (i = 0; i < height; ++i) {
                rht[k++] = matrix[i * width + j];
            }
        }

        delete[] matrix;
        matrix = rht;
        std::swap(height, width);
    }

    /// @returns a transposed matrix copy
    template <typename T>
    mat<T> transpose(mat<T> input) {
        input.transpose();
        return input;
    }
} // namespace cyfre

#endif
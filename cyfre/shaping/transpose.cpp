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

#ifndef OMPTHREAD
        for (j = 0; j < width; ++j) {
            for (i = 0; i < height; ++i) {
                rht[k++] = matrix[i * width + j];
            }
        }
#else
        if (height * width <= TRANSPOSE_MT_TREASHOLD) {
            for (j = 0; j < width; ++j) {
                for (i = 0; i < height; ++i) {
                    rht[k++] = matrix[i * width + j];
                }
            }
        } else {
            size_t m, o;
    #pragma omp parallel for num_threads(omp_get_max_threads())
            for (size_t n = 0; n < width * height; n++) {
                m = n / width;
                o = n % width;
                rht[n] = matrix[height * o + m];
            }
        }
#endif

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
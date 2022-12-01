#ifndef CYFRE_MS_SUBTRACTION_CPP
#define CYFRE_MS_SUBTRACTION_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
    template <class T>
    inline mat<T> mat<T>::operator-(const T scalar) const {
        size_t n = height * width;

        mat<T> scaled_difference;
        scaled_difference.height = height;
        scaled_difference.width = width;
        scaled_difference.matrix = new T[n];

#ifdef OMPTHREAD
    #pragma omp parallel for num_threads(omp_get_max_threads())
#endif
        for (size_t i = 0; i < n; ++i) {
            scaled_difference.matrix[i] = matrix[i] - scalar;
        }

        return scaled_difference;
    }

    template <class T>
    inline void mat<T>::operator-=(const T scalar) {
        size_t n = height * width;

#ifdef OMPTHREAD
    #pragma omp parallel for num_threads(omp_get_max_threads())
#endif
        for (size_t i = 0; i < n; ++i) {
            matrix[i] -= scalar;
        }
    }

    template <class T>
    inline mat<T> operator-(const T scalar, const mat<T> &that) {
        size_t n = that.height * that.width;

        mat<T> scaled_difference;
        scaled_difference.height = that.height;
        scaled_difference.width = that.width;
        scaled_difference.matrix = new T[n];

#ifdef OMPTHREAD
    #pragma omp parallel for num_threads(omp_get_max_threads())
#endif
        for (size_t i = 0; i < n; ++i) {
            scaled_difference.matrix[i] = scalar - that.matrix[i];
        }

        return scaled_difference;
    }
} // namespace cyfre

#endif
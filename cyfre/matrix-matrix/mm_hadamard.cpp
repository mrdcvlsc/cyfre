#ifndef CYFRE_MM_HADAMARD_CPP
#define CYFRE_MM_HADAMARD_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
    /// @returns hadamard matrix product - element by element multiplication, not to be confused with matrix
    /// multiplication
    template <class T>
    inline void mat<T>::hadamard(const mat<T> &that) {
#ifndef CHECK_SHAPE_DISABLE
        if (this->width != that.width || this->height != that.height) {
            throw std::length_error(
                "\n\nERROR : static mat hadamard(const mat& left, const mat& that) const\n"
                "\thadamard multiplication of two different shaped matrix is not allowed\n"
            );
        }
#endif

        size_t n = height * width;

#ifdef OMPTHREAD
    #pragma omp parallel for num_threads(omp_get_max_threads())
#endif
        for (size_t i = 0; i < n; ++i) {
            matrix[i] *= that.matrix[i];
        }
    }

    /// @returns hadamard matrix product - element by element multiplication, not to be confused with matrix
    /// multiplication
    template <typename T>
    mat<T> hadamard(const mat<T> &left, const mat<T> &right) {
#ifndef CHECK_SHAPE_DISABLE
        if (left.width != right.width || left.height != right.height) {
            throw std::length_error(
                "\n\nERROR : static mat hadamard(const mat& left, const mat& right) const\n"
                "\thadamard multiplication of two different shaped matrix is not allowed\n"
            );
        }
#endif

        size_t n = left.height * left.width;

        mat<T> hproduct;
        hproduct.height = left.height;
        hproduct.width = left.width;
        hproduct.matrix = new T[n];

        for (size_t i = 0; i < n; ++i) {
            hproduct.matrix[i] = left.matrix[i] * right.matrix[i];
        }

        return hproduct;
    }
} // namespace cyfre

#endif
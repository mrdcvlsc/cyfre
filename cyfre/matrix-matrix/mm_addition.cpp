#ifndef CYFRE_MM_ADDITION_CPP
#define CYFRE_MM_ADDITION_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
    /// --------------------------- addition ---------------------------------

    /// @returns element by element addition - old
    template <class T>
    inline mat<T> mat<T>::operator+(const mat<T> &that) const {
#ifndef CHECK_SHAPE_DISABLE
        if (this->width != that.width || this->height != that.height) {
            throw std::length_error(
                "\n\nERROR : mat operator+(const mat& that) const\n"
                "\taddition of two different shaped matrix is not allowed\n"
            );
        }
#endif

        size_t n = height * width;

        mat sum;
        sum.height = height;
        sum.width = width;
        sum.matrix = new T[n];

        for (size_t i = 0; i < n; ++i) {
            sum.matrix[i] = matrix[i] + that.matrix[i];
        }

        return sum;
    }

    template <class T>
    inline void mat<T>::operator+=(const mat<T> &that) {
#ifndef CHECK_SHAPE_DISABLE
        if (this->width != that.width || this->height != that.height) {
            std::string errmsg =
                "\n\nERROR : mat operator+=(const mat& that) const\n"
                "\taddition of two different shaped matrix is not allowed\n";
            throw std::length_error(errmsg);
        }
#endif

        size_t n = height * width;
        for (size_t i = 0; i < n; ++i) {
            matrix[i] += that.matrix[i];
        }
    }
} // namespace cyfre

#endif
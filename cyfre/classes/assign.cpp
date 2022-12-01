#ifndef CYFRE_MM_ASSIGN_CPP
#define CYFRE_MM_ASSIGN_CPP

#include "matrix_class.hpp"
#include <iostream>

namespace cyfre {
    // copy assignment
    template <class T>
    mat<T> &mat<T>::operator=(const mat<T> &original) {
        if (this != &original) {
            size_t n = original.height * original.width;
            height = original.height;
            width = original.width;

            if (matrix != NULL)
                delete[] matrix;
            matrix = new T[n];
            std::memcpy(matrix, original.matrix, sizeof(T) * n);
        }
        return *this;
    }

    // move assignment
    template <class T>
    mat<T> &mat<T>::operator=(mat<T> &&temporary) {
        if (this != &temporary) {
            if (matrix != NULL)
                delete[] matrix;

            height = temporary.height;
            width = temporary.width;
            matrix = temporary.matrix;

            temporary.height = 0;
            temporary.width = 0;
            temporary.matrix = NULL;
        }
        return *this;
    }
} // namespace cyfre

#endif
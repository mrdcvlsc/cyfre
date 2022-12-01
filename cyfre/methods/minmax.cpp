#ifndef CYFRE_MINMAX_CPP
#define CYFRE_MINMAX_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
    template <class T>
    T mat<T>::max() {
        size_t n = height * width;

        if (!n) {
            throw std::range_error("ERROR : T max() - the matrix is empty, there is no maximum");
        }

        T maximum = matrix[0];
        for (size_t i = 1; i < n; ++i) {
            if (matrix[i] > maximum) {
                maximum = matrix[i];
            }
        }
    }

    template <class T>
    T mat<T>::min() {
        size_t n = height * width;

        if (!n) {
            throw std::range_error("ERROR : T min() - the matrix is empty, there is no minimum");
        }

        T minimum = matrix[0];
        for (size_t i = 1; i < n; ++i) {
            if (matrix[i] < minimum) {
                minimum = matrix[i];
            }
        }
    }
} // namespace cyfre

#endif
#ifndef CYFRE_APPLY_CPP
#define CYFRE_APPLY_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
    // ================ applying function ==============================
    template <class T>
    void mat<T>::apply(std::function<T(T)> function_name) {
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                matrix[i * width + j] = function_name(matrix[i * width + j]);
            }
        }
    }
} // namespace cyfre

#endif
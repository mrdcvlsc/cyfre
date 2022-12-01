#ifndef CYFRE_POWER_CPP
#define CYFRE_POWER_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
    // ============================== MATRIX EXPOENTIAL ==============================

    /// @returns raised matrix to a certain number 'p'
    /// @note raising to a negative integer(inverse) is not supported yet but will be in the future
    template <class T>
    void mat<T>::power(size_t p) {
#ifndef CHECK_SHAPE_DISABLE
        if (width != height) {
            throw std::length_error("\n\nERROR : mat.power(size_t p)\n\tcannot raise a non-square matrix\n");
        } else if (p < 0) {
            throw std::domain_error(
                "\n\nERROR : mat.power(size_t p)\n\trasing to a negative number(-1 inverse) is not supported yet\n"
            );
        }
#endif

        if (p == 0) {
            mat<T> identity(TYPE::IDENTITY, width);
            *this = identity;
        } else if (p >= 2) {
            mat<T> multiplier = *this;
            for (size_t i = 2; i <= p; ++i) {
                *this *= multiplier;
            }
        }
    }

    /// @returns raised matrix to a certain number 'p'
    /// @note raising to a negative integer(inverse) is not supported yet but will be in the future
    template <typename T>
    mat<T> power(mat<T> base, size_t p) {
#ifndef CHECK_SHAPE_DISABLE
        if (base.width != base.height) {
            throw std::length_error("\n\nERROR : mat.power(size_t p)\n\tcannot raise a non-square matrix\n");
        } else if (p < 0) {
            throw std::length_error(
                "\n\nERROR : mat.power(size_t p)\n\trasing to a negative number(-1 inverse) is not supported yet\n"
            );
        }
#endif

        if (p == 0) {
            mat<T> identity(IDENTITY, base.width);
            base = identity;
        } else if (p >= 2) {
            mat<T> multiplier = base;
            for (size_t i = 2; i <= p; ++i) {
                base *= multiplier;
            }
        }
        return base;
    }
} // namespace cyfre

#endif
#ifndef CYFRE_INVERSE_CPP
#define CYFRE_INVERSE_CPP

#include "../classes/matrix_class.hpp"
#include <iostream>

namespace cyfre {
    // ============================= INVERSE MATRIX ================================

    /// converts matrix to it's inverse form
    template <class T>
    void mat<T>::inv() {
#ifndef CHECK_SHAPE_DISABLE
        if (height != width)
            throw std::length_error("\n\nERROR : cyfre::mat::inv() - cannot inverse a non-square matrix");
#endif

        mat<T> inverse(TYPE::IDENTITY, height);

        auto nonzrow = [](const mat<T> &input, size_t i, size_t j) -> long long int {
            for (size_t r = i; r < input.height; ++r) {
                if (input.matrix[r * input.width + j] != 0) {
                    return r;
                }
            }
            return -1;
        };

        auto fix_pivot = [&inverse](mat<T> &input, size_t pi, size_t pj) {
            for (size_t i = 0; i < input.height; ++i) {
                if (i != pi) {
                    inverse.row_scale(-input.matrix[i * input.width + pj], pi, i);
                    input.row_scale(-input.matrix[i * input.width + pj], pi, i);
                }
            }
        };

        auto make_pivot = [&inverse](mat<T> &input, size_t pi, size_t pj) {
            inverse.scale_row(pi, DIV, input.matrix[pi * input.width + pj]);
            input.scale_row(pi, DIV, input.matrix[pi * input.width + pj]);
        };

        size_t cpi = 0;
        size_t cpj = 0;

        while (cpi < height && cpj < width) {
            long long int nonzerorow = nonzrow(*this, cpi, cpj);

            if (nonzerorow < 0) {
                cpj++;
                continue;
            }

            if (nonzerorow != (long long int) cpi) {
                this->row_swap(cpi, nonzerorow);
                inverse.row_swap(cpi, nonzerorow);
            }

            if (matrix[cpi * width + cpj] != 1)
                make_pivot(*this, cpi, cpj);
            fix_pivot(*this, cpi, cpj);
            cpi++;
            cpj++;
        }

        for (size_t i = 0; i < height; ++i) {
            if (matrix[i * width + i] == 0)
                throw std::domain_error(
                    "\n\nERROR: cyfre::mat::inv() - matrix determinant is zero, cannot invert matrix"
                );
        }

        delete[] matrix;
        matrix = inverse.matrix;
        inverse.matrix = nullptr;
        inverse.height = 0;
        inverse.width = 0;
    }

    /// @returns inverse of a matrix
    template <typename T>
    mat<T> inv(mat<T> input) {
        input.inv();
        return input;
    }
} // namespace cyfre

#endif
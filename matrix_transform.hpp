#ifndef MATRIX_TRANSFORM_HPP
#define MATRIX_TRANSFORM_HPP

#include "matrix_class.hpp"

namespace cyfre
{
    /// @returns a transposed self copy
    template<typename T>
    mat<T> transpose(mat<T> input)
    {
        for(size_t i=0; i<input.height; ++i)
        {
            for(size_t j=0; j<input.width; ++j)
            {
                input.matrix[j][i] = input.matrix[i][j]; 
            }
        }
        return input;
    }

    // rotate left - 90 degree

    // rotate right - 90 degree

    // rotate 180 degree

    // mirror/reflect x,y,main-diagonal & left-diagonal axis

    // flaten into x axis, or y axis

    /// @returns echelon form of a matrix
    template<typename T>
    mat<T> echelon(mat<T> input)
    {

    }

    /// @returns reduced echelon form of a matrix
    template<typename T>
    mat<T> echelon_reduced(mat<T> input)
    {
        
    }
}

#endif
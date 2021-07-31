#ifndef MATRIX_TRANSFORM_HPP
#define MATRIX_TRANSFORM_HPP

#include "matrix_class.hpp"

namespace cyfre
{
    /// @returns a transposed self copy
    template<typename T>
    mat<T> transpose(mat<T> input)
    {
        input.transpose();
        return input;
    }

    // rotate left - 90 degree

    // rotate right - 90 degree

    // rotate 180 degree

    // mirror/reflect x,y,main-diagonal & left-diagonal axis

    // flaten into x axis, or y axis

    template<typename T>
    T det(mat<T> input)
    {
        #ifndef CHECK_SHAPE_DISABLE
        if(input.width!=input.height)
        {
            std::cerr<<"\n\nERROR : T det(mat<T> input) - non-square matricies has no determinant\n";
            exit(1);
        }
        #endif

        auto nonzrow = [](const mat<T>& input, size_t i, size_t j) -> long long int
        {
            for(size_t r=i; r<input.height; ++r)
            {
                if(input.matrix[r*input.width+j]!=0)
                {
                    return r;
                }
            }
            return -1;
        };

        auto fix_nonzero_pivot = [](mat<T>& input, size_t pi, size_t pj)
        {
            for(size_t i=pi+1; i<input.height; ++i)
            {
                input.row_scale(-(input.matrix[i*input.width+pj]/input.matrix[pi*input.width+pj]),pi,i);
            }
        };

        auto diag_product = [](const mat<T>& input)
        {
            T diagonal_product = 1;
            for(size_t i=0; i<input.height && i<input.width; ++i)
            {
                diagonal_product*=input.matrix[i*input.width+i];
            }
            return diagonal_product;
        };

        size_t cpi = 0;
        size_t cpj = 0;
        while(cpi<input.height && cpj<input.width)
        {
            long long int nonzerorow = nonzrow(input,cpi,cpj);
    
            if(nonzerorow<0)
            {
                cpj++;
                continue;
            }

            if(nonzerorow!=cpi)
            {
                input.row_swap(cpi,nonzerorow);
            }

            fix_nonzero_pivot(input,cpi,cpj);
            cpi++;
            cpj++;
        }
        return diag_product(input);
    }

    /// @returns reduced row echelon form of a matrix
    template<typename T>
    mat<T> ref(mat<T> input)
    {
        input.ref();
        return input;
    }

    /// @returns reduced row echelon form of a matrix
    template<typename T>
    mat<T> rref(mat<T> input)
    {
        input.rref();
        return input;
    }

    /// @returns inverse of a matrix
    template<typename T>
    mat<T> inv(mat<T> input)
    {
        input.inv();
        return input;
    }
}

#endif
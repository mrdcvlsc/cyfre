#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "cyfre.hpp"

namespace cyfre
{
    /// copies a cyfre::mat<T> object, then the values of that copy
    /// @returns a scaled copy cyfre::mat<T> object
    template<typename T>
    mat<T> scale(mat<T> input, const SCALAR_OPERATIONS scalar_operation, const T scalar)
    {
        auto scalar_function = [](SCALAR_OPERATIONS scalar_operation, const T scalar, typename std::vector<T>::iterator index)->void
        {
            switch(scalar_operation)
            {
            case ADD: (*index) += scalar; break;
            case SUB: (*index) -= scalar; break;
            case MUL: (*index) *= scalar; break;
            case DIV: (*index) /= scalar; break;
            default:
                std::cerr<<"\n\nERROR : void scale(SCALAR_OPERATIONS scalar_operation, T scalar="<<scalar_operation<<")\n";
                std::cerr<<"\tSCALAR_OPERATIONS has invalid argument value, the valid SCALAR_OPERATION values are: ADD, SUB, MULL, and DIV\n";
                exit(1);
            }
        };

        for(size_t i=0; i<input.height; ++i)
        {
            for(size_t j=0; j<input.width; ++j)
            {
                scalar_function(scalar_operation,scalar,(*(input.matrix.begin()+i)).begin()+j);
            }
        }
        return input;
    }

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

    /// @returns hadamard matrix product - element by element multiplication, not to be confused with matrix multiplication
    template<typename T>
    mat<T> hadamard(const mat<T>& left, const mat<T>& right)
    {
        if(left.width!=right.width || left.height!=right.height)
        {
            std::cerr<<"\n\nERROR : static mat hadamard(const mat& left, const mat& right) const\n";
            std::cerr<<"\thadamard multiplication of two different shaped matrix is not allowed\n";
            exit(1);
        }
        
        mat<T> answer = left;
        for(size_t i=0; i<answer.height; ++i)
        {
            for(size_t j=0; j<answer.width; ++j) answer.matrix[i][j]*=right.matrix[i][j];
        }

        return answer;
    }
}

#endif
#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "matrix_class.hpp"

namespace cyfre
{

    /// @returns hadamard matrix product - element by element multiplication, not to be confused with matrix multiplication
    template<typename T>
    mat<T> hadamard(const mat<T>& left, const mat<T>& right)
    {
        #ifndef CHECK_SHAPE_DISABLE
        if(left.width!=right.width || left.height!=right.height)
        {
            std::cerr<<"\n\nERROR : static mat hadamard(const mat& left, const mat& right) const\n";
            std::cerr<<"\thadamard multiplication of two different shaped matrix is not allowed\n";
            exit(1);
        }
        #endif
        
        mat<T> answer = left;
        for(size_t i=0; i<answer.height; ++i)
        {
            for(size_t j=0; j<answer.width; ++j) answer.matrix[i*answer.width+j]*=right.matrix[i*right.width+j];
        }

        return answer;
    }

    /// @returns raised matrix to a certain number 'p'
    /// @note raising to a negative integer(inverse) is not supported yet but will be in the future
    template<typename T>
    mat<T> power(mat<T> base, const int p)
    {
        #ifndef CHECK_SHAPE_DISABLE
        if(base.width!=base.height)
        {
            std::cerr<<"\n\nERROR : mat.power(size_t p)\n\tcannot raise a non-square matrix\n";
            exit(1);
        }
        else if(p<0)
        {
            std::cerr<<"\n\nERROR : mat.power(size_t p)\n\trasing to a negative number(-1 inverse) is not supported yet\n";
            exit(1);
        }
        #endif

        if(p==0)
        {
            mat<T> identity(IDENTITY,base.width);
            base = identity;
        }
        else if(p>=2)
        {
            mat<T> multiplier = base;
            for(size_t i=2; i<=p; ++i)
            {
                base*=multiplier;
            }
        }
        return base;
    }

    // p matrix

    // sudo-inverse

    // inverse

    // diagonalize

    // matrix^exponent - power

    // euler^matrix
}

#endif
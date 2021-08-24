#ifndef CYFRE_MM_HADAMARD_CPP
#define CYFRE_MM_HADAMARD_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    /// @returns hadamard matrix product - element by element multiplication, not to be confused with matrix multiplication
    template<class T>
    inline void mat<T>::hadamard(const mat<T>& that)
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"void hadamard(const mat& that)\n";
        #endif

        #ifndef CHECK_SHAPE_DISABLE
        if(this->width!=that.width || this->height!=that.height)
        {
            throw std::length_error(
                "\n\nERROR : static mat hadamard(const mat& left, const mat& that) const\n"
                "\thadamard multiplication of two different shaped matrix is not allowed\n"
            );
        }
        #endif
        
        size_t n = height*width;

        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<n; ++i)
        {
            matrix[i]*=that.matrix[i];
        }

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif
    }

    /// @returns hadamard matrix product - element by element multiplication, not to be confused with matrix multiplication
    template<typename T>
    mat<T> hadamard(const mat<T>& left, const mat<T>& right)
    {
        #ifndef CHECK_SHAPE_DISABLE
        if(left.width!=right.width || left.height!=right.height)
        {
            throw std::length_error(
                "\n\nERROR : static mat hadamard(const mat& left, const mat& right) const\n"
                "\thadamard multiplication of two different shaped matrix is not allowed\n"
            );
        }
        #endif
        
        size_t n = left.height*left.width;

        mat<T> hproduct;
        hproduct.height = left.height;
        hproduct.width = left.width;
        hproduct.matrix = new T[n];

        for(size_t i=0; i<n; ++i)
        {
            hproduct.matrix[i] = left.matrix[i] * right.matrix[i];
        }

        return hproduct;
    }
}

#endif
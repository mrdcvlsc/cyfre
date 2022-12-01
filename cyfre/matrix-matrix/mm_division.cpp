#ifndef CYFRE_MM_DIVISION_CPP
#define CYFRE_MM_DIVISION_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    /// ---------------------- Division -----------------------------

    /// @returns element by element division
    template<class T>
    inline mat<T> mat<T>::operator/(const mat<T>& that) const
    {
        #ifndef CHECK_SHAPE_DISABLE
        if(this->width!=that.width || this->height!=that.height)
        {
            throw std::length_error(
                "\n\nERROR : mat operator/(const mat& that) const\n"
                "\taddition of two different shaped matrix is not allowed\n"
            );
        }
        #endif
        
        size_t n = height*width;

        mat quotient;
        quotient.height = height;
        quotient.width = width;
        quotient.matrix = new T[n];
        
        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<n; ++i)
        {
            if(that.matrix[i]==0)
            {
                throw std::domain_error("ERROR : inline mat operator/(const mat& that) const - divide by zero");
            }
            quotient.matrix[i] = matrix[i] / that.matrix[i];
        }

        return quotient;
    }

    template<class T>
    inline void mat<T>::operator/=(const mat<T>& that)
    {
        #ifndef CHECK_SHAPE_DISABLE
        if(this->width!=that.width || this->height!=that.height)
        {
            throw std::length_error(
                std::string("\n\nERROR : mat operator/=(const mat& that) const\n")+
                "\taddition of two different shaped matrix is not allowed\n"
            );
        }
        #endif

        size_t n = height*width;
        
        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<n; ++i)
        {
            if(that.matrix[i]==0)
            {
                throw std::domain_error("ERROR : inline void operator/=(const mat& that) - divide by zero");
            }
            matrix[i]/=that.matrix[i];
        }
    }
}

#endif
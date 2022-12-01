#ifndef CYFRE_MM_SUBTRACTION_CPP
#define CYFRE_MM_SUBTRACTION_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    /// --------------------------- subtraction ---------------------------------

    /// @returns element by element subtraction - old
    template<class T>
    inline mat<T> mat<T>::operator-(const mat<T>& that) const
    {
        #ifndef CHECK_SHAPE_DISABLE
        if(this->width!=that.width || this->height!=that.height)
        {
            std::string errmsg = "\n\nERROR : mat operator-(const mat& that) const\n"
                                    "\tsubtraction of two different shaped matrix is not allowed\n";
            throw std::length_error(errmsg);
        }
        #endif
        
        size_t n = height*width;

        mat difference;
        difference.height = height;
        difference.width = width;
        difference.matrix = new T[n];

        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<n; ++i)
        {
            difference.matrix[i] = matrix[i] - that.matrix[i];
        }

        return difference;
    }

    template<class T>
    inline void mat<T>::operator-=(const mat<T>& that)
    {
        #ifndef CHECK_SHAPE_DISABLE
        if(this->width!=that.width || this->height!=that.height)
        {
            std::string errmsg = "\n\nERROR : mat operator-=(const mat& that) const\n"
                                    "\tsubtraction of two different shaped matrix is not allowed\n";
            throw std::length_error(errmsg);
        }
        #endif
        
        size_t n = height*width;

        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<n; ++i)
        {
            matrix[i] -= that.matrix[i];
        }
    }
}

#endif
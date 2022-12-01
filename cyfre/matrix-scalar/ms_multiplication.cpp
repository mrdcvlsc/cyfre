#ifndef CYFRE_MS_MULTIPLIACTION_CPP
#define CYFRE_MS_MULTIPLIACTION_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    template<class T>
    inline mat<T> mat<T>::operator*(const T scalar) const
    {
        size_t n = height*width;
        
        mat<T> scaled_product;
        scaled_product.height = height;
        scaled_product.width = width;
        scaled_product.matrix = new T[n];

        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<n; ++i)
        {
            scaled_product.matrix[i] = matrix[i] * scalar;
        }

        return scaled_product;
    }

    template<class T>
    inline void mat<T>::operator*=(const T scalar)
    {
        size_t n = height*width;

        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<n; ++i)
        {
            matrix[i] *= scalar;
        }
    }

    template<class T>
    inline mat<T> operator*(const T scalar, const mat<T>& that)
    {
        size_t n = that.height*that.width;

        mat<T> scaled_product;
        scaled_product.height = that.height;
        scaled_product.width = that.width;
        scaled_product.matrix = new T[n];

        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<n; ++i)
        {
            scaled_product.matrix[i] = scalar * that.matrix[i];
        }

        return scaled_product;
    }
}

#endif
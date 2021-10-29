#ifndef CYFRE_MS_MULTIPLIACTION_CPP
#define CYFRE_MS_MULTIPLIACTION_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    template<class T>
    inline mat<T> mat<T>::operator*(const T scalar) const
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"inline mat operator*(const T scalar) const\n";
        #endif

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

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif

        return scaled_product;
    }

    template<class T>
    inline void mat<T>::operator*=(const T scalar)
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"inline void operator*=(const T scalar)\n";
        #endif

        size_t n = height*width;

        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<n; ++i)
        {
            matrix[i] *= scalar;
        }

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif
    }

    template<class T>
    inline mat<T> operator*(const T scalar, const mat<T>& that)
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"template<typename S> inline friend mat operator*(const S scalar, const mat& that)\n";
        #endif

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

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif

        return scaled_product;
    }
}

#endif
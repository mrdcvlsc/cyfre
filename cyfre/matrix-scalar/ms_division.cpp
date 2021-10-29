#ifndef CYFRE_MS_DIVISION_CPP
#define CYFRE_MS_DIVISION_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    template<class T>
    inline mat<T> mat<T>::operator/(const T scalar) const
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"inline mat operator/(const T scalar) const\n";
        #endif

        if(scalar==0)
        {
            throw std::domain_error("ERROR : inline mat operator/(const T scalar) const - divide by zero");
        }

        size_t n = height*width;

        mat<T> scaled_quotient;
        scaled_quotient.height = height;
        scaled_quotient.width = width;
        scaled_quotient.matrix = new T[n];
        
        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<n; ++i)
        {
            scaled_quotient.matrix[i] = matrix[i] / scalar;
        }

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif

        return scaled_quotient;
    }

    template<class T>
    inline void mat<T>::operator/=(const T scalar)
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"inline void operator/=(const T scalar)\n";
        #endif

        size_t n = height*width;
        
        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<n; ++i)
        {
            if(scalar==0)
            {
                throw std::domain_error("ERROR : inline void operator/=(const T scalar) - divide by zero");
            }
            matrix[i] /= scalar;
        }

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif
    }

    template<class T>
    inline mat<T> operator/(const T scalar, const mat<T>& that)
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"template<typename S> inline friend mat operator/(const S scalar, const mat& that)\n";
        #endif

        size_t n = that.height * that.width;
        
        mat<T> scaled_quotient;
        scaled_quotient.height = that.height;
        scaled_quotient.width = that.width;
        scaled_quotient.matrix = new T[n];

        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<n; ++i)
        {
                if(that.matrix[i]==0)
                {
                    throw std::domain_error("ERROR : template<typename S> inline friend mat operator/(const S scalar, const mat& that) - divide by zero");
                }
                scaled_quotient.matrix[i] = scalar/that.matrix[i];
        }

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif

        return scaled_quotient;
    }
}

#endif
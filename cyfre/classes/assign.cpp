#ifndef CYFRE_MM_ASSIGN_CPP
#define CYFRE_MM_ASSIGN_CPP

#include <iostream>
#include "matrix_class.hpp"

namespace cyfre
{
    template<class T>
    mat<T>& mat<T>::operator=(const mat<T>& original)
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"mat(const mat& original)\n";
        #endif

        size_t n = original.height*original.width;

        if(height && (height!=original.height || width!=original.width))
        {
            delete [] matrix;
            matrix = new T[n];
        }
        else if(!height) matrix = new T[n];

        height = original.height;
        width =  original.width;

        // previous copy:
        // #ifdef OMPTHREAD
        // #pragma omp parallel for num_threads(omp_get_max_threads())
        // #endif
        // for(size_t i=0; i<n; ++i)
        // {
        //     matrix[i] = original.matrix[i];
        // }

        // new copy: it seems a single thread memcpy is faster than m-threaded assignments for memory <= 8GB
        std::memcpy(matrix,original.matrix,sizeof(T)*n);

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif

        return *this;
    }
}

#endif
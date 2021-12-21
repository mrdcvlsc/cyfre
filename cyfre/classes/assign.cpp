#ifndef CYFRE_MM_ASSIGN_CPP
#define CYFRE_MM_ASSIGN_CPP

#include <iostream>
#include "matrix_class.hpp"

namespace cyfre
{
    // copy assignment
    template<class T>
    mat<T>& mat<T>::operator=(const mat<T>& original)
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"mat(const mat& original)\n";
        #endif

        if(matrix!=NULL) delete [] matrix;

        size_t n = original.height*original.width;

        height = original.height;
        width =  original.width;

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
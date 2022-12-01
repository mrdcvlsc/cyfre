#ifndef CYFRE_INDEXING_CPP
#define CYFRE_INDEXING_CPP

#include <iostream>
#include "matrix_class.hpp"

namespace cyfre
{
    template<class T>
    inline T& mat<T>::operator()(size_t i, size_t j)
    {
        #ifndef CHECK_RANGE_DISABLE
        if((i < 0) ^ (i > height-1))
        {
            throw std::out_of_range(
                "\n\nERROR : T& operator()(size_t i, size_t j)\n"
                "\tthe given row index is out of bound\n"
            );
        }
        else if((j < 0) ^ (j > width-1))
        {
            throw std::out_of_range(
                "\n\nERROR : T& operator()(size_t i, size_t j)\n"
                "\tthe given column index is out of bound\n"
            );
        }
        #endif

        return matrix[i*width+j];
    }
    
    template<class T>
    inline const T& mat<T>::operator()(size_t i, size_t j) const
    {
        #ifndef CHECK_RANGE_DISABLE
        if((i < 0) ^ (i > height-1))
        {
            throw std::out_of_range(
                "\n\nERROR : const T& operator()(size_t i, size_t j)\n"
                "\tthe given row index is out of bound\n"
            );
        }
        else if((j < 0) ^ (j > width-1))
        {
            throw std::out_of_range(
                "\n\nERROR : const T& operator()(size_t i, size_t j)\n"
                "\tthe given column index is out of bound\n"
            );
        }
        #endif

        return matrix[i*width+j];
    }
}

#endif
#ifndef CYFRE_COMPARISION_CPP
#define CYFRE_COMPARISION_CPP

#include <iostream>
#include "matrix_class.hpp"

namespace cyfre
{
    /// compare matrix
    template<class T>
    inline bool mat<T>::operator==(const mat<T>& that) const
    {
        size_t n = width*height;
        for(size_t i=0; i<n; ++i)
        {
            if(matrix[i]!=that.matrix[i])
            {
                return false;
            }
        }

        return true;
    }

    template<class T>
    inline bool mat<T>::operator!=(const mat<T>& that) const
    {
        return !(*this==that);
    }
}

#endif
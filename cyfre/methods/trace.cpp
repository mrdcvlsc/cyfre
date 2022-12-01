#ifndef CYFRE_TRACE_CPP
#define CYFRE_TRACE_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    /// @returns T trace_total, the total sum of the main diagonal
    template<class T>
    T mat<T>::trace() const
    {
        #ifndef CHECK_SHAPE_DISABLE
        if(width!=height)
        {
            throw std::length_error(
                "\n\nERROR : mat.trace()\n"
                "\tthe matrix is not a square matrix, cannot get trace\n"
            );
        }
        #endif

        T trace_total = 0;
        for(size_t i=0; i<height; ++i) trace_total+=matrix[i*width+i];

        return trace_total;
    }

    /// @arg accepts a cyfre::mat<T> objects
    /// @returns T trace_total, the total sum of the main diagonal
    template<typename T>
    T trace(const mat<T>& input)
    {
        #ifndef CHECK_SHAPE_DISABLE
        if(input.width!=input.height)
        {
            std::cerr<<"\n\nERROR : mat.trace()\n";
            std::cerr<<"\tthe matrix is not a square matrix, cannot get trace\n";
            exit(1);
        }
        #endif

        T trace_total = 0;
        for(size_t i=0; i<input.height; ++i) trace_total+=input.matrix[i*input.width+i];
        return trace_total;
    }
}

#endif
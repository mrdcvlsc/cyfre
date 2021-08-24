#ifndef CYFRE_SUM_CPP
#define CYFRE_SUM_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    /// @returns T sum, the total sum of all the elements of the matrix
    template<class T>
    T mat<T>::sum() const
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"T sum() const\n";
        #endif

        T sum = 0;

        for(size_t i=0; i<height; ++i)
        {
            for(size_t j=0; j<width; ++j)
            {
                sum += matrix[i*width+j];
            }
        }

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif

        return sum;
    }

    /// @arg accepts a cyfre::mat<T> objects
    /// @returns T sum, the total sum of all the elements of the matrix
    template<typename T>
    T sum(const mat<T>& input)
    {
        T sum = 0, zero = 0;
        for(auto row: input.matrix) sum+=std::accumulate(row.begin(),row.end(),zero);
        return sum;
    }
}

#endif
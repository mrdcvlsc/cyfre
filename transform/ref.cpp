#ifndef CYFRE_REF_CPP
#define CYFRE_REF_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
     /// converts matrix to row echelon form of a matrix
    template<class T>
    void mat<T>::ref()
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"void ref()\n";
        #endif

        auto nonzrow = [](const mat<T>& input, const size_t i, const size_t j) -> long long int
        {
            for(size_t r=i; r<input.height; ++r)
            {
                if(input.matrix[r*input.width+j]!=0)
                {
                    return r;
                }
            }
            return -1;
        };

        auto fix_nonzero_pivot = [](mat<T>& input, const size_t pi, const size_t pj)
        {
            for(size_t i=pi+1; i<input.height; ++i)
            {
                input.row_scale(-(input.matrix[i*input.width+pj]/input.matrix[pi*input.width+pj]),pi,i);
            }
        };

        size_t cpi = 0;
        size_t cpj = 0;

        while(cpi<height && cpj<width)
        {
            long long int nonzerorow = nonzrow(*this,cpi,cpj);
    
            if(nonzerorow<0)
            {
                cpj++;
                continue;
            }

            if(nonzerorow!=(long long int)cpi)
            {
                row_swap(cpi,nonzerorow);
            }

            fix_nonzero_pivot(*this,cpi,cpj);
            cpi++;
            cpj++;
        }

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif
    }

    /// @returns reduced row echelon form of a matrix
    template<typename T>
    mat<T> ref(mat<T> input)
    {
        input.ref();
        return input;
    }
}

#endif
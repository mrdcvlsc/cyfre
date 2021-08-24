#ifndef CYFRE_RREF_CPP
#define CYFRE_RREF_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    /// converts matrix to reduced row echelon form of a matrix
    template<class T>
    void mat<T>::rref()
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"void rref()\n";
        #endif

        auto nonzrow = [](const mat<T>& input, size_t i, size_t j) -> long long int
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

        auto fix_pivot = [](mat<T>& input, size_t pi, size_t pj)
        {
            for(size_t i=0; i<input.height; ++i)
            {
                if(i!=pi)
                {
                    input.row_scale(-input.matrix[i*input.width+pj],pi,i);
                }
            }
        };

        auto make_pivot = [](mat<T>& input, size_t pi, size_t pj)
        {
            input.scale_row(pi,DIV,input.matrix[pi*input.width+pj]);
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

            if(nonzerorow!=(long long int)cpi) this->row_swap(cpi,nonzerorow);
            if(matrix[cpi*width+cpj]!=1) make_pivot(*this,cpi,cpj);
            fix_pivot(*this,cpi,cpj);
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
    mat<T> rref(mat<T> input)
    {
        input.rref();
        return input;
    }
}

#endif
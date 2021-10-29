#ifndef CYFRE_PADDING_CPP
#define CYFRE_PADDING_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    /// padding self
    template<class T>
    void mat<T>::padding(size_t pad_height, size_t pad_width)
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"void padding()\n";
        #endif

        if(pad_height==0 && pad_width==0)
        {
            return;
        }
        else if(pad_height<0) throw std::length_error("error in padding(): pad_height should not be < 0");
        else if(pad_width<0)  throw std::length_error("error in padding(): pad_width should not be < 0");

        size_t new_height = height+(2*pad_height);
        size_t new_width  = width+(2*pad_width);
        size_t dim_total = new_height*new_width;

        T* padded_matrix = new T[dim_total];

        #ifdef OMPTHREAD
        #pragma omp parallel for num_threads(omp_get_max_threads())
        #endif
        for(size_t i=0; i<dim_total; ++i) padded_matrix[i] = 0;

        size_t i=pad_height, j=pad_width;
        #ifdef OMPTHREAD
        #pragma omp parallel private(i,j)
        #endif
        for(i=pad_height; i<pad_height+height; ++i)
        {
            #ifdef OMPTHREAD
            #pragma omp for
            #endif
            for(j=pad_width; j<pad_width+width; ++j)
            {
                padded_matrix[i*new_width+j] = matrix[(i-pad_height)*width+(j-pad_width)];
            }
        }

        delete [] matrix;
        matrix = padded_matrix;
        height = new_height;
        width  = new_width;

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif
    }

    /// padding self
    template<class T>
    void mat<T>::padding(size_t pad_length)
    {
        padding(pad_length,pad_length);
    }

    /// @returns a paddingd matrix copy
    template<typename T>
    mat<T> padding(mat<T> input, size_t pad_height, size_t pad_width)
    {
        input.padding(pad_height,pad_width);
        return input;
    }

    /// @returns a paddingd matrix copy
    template<typename T>
    mat<T> padding(mat<T> input, size_t pad_length)
    {
        input.padding(pad_length,pad_length);
        return input;
    }
}

#endif
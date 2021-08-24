#ifndef CYFRE_MM_MULTIPLICATION_CPP
#define CYFRE_MM_MULTIPLICATION_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    /// ---------------------- Multiplication -----------------------------
        
    /// @returns matrix multiplication / dot product
    template<class T>
    inline mat<T> mat<T>::operator*(const mat<T>& that) const
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"inline mat operator*(const mat& that) const\n";
        #endif

        #ifndef CHECK_SHAPE_DISABLE
        if(this->width!=that.height)
        {
            throw std::length_error
            (
                "\n\nERROR : mat operator*(const mat& that) const\n"
                "\tmultiplication of incompatible matrix shapes\n"
                "\tmat_a columns is not equal to the mat_b rows\n"
            );
        }
        #endif

        size_t i,j,k=0;

        mat product;
        product.height = height;
        product.width = that.width;
        product.matrix = new T[height*that.width];

        T* at = new T[width*height];

        #ifndef OMPTHREAD
        for(size_t j=0; j<width; ++j)
        {
            for(size_t i=0; i<height; ++i)
            {
                at[k++] = matrix[i*width+j];
            }
        }
        #else
        if(height*width<=TRANSPOSE_MT_TREASHOLD)
        {
            for(size_t j=0; j<width; ++j)
            {
                for(size_t i=0; i<height; ++i)
                {
                    at[k++] = matrix[i*width+j];
                }
            }
        }
        else
        {
            size_t m, o;
            #pragma omp parallel for num_threads(omp_get_max_threads())
            for(size_t n = 0; n<width*height; n++)
            {
                m = n/width;
                o = n%width;
                at[n] = matrix[height*o+m];
            }
        }
        #endif

        T dot_sum;
        
        #ifdef OMPTHREAD
        #pragma omp parallel private(i,j,k)
        #endif
        {
            #ifdef OMPTHREAD
            #pragma omp for
            #endif
            for(i=0; i<height; ++i)
            {
                for(k=0; k<width; ++k)
                {                        
                    for(j=0; j<that.width; ++j)
                    {
                        product.matrix[i*that.width+j] += at[k*height+i]*that.matrix[k*that.height+j];
                    }
                }
            }
        }

        delete [] at;                

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif

        return product;
    }

    template<class T>
    inline void mat<T>::operator*=(const mat<T>& that)
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"inline void operator*=(const mat& that)\n";
        #endif

        #ifndef CHECK_SHAPE_DISABLE
        if(width!=height)
        {
            throw std::length_error(
                "\n\nERROR : mat operator*=(const mat& that) const\n"
                "\tmultiplication of incompatible matrix shapes\n"
                "\twhen multiplying matricies with the *= operator\n"
                "\tthe two matrix involved should be a square matrix\n"
                "\tlefthand matrix is not square\n"
            );
        }

        if(that.width!=that.height)
        {
            throw std::length_error(
                "\n\nERROR : mat operator*=(const mat& that) const\n"
                "\tmultiplication of incompatible matrix shapes\n"
                "\twhen multiplying matricies with the *= operator\n"
                "\tthe two matrix involved should be a square matrix\n"
                "\trighthand matrix is not square\n"
            );
        }
        #endif

        *this = *this * that;

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif
    }
}

#endif
#ifndef CYFRE_POWER_CPP
#define CYFRE_POWER_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    // ============================== MATRIX EXPOENTIAL ==============================

    /// @returns raised matrix to a certain number 'p'
    /// @note raising to a negative integer(inverse) is not supported yet but will be in the future
    template<class T>
    void mat<T>::power(size_t p)
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"void power(size_t p)\n";
        #endif

        #ifndef CHECK_SHAPE_DISABLE
        if(width!=height)
        {
            throw std::length_error("\n\nERROR : mat.power(size_t p)\n\tcannot raise a non-square matrix\n");
        }
        else if(p<0)
        {
            throw std::domain_error("\n\nERROR : mat.power(size_t p)\n\trasing to a negative number(-1 inverse) is not supported yet\n");
        }
        #endif

        if(p==0)
        {
            mat<T> identity(TYPE::IDENTITY,width);
            *this = identity;
        }
        else if(p>=2)
        {
            mat<T> multiplier = *this;
            for(size_t i=2; i<=p; ++i)
            {
                *this*=multiplier;
            }
        }

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif
    }

    /// @returns raised matrix to a certain number 'p'
    /// @note raising to a negative integer(inverse) is not supported yet but will be in the future
    template<typename T>
    mat<T> power(mat<T> base, size_t p)
    {
        #ifndef CHECK_SHAPE_DISABLE
        if(base.width!=base.height)
        {
            throw std::length_error("\n\nERROR : mat.power(size_t p)\n\tcannot raise a non-square matrix\n");
        }
        else if(p<0)
        {
            throw std::length_error("\n\nERROR : mat.power(size_t p)\n\trasing to a negative number(-1 inverse) is not supported yet\n");
        }
        #endif

        if(p==0)
        {
            mat<T> identity(IDENTITY,base.width);
            base = identity;
        }
        else if(p>=2)
        {
            mat<T> multiplier = base;
            for(size_t i=2; i<=p; ++i)
            {
                base*=multiplier;
            }
        }
        return base;
    }
}

#endif
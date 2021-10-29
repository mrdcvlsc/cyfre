#ifndef CYFRE_APPLY_CPP
#define CYFRE_APPLY_CPP

#include <iostream>
#include "../classes/matrix_class.hpp"

namespace cyfre
{
    // ================ applying function ==============================
    template<class T>
    void mat<T>::apply(std::function<T(T)> function_name)
    {
        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"void apply(std::function<T(T)> function_name\n";
        #endif

        for(size_t i=0; i<height; ++i)
        {
            for(size_t j=0; j<width; ++j)
            {
                matrix[i*width+j] = function_name(matrix[i*width+j]);
            }
        }

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif
    }
}

#endif
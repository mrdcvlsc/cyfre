#ifndef SCALARS_HPP
#define SCALARS_HPP

#include "cyfre.hpp"

namespace cyfre
{
    /// @arg accepts a vector of iterators that
    /// @returns a copy of the dot product of two std::vector<typename std::vector<T>::const_iterator>> :=
    template<typename T>
    T dot(std::vector<T> tuple1, std::vector<T> tuple2)
    {
        size_t length = tuple1.size();

        if(length!=tuple2.size())
        {
            std::cerr<<"\n\nERROR : T dot(std::vector<typename std::vector<T>> tuple1, std::vector<typename std::vector<T>> tuple2)\n";
            std::cerr<<"\tarray don't have the same lenght\n";
            std::cout<<"\ttuple1 length : "<<tuple1.size()<<'\n';
            std::cout<<"\ttuple2 length : "<<tuple2.size()<<'\n';
            exit(1); 
        }
        
        T summation = (T)0;

        for(size_t i=0; i<length; ++i) summation += tuple1[i]*tuple2[i];

        return summation;
    }

    /// @arg accepts a cyfre::mat<T> objects
    /// @returns T total, the total sum of all the elements of the matrix
    template<typename T>
    T total(const mat<T>& input)
    {
        T total = 0, zero = 0;
        for(auto row: input.matrix) total+=std::accumulate(row.begin(),row.end(),zero);
        return total;
    }

    /// @arg accepts a cyfre::mat<T> objects
    /// @returns T trace_total, the total sum of the main diagonal
    template<typename T>
    T trace(const mat<T>& input)
    {
        if(input.width!=input.height)
        {
            std::cerr<<"\n\nERROR : mat.trace()\n";
            std::cerr<<"\tthe matrix is not a square matrix, cannot get trace\n";
            exit(1);
        }

        T trace_total = 0;
        for(size_t i=0; i<input.height; ++i) trace_total+=input.matrix[i][i];
        return trace_total;
    }
}

#endif
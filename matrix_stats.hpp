#ifndef MATRIX_STATS_HPP
#define MATRIX_STATS_HPP

#include <iostream>
#include <math.h>
#include <map>
#include <set>
#include <utility>
#include "matrix_class.hpp"

namespace cyfre
{
    template<typename T>
    long double mean(const mat<T>& input)
    {
        T total = input.total();
        size_t n = input.height*input.width;
        return (long double)total/(long double)n;
    }

    template<typename T>
    long double median(const mat<T>& input)
    {
        auto oddmiddle = [](T odd)
        {
            if(odd==1) return (long double)0;
            return std::floor(((long double)odd/(long double)2));
        };

        if(input.height%2==0 && input.width%2==0)
        {
            size_t hh = (input.height/2)-1;
            size_t hw = (input.width/2)-1;

            return ((long double)input.matrix[hh][hw]+(long double)input.matrix[hh][hw+1]+
                   (long double)input.matrix[hh+1][hw]+(long double)input.matrix[hh+1][hw+1])/(long double)4;
        }
        else if(input.height%2!=0 && input.width%2==0)
        {
            size_t hh = oddmiddle(input.height);
            size_t hw = (input.width/2)-1;
            return ((long double)input.matrix[hh][hw]+(long double)input.matrix[hh][hw+1])/(long double)2;
        }
        else if(input.height%2==0 && input.width%2!=0)
        {
            size_t hh = (input.height/2)-1;
            size_t hw = oddmiddle(input.width);
            return ((long double)input.matrix[hh][hw]+(long double)input.matrix[hh+1][hw])/(long double)2;
        }
        else if(input.height%2!=0 && input.width%2!=0)
        {
            size_t hh = oddmiddle(input.height);
            size_t hw = oddmiddle(input.width);
            return (long double)input.matrix[hh][hw];
        }
        else if((input.height==1)&&(input.height==input.width))
        {
            return (long double)input.matrix[0][0];
        }
        return 0;
    }

    template<typename T>
    std::pair<size_t,std::vector<T>> mode(const mat<T>& input)
    {
        std::map<T,size_t> e_counts;
        for(size_t i=0; i<input.height; ++i)
        {
            for(size_t j=0; j<input.width; ++j)
            {
                auto curr = e_counts.find(input.matrix[i][j]);
                if(curr==e_counts.end())
                {
                    e_counts.insert({input.matrix[i][j],1});
                }
                else
                {
                    e_counts[input.matrix[i][j]]++;
                }
            }
        }

        size_t max = size_t(std::numeric_limits<size_t>::min());
        for(auto e: e_counts)
        {
            size_t curr_count = e.second;
            if(curr_count>max)
            {
                max = curr_count;
            }
        }

        std::set<T> modes;

        for(auto e: e_counts)
        {
            T curr_key = e.first;
            size_t curr_count = e.second;
            if(curr_count==max && curr_count!=1)
            {
                modes.insert(curr_key);
            }
        }

        if(modes.empty()) max = 0;

        std::vector<T> pair_second;
        pair_second.reserve(modes.size());
        for(auto e: modes)
        {
            pair_second.push_back(e);
        }

        return {max,pair_second};
    }

    enum OBSERVATIONS {POPULATION=0,SAMPLE=1};

    /// @returns variance
    template<typename T>
    long double variance(const mat<T>& input, const OBSERVATIONS type)
    {
        long double input_mean = mean(input);
        long double sum_of_squares = 0;
        for(size_t i=0; i<input.height; ++i)
        {
            for(size_t j=0; j<input.width; ++j)
            {
                sum_of_squares+= (input.matrix[i][j]-input_mean)*(input.matrix[i][j]-input_mean);
            }
        }

        long double n = input.height*input.width;

        return sum_of_squares/(long double)(n-(long double)type);
    }

    /// @returns standard deviation
    template<typename T>
    long double std_deviation(const mat<T>& input, const OBSERVATIONS type)
    {
        return std::sqrt(variance(input,type));
    }

    /// @returns sum of squares
    template<typename T>
    long double sofs(const mat<T>& input)
    {
        long double input_mean = mean(input);
        long double sum_of_squares = 0;
        for(size_t i=0; i<input.height; ++i)
        {
            for(size_t j=0; j<input.width; ++j)
            {
                sum_of_squares+= (input.matrix[i][j]-input_mean)*(input.matrix[i][j]-input_mean);
            }
        }
        return sum_of_squares;
    }

}

#endif
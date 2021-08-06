#ifndef MATRIX_CLASS
#define MATRIX_CLASS

#include <iostream>
#include <numeric>
#include <fstream>
#include <limits>
#include <cstdio>
#include <exception>
#include <random>
#include <functional>
#include <iterator>
#include "helper_functions.hpp"
#include "randomizer.hpp"

#ifdef DISPLAY_FUNC_CALLS
#include <chrono>
#endif

#ifdef OMPTHREAD
#include <omp.h>
#endif

/*
        CONTAINS ALL CYFRE LIBRARY TYPES from classes, to enums, and typedefs
*/

namespace cyfre
{
    #define TRANSPOSE_MT_TREASHOLD 3364000

    /// MATRIX TYPES FOR CONSTRUCTING A MATRIX
    enum TYPE{
        /// @arg - a square matrix where every element is '0'
        NULLZERO,
        /// @arg - a square matrix where every elements in the main diagonal has a value of '1'
        IDENTITY,
        /// @arg - a square matrix where every elements in the main diagonal has a value of a given 'N'
        SCALARMATRIX
    };

    /// enum type for random value constructor
    enum RANDOM{ INTEGER, REAL };

    /// SCALAR OPERATIONS
    enum SCALAR { ADD, SUB, MUL, DIV };

    template<class T>
    class mat
    {   
        public:

        T* matrix;
        size_t height;
        size_t width;
        
        // ============================== constructors ==============================

        /// initializes a 1x1 matrix with a value of zero
        mat() : matrix(nullptr), height(0), width(0)
        {
            #ifdef DISPLAY_FUNC_CALLS
            std::cout<<"mat()\n";
            auto start = std::chrono::high_resolution_clock::now();
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        mat(T one_value) : matrix(new T[1]), height(1), width(1)
        {
            #ifdef DISPLAY_FUNC_CALLS
            std::cout<<"mat(T one_value)\n";
            auto start = std::chrono::high_resolution_clock::now();
            #endif

            matrix[0] = one_value;

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// initializes a matrix from a text file
        mat(std::string text_file, char separator)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"mat(std::string text_file, char separator)\n";
            #endif

            std::ifstream filereader;
            filereader.open(text_file.c_str());

            if(filereader.fail()){
                throw std::ios_base::failure(
                    "\n\nERROR : constructor::mat<T>(\""+text_file+"\")\n"
                    "\tinitialization error, text file not found or might not be supported\n"
                );
            }

            std::vector<std::string> strlines;
            std::string tmp;
            
            while(!filereader.eof()){
                getline(filereader,tmp);
                strlines.push_back(tmp);
            }

            std::vector<std::vector<std::string>> matrix_strings;
            bool an_integer = true;
            for(size_t i=0; i<strlines.size(); ++i)
            {
                std::vector<std::string> row_parse = cyfre::helpers::parse(strlines[i],separator);
                for(size_t j=0; j<row_parse.size(); ++j)
                {
                    std::pair<bool,bool> isvalid_isrational = cyfre::helpers::isanumber(row_parse[j]);
                    if(!isvalid_isrational.first)
                    {
                        throw std::ios_base::failure(
                            "\n\nERROR : constructor::mat<T>(\""+text_file+"\")\n"
                            "\tinitialization error, invalid number inside the text file:"+text_file+", on line:"+std::to_string(i)+"\n"
                        );
                    }
                    if(isvalid_isrational.second) an_integer = false;
                }
                matrix_strings.push_back(row_parse);
            }

            for(size_t i=1; i<matrix_strings.size(); ++i)
            {
                if(matrix_strings[i].size()!=matrix_strings[i-1].size())
                {
                    throw std::length_error(
                        "\n\nERROR : constructor::mat<T>(\""+text_file+"\")\n"
                        "\tinitialization error, the text file provided an unequal length of rows\n"
                        "\terror occurs in text file after comparison on line "+std::to_string(i)+" & "+std::to_string(i+1)+"\n"
                    );
                }
            }

            height = matrix_strings.size();
            width  = matrix_strings[0].size();

            matrix = new T[height*width];

            size_t cnt = 0;
            for(size_t i=0; i<matrix_strings.size(); ++i)
            {
                for(size_t j=0; j<matrix_strings[i].size(); ++j)
                {
                    if(an_integer) matrix[cnt++] = (T)(std::stoll(matrix_strings[i][j]));
                    else matrix[cnt++] = (T)(std::stold(matrix_strings[i][j]));
                }
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// initializes a matrix using a 2 dimension vector : @arg std::vector<std::vector<T>> matrix
        mat(const std::vector<std::vector<T>>& matrix)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"mat(const std::vector<std::vector<T>>& matrix)\n";
            #endif

            if(matrix.empty())
            {
                throw std::length_error(
                    "\n\nERROR : mat(std::vector<std::vector<T>>)\n"
                    "\tthe outer 'std::vector<>' is empty\n"
                );
            }

            size_t prev_row_len = matrix[0].size();
            for(size_t i=0; i<matrix.size();++i)
            {
                if(matrix[i].size()!=prev_row_len)
                {
                    throw std::length_error(
                        "\n\nERROR : mat(std::vector<std::vector<T>>)\n"
                        "\tthe inner vector rows inside <std::vector'<std::vector<T>'> is not equal\n"
                    );
                }
                prev_row_len = matrix[0].size();
            }

            height = matrix.size();
            width  = matrix[0].size();

            this->matrix = new T[height*width];

            size_t cnt = 0;
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j)
                {
                    this->matrix[cnt++] = matrix[i][j];
                }
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// initializes a matrix using a vector : @arg std::vector<T> matrix
        mat(const std::vector<T>& array_vector) : height(1), width(array_vector.size())
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"mat(const std::vector<T>& array_vector)\n";
            #endif

            matrix = new T[height*width];

            for(size_t i=0; i<width; ++i)
            {
                matrix[i] = array_vector[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// initializes a matrix given a @arg height, @arg width for the matrix shape, and a @arg default_value of all elements in the matrix
        mat(const size_t height, const size_t width, const T default_value) : matrix(new T[height*width]), height(height), width(width)
        {
            #ifdef DISPLAY_FUNC_CALLS
            std::cout<<"mat(const size_t height, const size_t width, const T default_value)\n";
            auto start = std::chrono::high_resolution_clock::now();
            #endif

            size_t n = height*width;

            for(size_t i=0; i<n; ++i)
            {
                matrix[i] = default_value;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// initializes a matrix given a @arg height, @arg width for the matrix shape, that have a random values form the given @arg lower_bound to @arg upper_bound
        mat(const size_t height, const size_t width, const RANDOM typechoice, const T lower_bound, const T upper_bound) :
        matrix(new T[height*width]), height(height), width(width)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"mat(const size_t height, const size_t width, const RANDOM typechoice, const T lower_bound, const T upper_bound)\n";
            #endif

            unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
            std::mt19937_64 rand_engine(seed);
            std::uniform_real_distribution<float> random_number_float(lower_bound,upper_bound);
            std::uniform_int_distribution<long long> random_number_int(lower_bound,upper_bound);

            size_t n = height*width;

            for(size_t i=0; i<n; ++i)
            {
                switch(typechoice)
                {
                    case RANDOM::INTEGER:
                        matrix[i] = random_number_int(rand_engine);
                        break;
                    case RANDOM::REAL:
                        matrix[i] = random_number_float(rand_engine);
                        break;
                    default:
                        throw std::invalid_argument("\n\nERROR : mat(const size_t height, const size_t width, const RANDOM typechoice, const T lower_bound, const T upper_bound)\n\tinvalid random type");
                }
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// initializes a square matrix with a given 'x' scalar values of elements in the main diagonal
        mat(const TYPE matrix_type, const size_t n, T scalar)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"mat(const TYPE matrix_type, const size_t n, T scalar)\n";
            #endif

            if(matrix_type==TYPE::IDENTITY) scalar = 1;

            height = width = n;

            matrix = new T[n*n];
            
            size_t N = n*n;
            for(size_t i=0; i<N; ++i)
            {
                matrix[i] = 0;
            }

            for(size_t i=0; i<n; ++i)
            {
                matrix[i*width+i] = scalar;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }
        
        mat(const TYPE matrix_type, const size_t n) : mat(matrix_type,n,0)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"mat(const TYPE matrix_type, const size_t n) : mat(matrix_type,n,0)\n";
            #endif

            switch(matrix_type)
            {
                case TYPE::IDENTITY: break;
                case TYPE::NULLZERO: break;
                case TYPE::SCALARMATRIX  :
                    throw std::invalid_argument(
                        "\n\nERROR : mat(TYPE matrix_type, size_t n, T scalar)\n"
                        "\tSCALAR matrix initialization, missing argument\n"
                    );
                default:
                    throw std::invalid_argument("\n\nERROR : mat()\n\tmatrix initialization - constructor invalid given an invalid TYPE\n");
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// copy constructor
        mat(const mat& original)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"mat(const mat& original)\n";
            #endif
            
            size_t n = original.height*original.width;
            matrix = new T[n];

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                matrix[i] = original.matrix[i];
            }

            height = original.height;
            width = original.width;

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        ~mat()
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"~mat()\n";
            #endif

            if(height && width) delete [] matrix;
            height = 0;
            width = 0;

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        // copy operator
        mat& operator=(const mat& original)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"mat(const mat& original)\n";
            #endif

            size_t n = original.height*original.width;

            if(height && (height!=original.height || width!=original.width))
            {
                delete [] matrix;
                matrix = new T[n];
            }
            else if(!height) matrix = new T[n];

            height = original.height;
            width =  original.width;

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                matrix[i] = original.matrix[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return *this;
        }

        /// initialize a matrix from an openCV Mat object
        

        // ============================== scalar return methods ==============================

        // /// @returns the dot product of two std::vector<typename std::vector<T>::const_iterator>> :=
        // /// it accepts a vector of iterators that points to row or column elements or a matrix
        // inline static T dot(std::vector<typename std::vector<T>::const_iterator> iter_tuple1, std::vector<typename std::vector<T>::const_iterator> iter_tuple2)
        // {
        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto start = std::chrono::high_resolution_clock::now();
        //     std::cout<<"inline static mat::dot()\n";
        //     #endif

        //     size_t length = iter_tuple1.size();

        //     #ifndef CHECK_SHAPE_DISABLE
        //     if(length!=iter_tuple2.size())
        //     {
        //         throw std::length_error(
        //             std::string("\n\nERROR : T dot(std::vector<typename std::vector<T>> iter_tuple1, std::vector<typename std::vector<T>> iter_tuple2)\n")+
        //             "\tarray don't have the same lenght\n"
        //         ); 
        //     }
        //     #endif
            
        //     T summation = (T)0;

        //     for(size_t i=0; i<length; ++i) summation += (*iter_tuple1[i])*(*iter_tuple2[i]);

        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto finish = std::chrono::high_resolution_clock::now();
        //     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        //     std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        //     #endif

        //     return summation;
        // }

        /// @returns T total, the total sum of all the elements of the matrix
        T total() const
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"T total() const\n";
            #endif

            T total = 0;

            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j)
                {
                    total += matrix[i*width+j];
                }
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return total;
        }

        /// @returns T trace_total, the total sum of the main diagonal
        T trace() const
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"T trace() const\n";
            #endif

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

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return trace_total;
        }

        T max()
        {
            size_t n = height*width;

            if(!n)
            {
                throw std::range_error("ERROR : T max() - the matrix is empty, there is no maximum");
            }

            T maximum = matrix[0];
            for(size_t i=1; i<n; ++i)
            {
                if(matrix[i]>maximum)
                {
                    maximum = matrix[i];
                }
            }
        }

        T min()
        {
            size_t n = height*width;
            
            if(!n)
            {
                throw std::range_error("ERROR : T min() - the matrix is empty, there is no minimum");
            }

            T minimum = matrix[0];
            for(size_t i=1; i<n; ++i)
            {
                if(matrix[i]<minimum)
                {
                    minimum = matrix[i];
                }
            }
        }

        // ============================== ROW ==============================

        // /// @returns std::vector<typename std::vector<T>::const_iterator> of a row
        // std::vector<typename std::vector<T>::const_iterator> row_iterators(size_t row_index) const
        // {
        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto start = std::chrono::high_resolution_clock::now();
        //     std::cout<<"std::vector<typename std::vector<T>::const_iterator> row_iterators(size_t row_index) const\n";
        //     #endif

        //     #ifndef CHECK_RANGE_DISABLE
        //     if((row_index < 0) ^ (row_index > height-1))
        //     {
        //         throw std::out_of_range(
        //             std::string("\n\nERROR : std::vector<typename std::vector<T>::const_iterator> row_iterators(size_t row_index)\n")+
        //             "\tthe given row index is out of bound\n"
        //         );
        //     }
        //     #endif

        //     std::vector<typename std::vector<T>::const_iterator> row_iterator;
        //     for(size_t i=0; i<width; ++i) row_iterator.push_back(matrix[row_index].begin()+i);

        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto finish = std::chrono::high_resolution_clock::now();
        //     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        //     std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        //     #endif

        //     return row_iterator;
        // }

        // /// @returns std::vector<typename std::vector<T>::iterator> of a row
        // std::vector<typename std::vector<T>::iterator> row_iterators_r(size_t row_index)
        // {
        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto start = std::chrono::high_resolution_clock::now();
        //     std::cout<<"std::vector<typename std::vector<T>::iterator> row_iterators_r(size_t row_index)\n";
        //     #endif

        //     #ifndef CHECK_RANGE_DISABLE
        //     if((row_index < 0) ^ (row_index > height-1))
        //     {
        //         throw std::out_of_range(
        //             std::string("\n\nERROR : std::vector<typename std::vector<T>::iterator> row_iterators_r(size_t row_index)\n")+
        //             "\tthe given row index is out of bound\n"
        //         );
        //     }
        //     #endif

        //     std::vector<typename std::vector<T>::iterator> row_iterator;
        //     for(size_t i=0; i<width; ++i) row_iterator.push_back(matrix[row_index].begin()+i);

        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto finish = std::chrono::high_resolution_clock::now();
        //     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        //     std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        //     #endif

        //     return row_iterator;
        // }

        // /// @returns std::vector<std::vector<T>> of a row
        // std::vector<std::vector<T>> row(size_t row_index) const
        // {
        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto start = std::chrono::high_resolution_clock::now();
        //     std::cout<<"std::vector<std::vector<T>> row(size_t row_index) const\n";
        //     #endif

        //     #ifndef CHECK_RANGE_DISABLE
        //     if((row_index < 0) ^ (row_index > height-1))
        //     {
        //         throw std::out_of_range(
        //             std::string("\n\nERROR : std::vector<std::vector<T>> row(size_t row_index)\n")+
        //             "\tthe given row index is out of bound\n"
        //         );
        //     }
        //     #endif

        //     std::vector<std::vector<T>> row_vector;
        //     row_vector.reserve(width);
        //     row_vector.insert(row_vector.end(),matrix[row_index].begin(),matrix[row_index].end());

        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto finish = std::chrono::high_resolution_clock::now();
        //     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        //     std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        //     #endif

        //     return row_vector;
        // }

        /// 'ADD,SUB,MUL, or DIV' a given 'const T value' to all elements of a selected 'const size_t row_index' 
        void scale_row(const size_t row_index, const SCALAR scalar_operation, const T value)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void scale_row(const size_t row_index, const SCALAR scalar_operation, const T value)\n";
            #endif

            #ifndef CHECK_RANGE_DISABLE
            if((row_index < 0) ^ (row_index > height-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void scale_row(const size_t row_index, const SCALAR scalar_operation, const T value)\n"
                    "\tthe given row index is out of bound\n"
                );
            }
            #endif

            auto operation_function = [scalar_operation](const T matrix_index,const T operation_value)
            {
                switch(scalar_operation)
                {
                    case ADD: return matrix_index+operation_value;
                    case SUB: return matrix_index-operation_value;
                    case MUL: return matrix_index*operation_value;
                    case DIV: return matrix_index/operation_value;
                    default:
                        throw std::invalid_argument(
                            "\n\nERROR : scale_row(const size_t row_index, const SCALAR scalar_operation, const T value)\n"
                            "\tscale_row was given an invalid operation\n"
                        );
                }
            };

            for(size_t i=0; i<width; ++i)
            {
                matrix[row_index*width+i] = operation_function(matrix[row_index*width+i],value);
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

        }

        void row_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void row_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n";
            #endif

            #ifndef CHECK_RANGE_DISABLE
            if((output_index < 0) ^ (output_index > height-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void row_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n"
                    "\tthe given row 'output_index' is out of bound\n"
                );
            }
            else if((input_index < 0) ^ (input_index > height-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void row_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n"
                    "\tthe given row 'input_index'  is out of bound\n"
                );
            }
            #endif

            auto operation_function = [scalar_operation](const T matrix_index,const T operation_value)
            {
                switch(scalar_operation)
                {
                    case ADD: return matrix_index+operation_value;
                    case SUB: return matrix_index-operation_value;
                    case MUL: return matrix_index*operation_value;
                    case DIV: return matrix_index/operation_value;
                    default:
                        throw std::invalid_argument(
                            "\n\nERROR : void row_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n"
                            "\tthe 'scalar_operation' given was invalid\n"
                        );
                }
            };

            for(size_t i=0; i<width; ++i)
            {
                matrix[output_index*width+i] = operation_function(matrix[output_index*width+i],matrix[input_index*width+i]);
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// @note: swaps the values of a row to another row :: a<-->b
        void row_swap(size_t row_a, size_t row_b)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void row_swap(size_t row_a, size_t row_b)\n";
            #endif

            #ifndef CHECK_RANGE_DISABLE
            if((row_a < 0) ^ (row_a > height-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void row_swap(size_t row_a, size_t row_b)\n"
                    "\tthe given row 'row_a' is out of bound\n"
                );
            }
            else if((row_b < 0) ^ (row_b > height-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void row_swap(size_t row_a, size_t row_b)\n"
                    "\tthe given row 'row_b'  is out of bound\n"
                );
            }
            #endif

            T temp;
            for(size_t i=0; i<width; ++i)
            {
                temp = matrix[row_a*width+i];
                matrix[row_a*width+i] = matrix[row_b*width+i];
                matrix[row_b*width+i] = temp;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// @note: multiply all the values of a row to a non-zero constant
        /// @arg(scalar,base_row)
        /// @param 1 scalar : template S type value that you want to multiply to all the elements of the row
        /// @param 2 base_row : size_t index of the row you want to perform scaling
        template<typename S>
        void row_scale(S scalar, size_t base_row)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void row_scale(S scalar, size_t base_row)\n";
            #endif

            #ifndef CHECK_RANGE_DISABLE
            if((base_row < 0) ^ (base_row > height-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void row_scale(S scalar, size_t base_row)\n"
                    "\tthe given row 'base_row' is out of bound\n"
                );
            }
            #endif

            for(size_t i=0; i<width; ++i)
            {
                matrix[base_row*width+i] *= scalar;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// @note: multiply all the values of a row to a non-zero constant, then add the result to another row
        /// @arg(scalar,scale_row,base_row)
        /// @param 1 scalar : template S type value that you want to multiply to all the elements of the row
        /// @param 2 scale_row : size_t index of the row you want to scale
        /// @param 3 base_row : size_t index of the row you want to add the results of the scaled row
        template<typename S>
        void row_scale(S scalar, size_t scale_row, size_t base_row)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void row_scale(S scalar, size_t scale_row, size_t base_row)\n";
            #endif

            #ifndef CHECK_RANGE_DISABLE
            if((scale_row < 0) ^ (scale_row > height-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void row_scale(S scalar, size_t scale_row, size_t scale_row)\n"
                    "\tthe given row 'scale_row' is out of bound\n"
                );
            }
            else if((base_row < 0) ^ (base_row > height-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void row_scale(S scalar, size_t scale_row, size_t base_row)\n"
                    "\tthe given row 'base_row' is out of bound\n"
                );
            }
            #endif

            for(size_t i=0; i<width; ++i)
            {
                matrix[base_row*width+i] += scalar*matrix[scale_row*width+i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        // ============================== COLUMN ==============================

        // /// @returns std::vector<typename std::vector<T>::const_iterator> of a column
        // std::vector<typename std::vector<T>::const_iterator> column_iterators(size_t column_index) const
        // {
        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto start = std::chrono::high_resolution_clock::now();
        //     std::cout<<"std::vector<typename std::vector<T>::const_iterator> column_iterators(size_t column_index) const\n";
        //     #endif

        //     #ifndef CHECK_RANGE_DISABLE
        //     if((column_index < 0) ^ (column_index > width-1))
        //     {
        //         throw std::out_of_range(
        //             std::string("\n\nERROR : std::vector<typename std::vector<T>::const_iterator> column_iterators(size_t column_index)\n")+
        //             "\tthe given column index is out of bound\n"
        //         );
        //     }
        //     #endif

        //     std::vector<typename std::vector<T>::const_iterator> column_iterator;
        //     for(size_t i=0; i<height; ++i) column_iterator.push_back(matrix[i].begin()+column_index);

        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto finish = std::chrono::high_resolution_clock::now();
        //     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        //     std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        //     #endif

        //     return column_iterator;
        // }

        // /// @returns std::vector<typename std::vector<T>::iterator> of a column
        // std::vector<typename std::vector<T>::iterator> column_iterators_r(size_t column_index)
        // {
        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto start = std::chrono::high_resolution_clock::now();
        //     std::cout<<"std::vector<typename std::vector<T>::iterator> column_iterators_r(size_t column_index)\n";
        //     #endif

        //     #ifndef CHECK_RANGE_DISABLE
        //     if((column_index < 0) ^ (column_index > width-1))
        //     {
        //         throw std::out_of_range(
        //             std::string("\n\nERROR : std::vector<typename std::vector<T>::iterator> column_iterators_r(size_t column_index)\n")+
        //             "\tthe given column index is out of bound\n"
        //         );
        //     }
        //     #endif

        //     std::vector<typename std::vector<T>::iterator> column_iterator;
        //     for(size_t i=0; i<height; ++i) column_iterator.push_back(matrix[i].begin()+column_index);

        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto finish = std::chrono::high_resolution_clock::now();
        //     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        //     std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        //     #endif
            
        //     return column_iterator;
        // }

        // /// @returns std::vector<std::vector<T>> of a column
        // std::vector<std::vector<T>> column(size_t column_index) const
        // {
        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto start = std::chrono::high_resolution_clock::now();
        //     std::cout<<"std::vector<std::vector<T>> column(size_t column_index) const\n";
        //     #endif

        //     #ifndef CHECK_RANGE_DISABLE
        //     if((column_index < 0) ^ (column_index > width-1))
        //     {
        //         throw std::out_of_range(
        //             std::string("\n\nERROR : std::vector<std::vector<T>> column(size_t column_index)\n")+
        //             "\tthe given column index is out of bound\n"
        //         );
        //     }
        //     #endif

        //     std::vector<std::vector<T>> column_vector;
        //     column_vector.reserve(height);
        //     for(size_t i=0; i<height; ++i) column_vector.push_back(matrix[column_index][i]);

        //     #ifdef DISPLAY_FUNC_CALLS
        //     auto finish = std::chrono::high_resolution_clock::now();
        //     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        //     std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        //     #endif

        //     return column_vector;
        // }

        /// 'ADD,SUB,MUL, or DIV' a given 'const T value' to all elements of a selected 'const size_t column_index'
        void scale_column(const size_t column_index, const SCALAR scalar_operation, const T value)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void scale_column(const size_t column_index, const SCALAR scalar_operation, const T value)\n";
            #endif

            #ifndef CHECK_RANGE_DISABLE
            if((column_index < 0) ^ (column_index > width-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void scale_column(const size_t column_index, const SCALAR scalar_operation, const T value)\n"
                    "\tthe given column index is out of bound\n"
                );
            }
            #endif

            auto operation_function = [scalar_operation](const T matrix_index,const T operation_value)
            {
                switch(scalar_operation)
                {
                    case ADD: return matrix_index+operation_value;
                    case SUB: return matrix_index-operation_value;
                    case MUL: return matrix_index*operation_value;
                    case DIV: return matrix_index/operation_value;
                    default:
                        throw std::invalid_argument(
                            "\n\nERROR : scale_column(const size_t column_index, const SCALAR scalar_operation, const T value)\n"
                            "\tscale_column was given an invalid scalar operation\n"
                        );
                }
            };

            for(size_t i=0; i<height; ++i)
            {
                matrix[i*width+column_index] = operation_function(matrix[i*width+column_index],value);
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        void column_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void column_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n";
            #endif

            #ifndef CHECK_RANGE_DISABLE
            if((output_index < 0) ^ (output_index > width-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void column_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n"
                    "\tthe given column 'output_index' is out of bound\n"
                );
            }
            else if((input_index < 0) ^ (input_index > width-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void column_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n"
                    "\tthe given column 'input_index' is out of bound\n"
                );
            }
            #endif

            auto operation_function = [scalar_operation](const T matrix_index,const T operation_value)
            {
                switch(scalar_operation)
                {
                    case ADD: return matrix_index+operation_value;
                    case SUB: return matrix_index-operation_value;
                    case MUL: return matrix_index*operation_value;
                    case DIV: return matrix_index/operation_value;
                    default:
                        throw std::invalid_argument(
                            "\n\nERROR : void column_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n"
                            "\tthe 'scalar_operation' given was invalid\n"
                        );
                }
            };

            for(size_t i=0; i<height; ++i)
            {
                matrix[i*width+output_index] = operation_function(matrix[i*width+output_index],matrix[i*width+input_index]);
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// @note: swaps the values of a column to another column :: a<-->b
        void column_swap(size_t column_a, size_t column_b)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void column_swap(size_t column_a, size_t column_b)\n";
            #endif

            #ifndef CHECK_RANGE_DISABLE
            if((column_a < 0) ^ (column_a > width-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void column_swap(size_t column_a, size_t column_b)\n"
                    "\tthe given column 'column_a' is out of bound\n"
                );
            }
            else if((column_b < 0) ^ (column_b > width-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void column_swap(size_t column_a, size_t column_b)\n"
                    "\tthe given column 'column_b'  is out of bound\n"
                );
            }
            #endif

            T temp;
            for(size_t i=0; i<height; ++i)
            {
                temp = matrix[i*width+column_a];
                matrix[i*width+column_a] = matrix[i*width+column_b];
                matrix[i*width+column_b] = temp;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// @note: multiply all the values of a column to a non-zero constant
        /// @arg(scalar,base_column)
        /// @param 1 scalar : template S type value that you want to multiply to all the elements of the column
        /// @param 2 base_column : size_t index of the column you want to perform scaling
        template<typename S>
        void column_scale(S scalar, size_t base_column)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void column_scale(S scalar, size_t base_column)\n";
            #endif

            #ifndef CHECK_RANGE_DISABLE
            if((base_column < 0) ^ (base_column > width-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void column_scale(S scalar, size_t base_column)\n"
                    "\tthe given column 'base_column' is out of bound\n"    
                );
            }
            #endif

            for(size_t i=0; i<height; ++i)
            {
                matrix[i*width+base_column]*=scalar;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        /// @note: multiply all the values of a column to a non-zero constant, then add the result to another column
        /// @arg(scalar,scale_column,base_column)
        /// @param 1 scalar : template S type value that you want to multiply to all the elements of the column
        /// @param 2 scale_column : size_t index of the column you want to scale
        /// @param 3 base_column : size_t index of the column you want to add the results of the scaled column
        template<typename S>
        void column_scale(S scalar, size_t scale_column, size_t base_column)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void column_scale(S scalar, size_t scale_column, size_t base_column)\n";
            #endif

            #ifndef CHECK_RANGE_DISABLE
            if((scale_column < 0) ^ (scale_column > width-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void column_scale(S scalar, size_t scale_column, size_t scale_column)\n"
                    "\tthe given column 'scale_column' is out of bound\n"
                );
            }
            else if((base_column < 0) ^ (base_column > width-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : void column_scale(S scalar, size_t scale_column, size_t base_column)\n"
                    "\tthe given column 'base_column' is out of bound\n"
                );
            }
            #endif

            for(size_t i=0; i<height; ++i)
            {
                matrix[i*width+base_column] += scalar*matrix[i*width+scale_column];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        // ============================== SAFE INDEXING ================================

        inline T& operator()(size_t i, size_t j)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"T& operator()(size_t i, size_t j)\n";
            #endif

            #ifndef CHECK_RANGE_DISABLE
            if((i < 0) ^ (i > height-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : T& operator()(size_t i, size_t j)\n"
                    "\tthe given row index is out of bound\n"
                );
            }
            else if((j < 0) ^ (j > width-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : T& operator()(size_t i, size_t j)\n"
                    "\tthe given column index is out of bound\n"
                );
            }
            #endif

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return matrix[i*width+j];
        }
        
        inline const T& operator()(size_t i, size_t j) const
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"const T& operator()(size_t i, size_t j) const\n";
            #endif

            #ifndef CHECK_RANGE_DISABLE
            if((i < 0) ^ (i > height-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : const T& operator()(size_t i, size_t j)\n"
                    "\tthe given row index is out of bound\n"
                );
            }
            else if((j < 0) ^ (j > width-1))
            {
                throw std::out_of_range(
                    "\n\nERROR : const T& operator()(size_t i, size_t j)\n"
                    "\tthe given column index is out of bound\n"
                );
            }
            #endif

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return matrix[i*width+j];
        }

        // ============================== MATRIX OPERATIONS ==============================

        /// --------------------------- addition ---------------------------------

        /// @returns element by element addition - old
        inline mat operator+(const mat& that) const
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline mat operator+(const mat& that) const\n";
            #endif

            #ifndef CHECK_SHAPE_DISABLE
            if(this->width!=that.width || this->height!=that.height)
            {
                std::string errmsg = "\n\nERROR : mat operator+(const mat& that) const\n"
                                     "\taddition of two different shaped matrix is not allowed\n";
                throw std::length_error(errmsg);
            }
            #endif
            
            size_t n = height*width;

            mat sum;
            sum.height = height;
            sum.width = width;
            sum.matrix = new T[n];

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                sum.matrix[i] = matrix[i] + that.matrix[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return sum;
        }

        inline void operator+=(const mat& that)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline void operator+=(const mat& that)\n";
            #endif

            #ifndef CHECK_SHAPE_DISABLE
            if(this->width!=that.width || this->height!=that.height)
            {
                std::string errmsg = "\n\nERROR : mat operator+=(const mat& that) const\n"
                                     "\taddition of two different shaped matrix is not allowed\n";
                throw std::length_error(errmsg);
            }
            #endif
            
            size_t n = height*width;

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                matrix[i] += that.matrix[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        inline mat operator+(const T scalar) const
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline mat operator+(const T scalar) const\n";
            #endif

            size_t n = height*width;
            
            mat scaled_sum;
            scaled_sum.height = height;
            scaled_sum.width = width;
            scaled_sum.matrix = new T[n];

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                scaled_sum.matrix[i] = matrix[i] + scalar;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return scaled_sum;
        }

        inline void operator+=(const T scalar)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline void operator+=(const T scalar)\n";
            #endif

            size_t n = height*width;

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                matrix[i] += scalar;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        template<typename S> inline friend mat operator+(const S scalar, const mat& that)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"template<typename S> inline friend mat operator+(const S scalar, const mat& that)\n";
            #endif

            size_t n = that.height*that.width;

            mat scaled_sum;
            scaled_sum.height = that.height;
            scaled_sum.width = that.width;
            scaled_sum.matrix = new T[n];

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                scaled_sum.matrix[i] = scalar + that.matrix[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return scaled_sum;
        }

        /// --------------------------- subtraction ---------------------------------

        /// @returns element by element subtraction - old
        inline mat operator-(const mat& that) const
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline mat operator-(const mat& that) const\n";
            #endif

            #ifndef CHECK_SHAPE_DISABLE
            if(this->width!=that.width || this->height!=that.height)
            {
                std::string errmsg = "\n\nERROR : mat operator-(const mat& that) const\n"
                                     "\tsubtraction of two different shaped matrix is not allowed\n";
                throw std::length_error(errmsg);
            }
            #endif
            
            size_t n = height*width;

            mat difference;
            difference.height = height;
            difference.width = width;
            difference.matrix = new T[n];

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                difference.matrix[i] = matrix[i] - that.matrix[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return difference;
        }

        inline void operator-=(const mat& that)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline void operator-=(const mat& that)\n";
            #endif

            #ifndef CHECK_SHAPE_DISABLE
            if(this->width!=that.width || this->height!=that.height)
            {
                std::string errmsg = "\n\nERROR : mat operator-=(const mat& that) const\n"
                                     "\tsubtraction of two different shaped matrix is not allowed\n";
                throw std::length_error(errmsg);
            }
            #endif
            
            size_t n = height*width;

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                matrix[i] -= that.matrix[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        inline mat operator-(const T scalar) const
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline mat operator-(const T scalar) const\n";
            #endif

            size_t n = height*width;
            
            mat scaled_difference;
            scaled_difference.height = height;
            scaled_difference.width = width;
            scaled_difference.matrix = new T[n];

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                scaled_difference.matrix[i] = matrix[i] - scalar;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return scaled_difference;
        }

        inline void operator-=(const T scalar)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline void operator-=(const T scalar)\n";
            #endif

            size_t n = height*width;

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                matrix[i] -= scalar;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        template<typename S> inline friend mat operator-(const S scalar, const mat& that)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"template<typename S> inline friend mat operator-(const S scalar, const mat& that)\n";
            #endif

            size_t n = that.height*that.width;

            mat scaled_difference;
            scaled_difference.height = that.height;
            scaled_difference.width = that.width;
            scaled_difference.matrix = new T[n];

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                scaled_difference.matrix[i] = scalar - that.matrix[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return scaled_difference;
        }

        /// ---------------------- Division -----------------------------
        /// @returns element by element division
        inline mat operator/(const mat& that) const
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline mat operator/(const mat& that) const\n";
            #endif

            #ifndef CHECK_SHAPE_DISABLE
            if(this->width!=that.width || this->height!=that.height)
            {
                throw std::length_error(
                    "\n\nERROR : mat operator/(const mat& that) const\n"
                    "\taddition of two different shaped matrix is not allowed\n"
                );
            }
            #endif
            
            size_t n = height*width;

            mat quotient;
            quotient.height = height;
            quotient.width = width;
            quotient.matrix = new T[n];
            
            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                if(that.matrix[i]==0)
                {
                    throw std::domain_error("ERROR : inline mat operator/(const mat& that) const - divide by zero");
                }
                quotient.matrix[i] = matrix[i] / that.matrix[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return quotient;
        }

        inline void operator/=(const mat& that)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline void operator/=(const mat& that)\n";
            #endif

            #ifndef CHECK_SHAPE_DISABLE
            if(this->width!=that.width || this->height!=that.height)
            {
                throw std::length_error(
                    std::string("\n\nERROR : mat operator/=(const mat& that) const\n")+
                    "\taddition of two different shaped matrix is not allowed\n"
                );
            }
            #endif

            size_t n = height*width;
            
            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                if(that.matrix[i]==0)
                {
                    throw std::domain_error("ERROR : inline void operator/=(const mat& that) - divide by zero");
                }
                matrix[i]/=that.matrix[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        inline mat operator/(const T scalar) const
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline mat operator/(const T scalar) const\n";
            #endif

            if(scalar==0)
            {
                throw std::domain_error("ERROR : inline mat operator/(const T scalar) const - divide by zero");
            }

            size_t n = height*width;

            mat scaled_quotient;
            scaled_quotient.height = height;
            scaled_quotient.width = width;
            scaled_quotient.matrix = new T[n];
            
            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                scaled_quotient.matrix[i] = matrix[i] / scalar;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return scaled_quotient;
        }

        inline void operator/=(const T scalar)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline void operator/=(const T scalar)\n";
            #endif

            size_t n = height*width;
            
            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                if(scalar==0)
                {
                    throw std::domain_error("ERROR : inline void operator/=(const T scalar) - divide by zero");
                }
                matrix[i] /= scalar;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        template<typename S> inline friend mat operator/(const S scalar, const mat& that)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"template<typename S> inline friend mat operator/(const S scalar, const mat& that)\n";
            #endif

            size_t n = that.height * that.width;
            
            mat scaled_quotient;
            scaled_quotient.height = that.height;
            scaled_quotient.width = that.width;
            scaled_quotient.matrix = new T[n];

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                    if(that.matrix[i]==0)
                    {
                        throw std::domain_error("ERROR : template<typename S> inline friend mat operator/(const S scalar, const mat& that) - divide by zero");
                    }
                    scaled_quotient.matrix[i] = scalar/that.matrix[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return scaled_quotient;
        }

        /// ---------------------- Multiplication -----------------------------
        /// @returns matrix multiplication / dot product
        inline mat operator*(const mat& that) const
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline mat operator*(const mat& that) const\n";
            #endif

            #ifndef CHECK_SHAPE_DISABLE
            if(this->width!=that.height)
            {
                throw std::length_error(
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

            T* rht = new T[that.width*that.height];

            #ifndef OMPTHREAD
            for(size_t j=0; j<that.width; ++j)
            {
                for(size_t i=0; i<that.height; ++i)
                {
                    rht[k++] = that.matrix[i*that.width+j];
                }
            }
            #else
            if(that.height*that.width<=TRANSPOSE_MT_TREASHOLD)
            {
                for(size_t j=0; j<that.width; ++j)
                {
                    for(size_t i=0; i<that.height; ++i)
                    {
                        rht[k++] = that.matrix[i*that.width+j];
                    }
                }
            }
            else
            {
                size_t m, o;
                #pragma omp parallel for num_threads(omp_get_max_threads())
                for(size_t n = 0; n<that.width*that.height; n++)
                {
                    m = n/that.width;
                    o = n%that.width;
                    rht[n] = that.matrix[that.height*o+m];
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
                    for(j=0; j<that.width; ++j)
                    {
                        dot_sum = 0;

                        for(k=0; k<width; ++k)
                        {
                            dot_sum += matrix[i*width+k]*rht[j*that.height+k];
                        }
                        product.matrix[i*that.width+j] = dot_sum;
                    }
                }
            }

            delete [] rht;                

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return product;
        }

        inline void operator*=(const mat& that)
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

        /// @returns hadamard matrix product - element by element multiplication, not to be confused with matrix multiplication
        inline void hadamard(const mat& that)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void hadamard(const mat& that)\n";
            #endif

            #ifndef CHECK_SHAPE_DISABLE
            if(this->width!=that.width || this->height!=that.height)
            {
                throw std::length_error(
                    "\n\nERROR : static mat hadamard(const mat& left, const mat& that) const\n"
                    "\thadamard multiplication of two different shaped matrix is not allowed\n"
                );
            }
            #endif
            
            size_t n = height*width;

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                matrix[i]*=that.matrix[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        // multiplication by scalar

        inline mat operator*(const T scalar) const
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline mat operator*(const T scalar) const\n";
            #endif

            size_t n = height*width;
            
            mat scaled_product;
            scaled_product.height = height;
            scaled_product.width = width;
            scaled_product.matrix = new T[n];

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                scaled_product.matrix[i] = matrix[i] * scalar;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return scaled_product;
        }

        inline void operator*=(const T scalar)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"inline void operator*=(const T scalar)\n";
            #endif

            size_t n = height*width;

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                matrix[i] *= scalar;
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        template<typename S> inline friend mat operator*(const S scalar, const mat& that)
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"template<typename S> inline friend mat operator*(const S scalar, const mat& that)\n";
            #endif

            size_t n = that.height*that.width;

            mat scaled_product;
            scaled_product.height = that.height;
            scaled_product.width = that.width;
            scaled_product.matrix = new T[n];

            #ifdef OMPTHREAD
            #pragma omp parallel for num_threads(omp_get_max_threads())
            #endif
            for(size_t i=0; i<n; ++i)
            {
                scaled_product.matrix[i] = scalar * that.matrix[i];
            }

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif

            return scaled_product;
        }

        // ============================== MATRIX EXPOENTIAL ==============================

        /// @returns raised matrix to a certain number 'p'
        /// @note raising to a negative integer(inverse) is not supported yet but will be in the future
        void power(size_t p)
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
                mat multiplier = *this;
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

        // ============================== MATRIX TRANSFORMATION ==============================

        /// transpose self
        void transpose()
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void transpose()\n";
            #endif

            size_t i,j,k=0;

            T* rht = new T[width*height];

            #ifndef OMPTHREAD
            for(size_t j=0; j<width; ++j)
            {
                for(size_t i=0; i<height; ++i)
                {
                    rht[k++] = matrix[i*width+j];
                }
            }
            #else
            if(height*width<=TRANSPOSE_MT_TREASHOLD)
            {
                for(size_t j=0; j<width; ++j)
                {
                    for(size_t i=0; i<height; ++i)
                    {
                        rht[k++] = matrix[i*width+j];
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
                    rht[n] = matrix[height*o+m];
                }
            }
            #endif

            delete [] matrix;
            matrix = rht;
            std::swap(height,width);

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        // ============================= INVERSE MATRIX ================================

        /// converts matrix to it's inverse form
        void inv()
        {
            #ifdef DISPLAY_FUNC_CALLS
            auto start = std::chrono::high_resolution_clock::now();
            std::cout<<"void inv()\n";
            #endif

            #ifndef CHECK_SHAPE_DISABLE
            if(height!=width) throw std::length_error("\n\nERROR : cyfre::mat::inv() - cannot inverse a non-square matrix");
            #endif

            mat inverse(TYPE::IDENTITY,height);

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

            auto fix_pivot = [&inverse](mat<T>& input, size_t pi, size_t pj)
            {
                for(size_t i=0; i<input.height; ++i)
                {
                    if(i!=pi)
                    {
                        inverse.row_scale(-input.matrix[i*input.width+pj],pi,i);
                        input.row_scale(-input.matrix[i*input.width+pj],pi,i);
                    }
                }
            };

            auto make_pivot = [&inverse](mat<T>& input, size_t pi, size_t pj)
            {
                inverse.scale_row(pi,DIV,input.matrix[pi*input.width+pj]);
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

                if(nonzerorow!=(long long int)cpi)
                {
                    this->row_swap(cpi,nonzerorow);
                    inverse.row_swap(cpi,nonzerorow);
                }

                if(matrix[cpi*width+cpj]!=1) make_pivot(*this,cpi,cpj);
                fix_pivot(*this,cpi,cpj);
                cpi++;
                cpj++;
            }

            for(size_t i=0; i<height; ++i)
            {
                if(matrix[i*width+i]==0) throw std::domain_error("\n\nERROR: cyfre::mat::inv() - matrix determinant is zero, cannot invert matrix");
            }

            delete [] matrix;
            matrix = inverse.matrix;
            inverse.matrix = nullptr;
            inverse.height = 0;
            inverse.width = 0;

            #ifdef DISPLAY_FUNC_CALLS
            auto finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
            std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
            #endif
        }

        // ============================= ECHELON FORM ================================

        /// converts matrix to row echelon form of a matrix
        void ref()
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

        /// converts matrix to reduced row echelon form of a matrix
        void rref()
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

        // ================ applying function ==============================
        void apply(std::function<T(T)> function_name)
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

    };// end of mat class

    template<typename T>
    void display(const mat<T>& input)
    {

        // 100 width can still be displayed
        // 60 height can still be displayed

        #ifdef DISPLAY_FUNC_CALLS
        auto start = std::chrono::high_resolution_clock::now();
        std::cout<<"void display(const mat<T>& input)\n";
        #endif

        std::vector<std::string> matrixstr;

        size_t n = input.height*input.width;

        for(size_t i=0; i<n; ++i) matrixstr.push_back(std::to_string(input.matrix[i]));

        std::vector<size_t> max_cols_len(input.width,0);

        for(size_t j=0; j<input.width; ++j)
        {
            for(size_t i=0; i<input.height; ++i)
            {
                if(matrixstr[i*input.width+j].size()>max_cols_len[j])
                {
                    max_cols_len[j] = matrixstr[i*input.width+j].size();
                }
            }
        }

        for(size_t i=0; i<input.height; ++i)
        {
            if(i==0) std::cout<<"[[";
            else std::cout<<" [";

            for(size_t j=0; j<input.width; ++j)
            {
                size_t front_space = max_cols_len[j]-matrixstr[i*input.width+j].size();
                while(front_space--) std::cout<<' ';
                std::cout<<matrixstr[i*input.width+j];
                if(j!=input.width-1) std::cout<<", ";
                else std::cout<<"]";
            }
            if(i!=input.height-1) std::cout<<",\n";
            else std::cout<<"]\n";
        }

        // std::cout<<"[";
        // for(size_t i=0; i<input.height; ++i)
        // {
        //     std::cout<<"[";
        //     for(size_t j=0; j<input.width; ++j)
        //     {
        //         if(input.matrix[i*input.width+j]==0)
        //             std::cout<<std::abs(input.matrix[i*input.width+j]);
        //         else
        //             std::cout<<input.matrix[i*input.width+j];

        //         if(j!=input.width-1) std::cout<<' ';
        //     }
        //     std::cout<<"]";
        //     if(i!=input.height-1) std::cout<<",\n";
        //     else std::cout<<"]\n";
        // }

        // if(input.height==0 && input.width==0) std::cout<<"]\n";

        #ifdef DISPLAY_FUNC_CALLS
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start);
        std::cout<<"took "<<duration.count()<<" nanoseconds\n\n";
        #endif

        std::cout.width(0);
    }
}

#endif

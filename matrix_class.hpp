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
#include "helper_functions.hpp"
#include "randomizer.hpp"

#define SAFECHECK 1

/*
        CONTAINS ALL CYFRE LIBRARY TYPES from classes, to enums, and typedefs
*/

namespace cyfre
{
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

    template<typename T>
    class mat
    {   
        public:

        size_t height;
        size_t width;

        std::vector<std::vector<T>> matrix;
        
        // ============================== constructors ==============================

        /// initializes a 1x1 matrix with a value of zero
        mat()
        {
            height = 1;
            width = 1;
            std::vector<T> default_index;
            default_index.push_back(T(0));
            matrix.push_back(default_index);
        }

        mat(T one_value)
        {
            height = 1;
            width = 1;
            std::vector<T> default_index;
            default_index.push_back(one_value);
            matrix.push_back(default_index);
        }

        /// initializes a matrix from a text file
        mat(std::string text_file, char separator)
        {
            std::ifstream filereader;
            filereader.open(text_file.c_str());

            if(filereader.fail()){
                throw std::ios_base::failure(
                    std::string("\n\nERROR : constructor::mat<T>(\""+text_file+"\")\n")+
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
                            std::string("\n\nERROR : constructor::mat<T>(\""+text_file+"\")\n")+
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
                        std::string("\n\nERROR : constructor::mat<T>(\""+text_file+"\")\n")+
                        std::string("\tinitialization error, the text file provided an unequal length of rows\n")+
                        std::string("\terror occurs in text file after comparison on line "+std::to_string(i)+" & "+std::to_string(i+1)+"\n")
                    );
                }
            }

            std::vector<std::vector<T>> fmat;
            for(size_t i=0; i<matrix_strings.size(); ++i)
            {
                std::vector<T> tmp;
                fmat.push_back(tmp);
                for(size_t j=0; j<matrix_strings[i].size(); ++j)
                {
                    if(an_integer) fmat[i].push_back((T)std::stoll(matrix_strings[i][j]));
                    else fmat[i].push_back((T)std::stold(matrix_strings[i][j]));
                }
            }

            this->height = fmat.size();
            this->width  = fmat[0].size();
            this->matrix = fmat;
        }

        /// initializes a matrix using a 2 dimension vector : @arg std::vector<std::vector<T>> matrix
        mat(const std::vector<std::vector<T>>& matrix)
        {
            if(matrix.empty())
            {
                throw std::length_error(
                    std::string("\n\nERROR : mat(std::vector<std::vector<T>>)\n")+
                    "\tthe outer 'std::vector<>' is empty\n"
                );
            }

            size_t prev_row_len = matrix[0].size();
            for(size_t i=0; i<matrix.size();++i)
            {
                if(matrix[i].size()!=prev_row_len)
                {
                    throw std::length_error(
                        std::string("\n\nERROR : mat(std::vector<std::vector<T>>)\n")+
                        "\tthe inner vector rows inside <std::vector'<std::vector<T>'> is not equal\n"
                    );
                }
                prev_row_len = matrix[0].size();
            }

            height = matrix.size();
            width  = matrix[0].size();
            this->matrix = matrix;
        }

        /// initializes a matrix using a vector : @arg std::vector<T> matrix
        mat(const std::vector<T>& array_vector)
        {
            height = 1;
            width = array_vector.size();
            matrix.push_back(array_vector);
        }

        /// initializes a matrix given a @arg height, @arg width for the matrix shape, and a @arg default_value of all elements in the matrix
        mat(const size_t height, const size_t width, const T default_value)
        {
            size_t i=height, j=width;
            this->height = height;
            this->width  = width;

            matrix.reserve(height);
            std::vector<T> row;
            row.reserve(width);

            while(j--) row.push_back(default_value);
            while(i--) matrix.push_back(row);
        }

        /// initializes a matrix given a @arg height, @arg width for the matrix shape, that have a random values form the given @arg lower_bound to @arg upper_bound
        mat(const size_t height, const size_t width, const RANDOM typechoice, const T lower_bound, const T upper_bound)
        {
            this->height = height;
            this->width  = width;

            for(size_t i=0; i<height; ++i)
            {
                std::vector<T> row;
                row.reserve(width);
                for(size_t j=0; j<width; ++j)
                {
                    switch(typechoice)
                    {
                        case RANDOM::INTEGER:
                            row.push_back(randomize::integer<long long int,std::mt19937_64>(lower_bound,upper_bound));
                            break;
                        case RANDOM::REAL:
                            row.push_back(randomize::real<long double,std::mt19937_64>(lower_bound,upper_bound));
                            break;
                        default:
                            throw std::invalid_argument("\n\nERROR : mat(const size_t height, const size_t width, const RANDOM typechoice, const T lower_bound, const T upper_bound)\n\tinvalid random type");
                    }
                }
                matrix.push_back(row);
            }
        }

        /// initializes a square matrix with a given 'x' scalar values of elements in the main diagonal
        mat(const TYPE matrix_type, const size_t n, T scalar)
        {
            if(matrix_type==TYPE::IDENTITY) scalar = 1;

            size_t i=n, j=n;
            height = width = n;

            std::vector<T> row;
            row.reserve(n);
            matrix.reserve(n);

            while(j--) row.push_back(0);            
            while(i--) matrix.push_back(row);
            
            for(size_t i=0; i<n; ++i) matrix[i][i] = scalar;
        }
        
        mat(const TYPE matrix_type, const size_t n) : mat(matrix_type,n,0)
        {
            switch(matrix_type)
            {
                case TYPE::IDENTITY: break;
                case TYPE::NULLZERO: break;
                case TYPE::SCALARMATRIX  :
                    throw std::invalid_argument(
                        std::string("\n\nERROR : mat(TYPE matrix_type, size_t n, T scalar)\n")+
                        "\tSCALAR matrix initialization, missing argument\n"
                    );
                default:
                    throw std::invalid_argument("\n\nERROR : mat()\n\tmatrix initialization - constructor invalid given an invalid TYPE\n");
            }
        }

        /// initialize a matrix from an openCV Mat object
        

        // ============================== scalar return methods ==============================

        /// @returns the dot product of two std::vector<typename std::vector<T>::const_iterator>> :=
        /// it accepts a vector of iterators that points to row or column elements or a matrix
        inline static T dot(std::vector<typename std::vector<T>::const_iterator> iter_tuple1, std::vector<typename std::vector<T>::const_iterator> iter_tuple2)
        {
            size_t length = iter_tuple1.size();

            if(length!=iter_tuple2.size())
            {
                throw std::length_error(
                    std::string("\n\nERROR : T dot(std::vector<typename std::vector<T>> iter_tuple1, std::vector<typename std::vector<T>> iter_tuple2)\n")+
                    "\tarray don't have the same lenght\n"
                ); 
            }
            
            T summation = (T)0;

            for(size_t i=0; i<length; ++i) summation += (*iter_tuple1[i])*(*iter_tuple2[i]);

            return summation;
        }

        /// @returns T total, the total sum of all the elements of the matrix
        T total() const
        {
            T total = 0, zero = 0;
            for(auto row: matrix) total+=std::accumulate(row.begin(),row.end(),zero);
            return total;
        }

        /// @returns T trace_total, the total sum of the main diagonal
        T trace() const
        {
            if(width!=height)
            {
                throw std::length_error(
                    std::string("\n\nERROR : mat.trace()\n")+
                    "\tthe matrix is not a square matrix, cannot get trace\n"
                );
            }

            T trace_total = 0;
            for(size_t i=0; i<height; ++i) trace_total+=matrix[i][i];
        }

        // ============================== ROW ==============================

        /// @returns std::vector<typename std::vector<T>::const_iterator> of a row
        std::vector<typename std::vector<T>::const_iterator> row_iterators(size_t row_index) const
        {
            if((row_index < 0) ^ (row_index > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : std::vector<typename std::vector<T>::const_iterator> row_iterators(size_t row_index)\n")+
                    "\tthe given row index is out of bound\n"
                );
            }

            std::vector<typename std::vector<T>::const_iterator> row_iterator;
            for(size_t i=0; i<width; ++i) row_iterator.push_back(matrix[row_index].begin()+i);
            return row_iterator;
        }

        /// @returns std::vector<typename std::vector<T>::iterator> of a row
        std::vector<typename std::vector<T>::iterator> row_iterators_r(size_t row_index)
        {
            if((row_index < 0) ^ (row_index > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : std::vector<typename std::vector<T>::iterator> row_iterators_r(size_t row_index)\n")+
                    "\tthe given row index is out of bound\n"
                );
            }

            std::vector<typename std::vector<T>::iterator> row_iterator;
            for(size_t i=0; i<width; ++i) row_iterator.push_back(matrix[row_index].begin()+i);
            return row_iterator;
        }

        /// @returns std::vector<std::vector<T>> of a row
        std::vector<std::vector<T>> row(size_t row_index) const
        {
            if((row_index < 0) ^ (row_index > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : std::vector<std::vector<T>> row(size_t row_index)\n")+
                    "\tthe given row index is out of bound\n"
                );
            }

            std::vector<std::vector<T>> row_vector;
            row_vector.reserve(width);
            row_vector.insert(row_vector.end(),matrix[row_index].begin(),matrix[row_index].end());
            return row_vector;
        }

        /// 'ADD,SUB,MUL, or DIV' a given 'const T value' to all elements of a selected 'const size_t row_index' 
        void scale_row(const size_t row_index, const SCALAR scalar_operation, const T value)
        {
            if((row_index < 0) ^ (row_index > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void scale_row(const size_t row_index, const SCALAR scalar_operation, const T value)\n")+
                    "\tthe given row index is out of bound\n"
                );
            }

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
                            std::string("\n\nERROR : scale_row(const size_t row_index, const SCALAR scalar_operation, const T value)\n")+
                            "\tscale_row was given an invalid operation\n"
                        );
                }
            };

            for(size_t i=0; i<width; ++i)
            {
                matrix[row_index][i] = operation_function(matrix[row_index][i],value);
            }
        }

        void row_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)
        {
            if((output_index < 0) ^ (output_index > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void row_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n")+
                    "\tthe given row 'output_index' is out of bound\n"
                );
            }
            else if((input_index < 0) ^ (input_index > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void row_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n")+
                    "\tthe given row 'input_index'  is out of bound\n"
                );
            }

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
                            std::string("\n\nERROR : void row_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n")+
                            "\tthe 'scalar_operation' given was invalid\n"
                        );
                }
            };

            for(size_t i=0; i<width; ++i)
            {
                matrix[output_index][i] = operation_function(matrix[output_index][i],matrix[input_index][i]);
            }
        }

        /// @note: swaps the values of a row to another row :: a<-->b
        void row_swap(size_t row_a, size_t row_b)
        {
            #ifdef SAFECHECK
            if((row_a < 0) ^ (row_a > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void row_swap(size_t row_a, size_t row_b)\n")+
                    "\tthe given row 'row_a' is out of bound\n"
                );
            }
            else if((row_b < 0) ^ (row_b > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void row_swap(size_t row_a, size_t row_b)\n")+
                    "\tthe given row 'row_b'  is out of bound\n"
                );
            }
            #endif

            T temp;
            for(size_t i=0; i<width; ++i)
            {
                temp = matrix[row_a][i];
                matrix[row_a][i] = matrix[row_b][i];
                matrix[row_b][i] = temp;
            }
        }

        /// @note: multiply all the values of a row to a non-zero constant
        /// @arg(scalar,base_row)
        /// @param 1 scalar : template S type value that you want to multiply to all the elements of the row
        /// @param 2 base_row : size_t index of the row you want to perform scaling
        template<typename S>
        void row_scale(S scalar, size_t base_row)
        {
            #ifdef SAFECHECK
            if((base_row < 0) ^ (base_row > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void row_scale(S scalar, size_t base_row)\n")+
                    "\tthe given row 'base_row' is out of bound\n"
                );
            }
            #endif

            for(size_t i=0; i<width; ++i)
            {
                matrix[base_row][i]*=scalar;
            }
        }

        /// @note: multiply all the values of a row to a non-zero constant, then add the result to another row
        /// @arg(scalar,scale_row,base_row)
        /// @param 1 scalar : template S type value that you want to multiply to all the elements of the row
        /// @param 2 scale_row : size_t index of the row you want to scale
        /// @param 3 base_row : size_t index of the row you want to add the results of the scaled row
        template<typename S>
        void row_scale(S scalar, size_t scale_row, size_t base_row)
        {
            #ifdef SAFECHECK
            if((scale_row < 0) ^ (scale_row > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void row_scale(S scalar, size_t scale_row, size_t scale_row)\n")+
                    "\tthe given row 'scale_row' is out of bound\n"
                );
            }
            else if((base_row < 0) ^ (base_row > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void row_scale(S scalar, size_t scale_row, size_t base_row)\n")+
                    "\tthe given row 'base_row' is out of bound\n"
                );
            }
            #endif

            for(size_t i=0; i<width; ++i)
            {
                matrix[base_row][i] += scalar*matrix[scale_row][i];
            }
        }

        // ============================== COLUMN ==============================

        /// @returns std::vector<typename std::vector<T>::const_iterator> of a column
        std::vector<typename std::vector<T>::const_iterator> column_iterators(size_t column_index) const
        {
            if((column_index < 0) ^ (column_index > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : std::vector<typename std::vector<T>::const_iterator> column_iterators(size_t column_index)\n")+
                    "\tthe given column index is out of bound\n"
                );
            }

            std::vector<typename std::vector<T>::const_iterator> column_iterator;
            for(size_t i=0; i<height; ++i) column_iterator.push_back(matrix[i].begin()+column_index);
            return column_iterator;
        }

        /// @returns std::vector<typename std::vector<T>::iterator> of a column
        std::vector<typename std::vector<T>::iterator> column_iterators_r(size_t column_index)
        {
            if((column_index < 0) ^ (column_index > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : std::vector<typename std::vector<T>::iterator> column_iterators_r(size_t column_index)\n")+
                    "\tthe given column index is out of bound\n"
                );
            }

            std::vector<typename std::vector<T>::iterator> column_iterator;
            for(size_t i=0; i<height; ++i) column_iterator.push_back(matrix[i].begin()+column_index);
            return column_iterator;
        }

        /// @returns std::vector<std::vector<T>> of a column
        std::vector<std::vector<T>> column(size_t column_index) const
        {
            if((column_index < 0) ^ (column_index > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : std::vector<std::vector<T>> column(size_t column_index)\n")+
                    "\tthe given column index is out of bound\n"
                );
            }

            std::vector<std::vector<T>> column_vector;
            column_vector.reserve(height);
            for(size_t i=0; i<height; ++i) column_vector.push_back(matrix[column_index][i]);
            return column_vector;
        }

        /// 'ADD,SUB,MUL, or DIV' a given 'const T value' to all elements of a selected 'const size_t column_index'
        void scale_column(const size_t column_index, const SCALAR scalar_operation, const T value)
        {
            if((column_index < 0) ^ (column_index > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void scale_column(const size_t column_index, const SCALAR scalar_operation, const T value)\n")+
                    "\tthe given column index is out of bound\n"
                );
            }

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
                            std::string("\n\nERROR : scale_column(const size_t column_index, const SCALAR scalar_operation, const T value)\n")+
                            "\tscale_column was given an invalid scalar operation\n"
                        );
                }
            };

            for(size_t i=0; i<height; ++i)
            {
                matrix[i][column_index] = operation_function(matrix[i][column_index],value);
            }
        }

        void column_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)
        {
            if((output_index < 0) ^ (output_index > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void column_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n")+
                    "\tthe given column 'output_index' is out of bound\n"
                );
            }
            else if((input_index < 0) ^ (input_index > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void column_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n")+
                    "\tthe given column 'input_index' is out of bound\n"
                );
            }

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
                            std::string("\n\nERROR : void column_operation(const size_t output_index, const SCALAR scalar_operation, size_t input_index)\n")+
                            "\tthe 'scalar_operation' given was invalid\n"
                        );
                }
            };

            for(size_t i=0; i<height; ++i)
            {
                matrix[i][output_index] = operation_function(matrix[i][output_index],matrix[i][input_index]);
            }
        }

        /// @note: swaps the values of a column to another column :: a<-->b
        void column_swap(size_t column_a, size_t column_b)
        {
            #ifdef SAFECHECK
            if((column_a < 0) ^ (column_a > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void column_swap(size_t column_a, size_t column_b)\n")+
                    "\tthe given column 'column_a' is out of bound\n"
                );
            }
            else if((column_b < 0) ^ (column_b > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void column_swap(size_t column_a, size_t column_b)\n")+
                    "\tthe given column 'column_b'  is out of bound\n"
                );
            }
            #endif

            T temp;
            for(size_t i=0; i<height; ++i)
            {
                temp = matrix[i][column_a];
                matrix[i][column_a] = matrix[i][column_b];
                matrix[i][column_b] = temp;
            }
        }

        /// @note: multiply all the values of a column to a non-zero constant
        /// @arg(scalar,base_column)
        /// @param 1 scalar : template S type value that you want to multiply to all the elements of the column
        /// @param 2 base_column : size_t index of the column you want to perform scaling
        template<typename S>
        void column_scale(S scalar, size_t base_column)
        {
            #ifdef SAFECHECK
            if((base_column < 0) ^ (base_column > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void column_scale(S scalar, size_t base_column)\n")+
                    "\tthe given column 'base_column' is out of bound\n"    
                );
            }
            #endif

            for(size_t i=0; i<height; ++i)
            {
                matrix[i][base_column]*=scalar;
            }
        }

        /// @note: multiply all the values of a column to a non-zero constant, then add the result to another column
        /// @arg(scalar,scale_column,base_column)
        /// @param 1 scalar : template S type value that you want to multiply to all the elements of the column
        /// @param 2 scale_column : size_t index of the column you want to scale
        /// @param 3 base_column : size_t index of the column you want to add the results of the scaled column
        template<typename S>
        void column_scale(S scalar, size_t scale_column, size_t base_column)
        {
            #ifdef SAFECHECK
            if((scale_column < 0) ^ (scale_column > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void column_scale(S scalar, size_t scale_column, size_t scale_column)\n")+
                    "\tthe given column 'scale_column' is out of bound\n"
                );
            }
            else if((base_column < 0) ^ (base_column > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : void column_scale(S scalar, size_t scale_column, size_t base_column)\n")+
                    "\tthe given column 'base_column' is out of bound\n"
                );
            }
            #endif

            for(size_t i=0; i<height; ++i)
            {
                matrix[i][base_column] += scalar*matrix[i][scale_column];
            }
        }

        // ============================== SAFE INDEXING ================================

        T& operator()(size_t i, size_t j)
        {
            if((i < 0) ^ (i > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : T& operator()(size_t i, size_t j)\n")+
                    "\tthe given row index is out of bound\n"
                );
            }
            else if((j < 0) ^ (j > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : T& operator()(size_t i, size_t j)\n")+
                    "\tthe given column index is out of bound\n"
                );
            }
            return matrix[i][j];
        }
        
        const T& operator()(size_t i, size_t j) const
        {
            if((i < 0) ^ (i > height-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : const T& operator()(size_t i, size_t j)\n")+
                    "\tthe given row index is out of bound\n"
                );
            }
            else if((j < 0) ^ (j > width-1))
            {
                throw std::out_of_range(
                    std::string("\n\nERROR : const T& operator()(size_t i, size_t j)\n")+
                    "\tthe given column index is out of bound\n"
                );
            }
            return matrix[i][j];
        }

        // ============================== MATRIX OPERATIONS ==============================

        /// ---------------------- Addition -----------------------------
        /// @returns element by element addition
        inline mat operator+(const mat& that) const
        {
            if(this->width!=that.width || this->height!=that.height)
            {
                throw std::length_error(
                    std::string("\n\nERROR : mat operator+(const mat& that) const\n")+
                    "\taddition of two different shaped matrix is not allowed\n"
                );
            }
            
            mat answer = *this;
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j) answer.matrix[i][j]+=that.matrix[i][j];
            }

            return answer;
        }

        inline void operator+=(const mat& that)
        {
            if(this->width!=that.width || this->height!=that.height)
            {
                throw std::length_error(
                    std::string("\n\nERROR : mat operator+=(const mat& that) const\n")+
                    "\taddition of two different shaped matrix is not allowed\n"
                );
            }
            
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j) matrix[i][j]+=that.matrix[i][j];
            }
        }

        inline mat operator+(const T scalar) const
        {
            mat scaled_addition = *this;
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j)
                {
                    scaled_addition.matrix[i][j]+=scalar;
                }
            }
            return scaled_addition;
        }

        inline void operator+=(const T scalar)
        {
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j)
                {
                    matrix[i][j]+=scalar;
                }
            }
        }

        template<typename S> inline friend mat operator+(const S scalar, const mat& that)
        {
            mat scaled_addition = that;
            for(size_t i=0; i<scaled_addition.height; ++i)
            {
                for(size_t j=0; j<scaled_addition.width; ++j)
                {
                    scaled_addition.matrix[i][j] = scalar+scaled_addition.matrix[i][j];
                }
            }
            return scaled_addition;
        }

        /// ---------------------- Subtraction -----------------------------
        /// @returns element by element subtraction
        inline mat operator-(const mat& that) const
        {
            if(this->width!=that.width || this->height!=that.height)
            {
                throw std::length_error(
                    std::string("\n\nERROR : mat operator-(const mat& that) const\n")+
                    "\taddition of two different shaped matrix is not allowed\n"
                );
            }
            
            mat answer = *this;
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j) answer.matrix[i][j]-=that.matrix[i][j];
            }

            return answer;
        }

        inline void operator-=(const mat& that)
        {
            if(this->width!=that.width || this->height!=that.height)
            {
                throw std::length_error(
                    std::string("\n\nERROR : mat operator-=(const mat& that) const\n")+
                    "\taddition of two different shaped matrix is not allowed\n"
                );
            }
            
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j) matrix[i][j]-=that.matrix[i][j];
            }
        }

        inline mat operator-(const T scalar) const
        {
            mat scaled_addition = *this;
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j)
                {
                    scaled_addition.matrix[i][j]-=scalar;
                }
            }
            return scaled_addition;
        }

        inline void operator-=(const T scalar)
        {
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j)
                {
                    matrix[i][j]-=scalar;
                }
            }
        }

        template<typename S> inline friend mat operator-(const S scalar, const mat& that)
        {
            mat scaled_addition = that;
            for(size_t i=0; i<scaled_addition.height; ++i)
            {
                for(size_t j=0; j<scaled_addition.width; ++j)
                {
                    scaled_addition.matrix[i][j] = scalar-scaled_addition.matrix[i][j];
                }
            }
            return scaled_addition;
        }

        /// ---------------------- Division -----------------------------
        /// @returns element by element division
        inline mat operator/(const mat& that) const
        {
            if(this->width!=that.width || this->height!=that.height)
            {
                throw std::length_error(
                    std::string("\n\nERROR : mat operator/(const mat& that) const\n")+
                    "\taddition of two different shaped matrix is not allowed\n"
                );
            }
            
            mat answer = *this;
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j) answer.matrix[i][j]/=that.matrix[i][j];
            }

            return answer;
        }

        inline void operator/=(const mat& that)
        {
            if(this->width!=that.width || this->height!=that.height)
            {
                throw std::length_error(
                    std::string("\n\nERROR : mat operator/=(const mat& that) const\n")+
                    "\taddition of two different shaped matrix is not allowed\n"
                );
            }
            
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j) matrix[i][j]/=that.matrix[i][j];
            }
        }

        inline mat operator/(const T scalar) const
        {
            mat scaled_addition = *this;
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j)
                {
                    scaled_addition.matrix[i][j]/=scalar;
                }
            }
            return scaled_addition;
        }

        inline void operator/=(const T scalar)
        {
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j)
                {
                    matrix[i][j]/=scalar;
                }
            }
        }

        template<typename S> inline friend mat operator/(const S scalar, const mat& that)
        {
            mat scaled_addition = that;
            for(size_t i=0; i<scaled_addition.height; ++i)
            {
                for(size_t j=0; j<scaled_addition.width; ++j)
                {
                    scaled_addition.matrix[i][j] = scalar/scaled_addition.matrix[i][j];
                }
            }
            return scaled_addition;
        }

        /// ---------------------- Multiplication -----------------------------
        /// @returns matrix multiplication / dot product
        inline mat operator*(const mat& that) const
        {
            if(this->width!=that.height)
            {
                throw std::length_error(
                    std::string("\n\nERROR : mat operator*(const mat& that) const\n")+
                    std::string("\tmultiplication of incompatible matrix shapes\n")+
                    "\tmat_a columns is not equal to the mat_b rows\n"
                );
            }

            mat answer(height,that.width,0);

            std::vector<std::vector<typename std::vector<T>::const_iterator>> row_tuple_iter;
            std::vector<std::vector<typename std::vector<T>::const_iterator>> col_tuple_iter;

            for(size_t i=0; i<height; ++i)     row_tuple_iter.push_back(this->row_iterators(i));
            for(size_t i=0; i<that.width; ++i) col_tuple_iter.push_back(that.column_iterators(i));

            for(size_t i=0; i<answer.height; ++i)
            {
                for(size_t j=0; j<answer.width; ++j)
                {
                    answer.matrix[i][j] = mat::dot((row_tuple_iter[i]),(col_tuple_iter[j]));
                }
            }

            return answer;
        }

        inline void operator*=(const mat& that)
        {
            *this = *this * that;
        }

        /// @returns hadamard matrix product - element by element multiplication, not to be confused with matrix multiplication
        void hadamard(const mat& that)
        {
            if(this->width!=that.width || this->height!=that.height)
            {
                throw std::length_error(
                    std::string("\n\nERROR : static mat hadamard(const mat& left, const mat& that) const\n")+
                    "\thadamard multiplication of two different shaped matrix is not allowed\n"
                );
            }
            
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j) matrix[i][j]*=that.matrix[i][j];
            }
        }

        inline mat operator*(const T scalar) const
        {
            mat scaled_addition = *this;
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j)
                {
                    scaled_addition.matrix[i][j]*=scalar;
                }
            }
            return scaled_addition;
        }

        inline void operator*=(const T scalar)
        {
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j)
                {
                    matrix[i][j]*=scalar;
                }
            }
        }
        
        template<typename S> inline friend mat operator*(const S scalar, const mat& that)
        {
            mat scaled_addition = that;
            for(size_t i=0; i<scaled_addition.height; ++i)
            {
                for(size_t j=0; j<scaled_addition.width; ++j)
                {
                    scaled_addition.matrix[i][j] = scalar*scaled_addition.matrix[i][j];
                }
            }
            return scaled_addition;
        }

        // ============================== MATRIX EXPOENTIAL ==============================

        /// @returns raised matrix to a certain number 'p'
        /// @note raising to a negative integer(inverse) is not supported yet but will be in the future
        void power(size_t p)
        {
            if(width!=height)
            {
                throw std::length_error("\n\nERROR : mat.power(size_t p)\n\tcannot raise a non-square matrix\n");
            }
            else if(p<0)
            {
                throw std::domain_error("\n\nERROR : mat.power(size_t p)\n\trasing to a negative number(-1 inverse) is not supported yet\n");
            }
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
        }

        // ============================== MATRIX TRANSFORMATION ==============================

        /// transpose self
        void transpose()
        {
            if(height==width)
            {
                // to be change
                mat answer(width,height,(T)0);
                for(size_t i=0; i<height; ++i)
                {
                    for(size_t j=0; j<width; ++j)
                    {
                        answer.matrix[j][i] = matrix[i][j]; 
                    }
                }
                *this = answer;
            }
            else
            {
                mat answer(width,height,(T)0);
                for(size_t i=0; i<height; ++i)
                {
                    for(size_t j=0; j<width; ++j)
                    {
                        answer.matrix[j][i] = matrix[i][j]; 
                    }
                }
                *this = answer;
            }
        }

        // ============================= INVERSE MATRIX ================================

        /// converts matrix to it's inverse form
        void inv()
        {
            if(height!=width) throw std::length_error("\n\nERROR : cyfre::mat::inv() - cannot inverse a non-square matrix");

            mat inverse(TYPE::IDENTITY,height);

            auto nonzrow = [](const mat<T>& input, size_t i, size_t j) -> long long int
            {
                for(size_t r=i; r<input.height; ++r)
                {
                    if(input.matrix[r][j]!=0)
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
                        inverse.row_scale(-input.matrix[i][pj],pi,i);
                        input.row_scale(-input.matrix[i][pj],pi,i);
                    }
                }
            };

            auto make_pivot = [&inverse](mat<T>& input, size_t pi, size_t pj)
            {
                inverse.scale_row(pi,DIV,input.matrix[pi][pj]);
                input.scale_row(pi,DIV,input.matrix[pi][pj]);
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

                if(matrix[cpi][cpj]!=1) make_pivot(*this,cpi,cpj);
                fix_pivot(*this,cpi,cpj);
                cpi++;
                cpj++;
            }

            for(size_t i=0; i<height; ++i)
            {
                if(matrix[i][i]==0) throw std::domain_error("\n\nERROR: cyfre::mat::inv() - matrix determinant is zero, cannot invert matrix");
            }

            matrix = inverse.matrix;
        }

        // ============================= ECHELON FORM ================================

        /// converts matrix to row echelon form of a matrix
        void ref()
        {
            auto nonzrow = [](const mat<T>& input, const size_t i, const size_t j) -> long long int
            {
                for(size_t r=i; r<input.height; ++r)
                {
                    if(input.matrix[r][j]!=0)
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
                    input.row_scale(-(input.matrix[i][pj]/input.matrix[pi][pj]),pi,i);
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

                if(nonzerorow!=cpi)
                {
                    row_swap(cpi,nonzerorow);
                }

                fix_nonzero_pivot(*this,cpi,cpj);
                cpi++;
                cpj++;
            }
        }

        /// converts matrix to reduced row echelon form of a matrix
        void rref()
        {
            auto nonzrow = [](const mat<T>& input, size_t i, size_t j) -> long long int
            {
                for(size_t r=i; r<input.height; ++r)
                {
                    if(input.matrix[r][j]!=0)
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
                        input.row_scale(-input.matrix[i][pj],pi,i);
                    }
                }
            };

            auto make_pivot = [](mat<T>& input, size_t pi, size_t pj)
            {
                input.scale_row(pi,DIV,input.matrix[pi][pj]);
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

                if(nonzerorow!=cpi) this->row_swap(cpi,nonzerorow);
                if(matrix[cpi][cpj]!=1) make_pivot(*this,cpi,cpj);
                fix_pivot(*this,cpi,cpj);
                cpi++;
                cpj++;
            }
        }

        // ================ applying function ==============================
        void apply(std::function<T(T)> function_name)
        {
            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j)
                {
                    matrix[i][j] = function_name(matrix[i][j]);
                }
            }
        }

    };// end of mat class

    template<typename T>
    void display(const mat<T>& input)
    {
        std::cout<<"\n[";
        for(size_t i=0; i<input.height; ++i)
        {
            std::cout<<"[";
            for(size_t j=0; j<input.width; ++j)
            {
                if(input.matrix[i][j]==0)
                    std::cout<<std::abs(input.matrix[i][j]);
                else
                    std::cout<<input.matrix[i][j];

                if(j!=input.width-1) std::cout<<' ';
            }
            std::cout<<"]";
            if(i!=input.height-1) std::cout<<",\n";
            else std::cout<<"]\n";
        }
    }
}

#endif

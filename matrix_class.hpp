#ifndef MATRIX_CLASS
#define MATRIX_CLASS

#include <iostream>
#include <numeric>
#include <fstream>
#include <limits>
#include <cstdio>
#include "helper_functions.hpp"

/*
        CONTAINS ALL CYFRE LIBRARY TYPES from classes, to enums, and typedefs
*/

namespace cyfre
{
    enum MATRIX_TYPES{
        /// @arg - a square matrix where every elements in the main diagonal has a value of '1'
        IDENTITY,
        /// @arg - a square matrix where every element is '0'
        NULLZERO,
        /// @arg - a square matrix where every elements in the main diagonal has a value of a given 'N'
        SCALAR,
        /// @arg - a nx1 matrix
        COLUMN,
        /// @arg - a 1xn matrix
        ROW
    };

    enum SCALAR_OPERATIONS { ADD, SUB, MUL, DIV };

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

        /// initializes a matrix from a text file
        mat(std::string text_file, char separator)
        {
            std::ifstream filereader;
            filereader.open(text_file.c_str());

            if(filereader.fail()){
                std::cerr<<"\nERROR : constructor::mat<T>(\""<<text_file<<"\")"<<std::endl;
                std::cerr<<"\tinitialization error, text file not found or might not be supported\n";
                exit(2);
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
                        std::cerr<<"\nERROR : constructor::mat<T>(\""<<text_file<<"\")"<<std::endl;
                        std::cerr<<"\tinitialization error, invalid number inside the text file:"<<text_file<<", on line:"<<i<<"\n";
                        exit(2);
                    }
                    if(isvalid_isrational.second) an_integer = false;
                }
                matrix_strings.push_back(row_parse);
            }

            for(size_t i=1; i<matrix_strings.size(); ++i)
            {
                if(matrix_strings[i].size()!=matrix_strings[i-1].size())
                {
                    std::cerr<<"\nERROR : constructor::mat<T>(\""<<text_file<<"\")"<<std::endl;
                    std::cerr<<"\tinitialization error, the text file provided an unequal length of rows\n";
                    std::cerr<<"\terror occurs in text file after comparison on line "<<i<<" & "<<i+1<<"\n";
                    exit(2);
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
                std::cerr<<"\n\nERROR : mat(std::vector<std::vector<T>>)\n";
                std::cerr<<"\tthe outer 'std::vector<>' is empty\n";
                exit(1);
            }

            size_t prev_row_len = matrix[0].size();
            for(size_t i=0; i<matrix.size();++i)
            {
                if(matrix[i].size()!=prev_row_len)
                {
                    std::cerr<<"\n\nERROR : mat(std::vector<std::vector<T>>)\n";
                    std::cerr<<"\tthe inner vector rows inside <std::vector'<std::vector<T>'> is not equal\n";
                    exit(1);
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

        /// initializes a square matrix with a given 'x' scalar values of elements in the main diagonal
        mat(const MATRIX_TYPES matrix_type, const size_t n, const T scalar)
        {
            size_t i=n, j=n;
            height = width = n;

            std::vector<T> row;
            row.reserve(n);
            matrix.reserve(n);

            while(j--) row.push_back(0);            
            while(i--) matrix.push_back(row);
            
            for(size_t i=0; i<n; ++i) matrix[i][i] = scalar;
        }
        
        mat(const MATRIX_TYPES matrix_type, const size_t n) : mat(matrix_type,n,0)
        {
            switch(matrix_type)
            {
                case IDENTITY: for(size_t i=0; i<n; ++i) matrix[i][i] = 1; break;
                case NULLZERO: break;
                case SCALAR  :
                    std::cerr<<"\n\nERROR : mat(MATRIX_TYPES matrix_type, size_t n, T scalar)\n";
                    std::cerr<<"\tSCALAR matrix initialization, missing argument\n";
                    exit(1);
                default:
                    std::cerr<<"\n\nERROR : mat()\n\tmatrix initialization\n";
                    exit(1);
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
                std::cerr<<"\n\nERROR : T dot(std::vector<typename std::vector<T>> iter_tuple1, std::vector<typename std::vector<T>> iter_tuple2)\n";
                std::cerr<<"\tarray don't have the same lenght\n";
                std::cout<<"\titer_tuple1 length : "<<iter_tuple1.size()<<'\n';
                std::cout<<"\titer_tuple2 length : "<<iter_tuple2.size()<<'\n';
                exit(1); 
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
                std::cerr<<"\n\nERROR : mat.trace()\n";
                std::cerr<<"\tthe matrix is not a square matrix, cannot get trace\n";
                exit(1);
            }

            T trace_total = 0;
            for(size_t i=0; i<height; ++i) trace_total+=matrix[i][i];
        }

        /// @returns T determinant of matrix, this method is using LU Decomposition
        /*
        long long int determinant() const
        {
            std::vector<std::vector<T>> lower=matrix, upper=matrix;
            size_t i=0, j=0, k=0, n=height;
            for(i=0; i<n; i++)
            {
                for(j=0; j<n; j++)
                {
                    if(j<i) lower[j][i] = 0;
                    else
                    {
                        lower[j][i] = matrix[j][i];
                        for (k=0; k<i; k++) lower[j][i] = lower[j][i] - lower[j][k] * upper[k][i];
                    }
                }
                for(j=0; j<n; j++)
                {
                    if(j<i)       upper[i][j] = 0;
                    else if(j==i) upper[i][j] = 1;
                    else
                    {
                        upper[i][j] = matrix[i][j] / lower[i][i];
                        for (k = 0; k < i; k++) upper[i][j] = upper[i][j] - ((lower[i][k] * upper[k][j]) / lower[i][i]);
                    }
                }
            }

            long long int upper_determinant = 1, lower_determinant = 1;
            for(size_t i = 0; i < n; ++i)
            {
                upper_determinant *= upper[i][i];
                lower_determinant *= lower[i][i];
            }
            return upper_determinant*lower_determinant;
        }
        */

        // ============================== ROW ==============================

        /// @returns std::vector<typename std::vector<T>::const_iterator> of a row
        std::vector<typename std::vector<T>::const_iterator> row_iterators(size_t row_index) const
        {
            if((row_index < 0) ^ (row_index > width))
            {
                std::cerr<<"\n\nERROR : std::vector<typename std::vector<T>::const_iterator> row_iterators(size_t row_index)\n";
                std::cerr<<"\tthe given row index is out of bound\n";
                exit(1);
            }

            std::vector<typename std::vector<T>::const_iterator> row_iterator;
            for(size_t i=0; i<width; ++i) row_iterator.push_back(matrix[row_index].begin()+i);
            return row_iterator;
        }

        /// @returns std::vector<typename std::vector<T>::iterator> of a row
        std::vector<typename std::vector<T>::iterator> row_iterators_r(size_t row_index)
        {
            if((row_index < 0) ^ (row_index > width))
            {
                std::cerr<<"\n\nERROR : std::vector<typename std::vector<T>::iterator> row_iterators_r(size_t row_index)\n";
                std::cerr<<"\tthe given row index is out of bound\n";
                exit(1);
            }

            std::vector<typename std::vector<T>::iterator> row_iterator;
            for(size_t i=0; i<width; ++i) row_iterator.push_back(matrix[row_index].begin()+i);
            return row_iterator;
        }

        /// @returns std::vector<std::vector<T>> of a row
        std::vector<std::vector<T>> row(size_t row_index) const
        {
            if((row_index < 0) ^ (row_index > width))
            {
                std::cerr<<"\n\nERROR : std::vector<std::vector<T>> row(size_t row_index)\n";
                std::cerr<<"\tthe given row index is out of bound\n";
                exit(1);
            }

            std::vector<std::vector<T>> row_vector;
            row_vector.reserve(width);
            row_vector.insert(row_vector.end(),matrix[row_index].begin(),matrix[row_index].end());
            return row_vector;
        }

        /// 'ADD,SUB,MUL, or DIV' a given 'const T value' to all elements of a selected 'const size_t row_index' 
        void scale_row(const size_t row_index, const SCALAR_OPERATIONS scalar_operation, const T value)
        {
            if((row_index < 0) ^ (row_index > width))
            {
                std::cerr<<"\n\nERROR : void scale_row(const size_t row_index, const SCALAR_OPERATIONS scalar_operation, const T value)\n";
                std::cerr<<"\tthe given row index is out of bound\n";
                exit(1);
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
                        std::cerr<<"\n\nERROR : scale_row(const size_t row_index, const SCALAR_OPERATIONS scalar_operation, const T value)\n";
                        std::cerr<<"\tscale_row was given an invalid operation\n";
                        exit(1);
                }
            };

            for(size_t i=0; i<width; ++i)
            {
                matrix[row_index][i] = operation_function(matrix[row_index][i],value);
            }
        }

        void row_operation(const size_t output_index, const SCALAR_OPERATIONS scalar_operation, size_t input_index)
        {
            if((output_index < 0) ^ (output_index > width))
            {
                std::cerr<<"\n\nERROR : void row_operation(const size_t output_index, const SCALAR_OPERATIONS scalar_operation, size_t input_index)\n";
                std::cerr<<"\tthe given row 'output_index' is out of bound\n";
                exit(1);
            }
            else if((input_index < 0) ^ (input_index > width))
            {
                std::cerr<<"\n\nERROR : void row_operation(const size_t output_index, const SCALAR_OPERATIONS scalar_operation, size_t input_index)\n";
                std::cerr<<"\tthe given row 'input_index'  is out of bound\n";
                exit(1);
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
                        std::cerr<<"\n\nERROR : void row_operation(const size_t output_index, const SCALAR_OPERATIONS scalar_operation, size_t input_index)\n";
                        std::cerr<<"\tthe 'scalar_operation' given was invalid\n";
                        exit(1);
                }
            };

            for(size_t i=0; i<width; ++i)
            {
                matrix[output_index][i] = operation_function(matrix[output_index][i],matrix[input_index][i]);
            }
        }

        // ============================== COLUMN ==============================

        /// @returns std::vector<typename std::vector<T>::const_iterator> of a column
        std::vector<typename std::vector<T>::const_iterator> column_iterators(size_t column_index) const
        {
            if((column_index < 0) ^ (column_index > height))
            {
                std::cerr<<"\n\nERROR : std::vector<typename std::vector<T>::const_iterator> column_iterators(size_t column_index)\n";
                std::cerr<<"\tthe given column index is out of bound\n";
                exit(1);
            }

            std::vector<typename std::vector<T>::const_iterator> column_iterator;
            for(size_t i=0; i<height; ++i) column_iterator.push_back(matrix[i].begin()+column_index);
            return column_iterator;
        }

        /// @returns std::vector<typename std::vector<T>::iterator> of a column
        std::vector<typename std::vector<T>::iterator> column_iterators_r(size_t column_index)
        {
            if((column_index < 0) ^ (column_index > height))
            {
                std::cerr<<"\n\nERROR : std::vector<typename std::vector<T>::iterator> column_iterators_r(size_t column_index)\n";
                std::cerr<<"\tthe given column index is out of bound\n";
                exit(1);
            }

            std::vector<typename std::vector<T>::iterator> column_iterator;
            for(size_t i=0; i<height; ++i) column_iterator.push_back(matrix[i].begin()+column_index);
            return column_iterator;
        }

        /// @returns std::vector<std::vector<T>> of a column
        std::vector<std::vector<T>> column(size_t column_index) const
        {
            if((column_index < 0) ^ (column_index > height))
            {
                std::cerr<<"\n\nERROR : std::vector<std::vector<T>> column(size_t column_index)\n";
                std::cerr<<"\tthe given column index is out of bound\n";
                exit(1);
            }

            std::vector<std::vector<T>> column_vector;
            column_vector.reserve(height);
            for(size_t i=0; i<height; ++i) column_vector.push_back(matrix[column_index][i]);
            return column_vector;
        }

        /// 'ADD,SUB,MUL, or DIV' a given 'const T value' to all elements of a selected 'const size_t column_index'
        void scale_column(const size_t column_index, const SCALAR_OPERATIONS scalar_operation, const T value)
        {
            if((column_index < 0) ^ (column_index > height))
            {
                std::cerr<<"\n\nERROR : void scale_column(const size_t column_index, const SCALAR_OPERATIONS scalar_operation, const T value)\n";
                std::cerr<<"\tthe given column index is out of bound\n";
                exit(1);
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
                        std::cerr<<"\n\nERROR : scale_column(const size_t column_index, const SCALAR_OPERATIONS scalar_operation, const T value)\n";
                        std::cerr<<"\tscale_column was given an invalid operation\n";
                        exit(1);
                }
            };

            for(size_t i=0; i<height; ++i)
            {
                matrix[i][column_index] = operation_function(matrix[i][column_index],value);
            }
        }

        void column_operation(const size_t output_index, const SCALAR_OPERATIONS scalar_operation, size_t input_index)
        {
            if((output_index < 0) ^ (output_index > height))
            {
                std::cerr<<"\n\nERROR : void column_operation(const size_t output_index, const SCALAR_OPERATIONS scalar_operation, size_t input_index)\n";
                std::cerr<<"\tthe given column 'output_index' is out of bound\n";
                exit(1);
            }
            else if((input_index < 0) ^ (input_index > height))
            {
                std::cerr<<"\n\nERROR : void column_operation(const size_t output_index, const SCALAR_OPERATIONS scalar_operation, size_t input_index)\n";
                std::cerr<<"\tthe given column 'input_index' is out of bound\n";
                exit(1);
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
                        std::cerr<<"\n\nERROR : void column_operation(const size_t output_index, const SCALAR_OPERATIONS scalar_operation, size_t input_index)\n";
                        std::cerr<<"\tthe 'scalar_operation' given was invalid\n";
                        exit(1);
                }
            };

            for(size_t i=0; i<height; ++i)
            {
                matrix[i][output_index] = operation_function(matrix[i][output_index],matrix[i][input_index]);
            }
        }

        // ============================== MATRIX OPERATIONS ==============================

        /// ---------------------- Addition -----------------------------
        /// @returns element by element addition
        inline mat operator+(const mat& that) const
        {
            if(this->width!=that.width || this->height!=that.height)
            {
                std::cerr<<"\n\nERROR : mat operator+(const mat& that) const\n";
                std::cerr<<"\taddition of two different shaped matrix is not allowed\n";
                exit(1);
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
                std::cerr<<"\n\nERROR : mat operator-(const mat& that) const\n";
                std::cerr<<"\taddition of two different shaped matrix is not allowed\n";
                exit(1);
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
                std::cerr<<"\n\nERROR : mat operator-(const mat& that) const\n";
                std::cerr<<"\taddition of two different shaped matrix is not allowed\n";
                exit(1);
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
                std::cerr<<"\n\nERROR : mat operator-(const mat& that) const\n";
                std::cerr<<"\taddition of two different shaped matrix is not allowed\n";
                exit(1);
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
                std::cerr<<"\n\nERROR : mat operator/(const mat& that) const\n";
                std::cerr<<"\taddition of two different shaped matrix is not allowed\n";
                exit(1);
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
                std::cerr<<"\n\nERROR : mat operator-(const mat& that) const\n";
                std::cerr<<"\taddition of two different shaped matrix is not allowed\n";
                exit(1);
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
                std::cerr<<"\n\nERROR : mat operator*(const mat& that) const\n";
                std::cerr<<"\tmultiplication of incompatible matrix shapes\n";
                std::cerr<<"\tmat_a columns is not equal to the mat_b rows\n";
                exit(1);
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
                std::cerr<<"\n\nERROR : static mat hadamard(const mat& left, const mat& that) const\n";
                std::cerr<<"\thadamard multiplication of two different shaped matrix is not allowed\n";
                exit(1);
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
                std::cerr<<"\n\nERROR : mat.power(size_t p)\n\tcannot raise a non-square matrix\n";
                exit(1);
            }
            else if(p<0)
            {
                std::cerr<<"\n\nERROR : mat.power(size_t p)\n\trasing to a negative number(-1 inverse) is not supported yet\n";
                exit(1);
            }
            if(p==0)
            {
                mat<T> identity(IDENTITY,width);
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
    };

    template<typename T>
    void display(const mat<T>& input)
    {
        std::cout<<"\n[";
        for(size_t i=0; i<input.height; ++i)
        {
            std::cout<<"[";
            for(size_t j=0; j<input.width; ++j)
            {
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

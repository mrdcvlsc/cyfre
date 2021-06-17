#ifndef CYFRE_HPP
#define CYFRE_HPP

#include <iostream>
#include <numeric>
#include <vector>

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

        mat()
        {
            height = 1;
            width = 1;
            std::vector<T> default_index;
            default_index.push_back(T(0));
            matrix.push_back(default_index);
        }

        // mat(const std::string text_file)
        // {

        // }

        /// initializes a matrix using a 2 dimension vector : @arg std::vector<std::vector<T>> matrix
        mat(std::vector<std::vector<T>> matrix)
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

        /// initializes a matrix given a @arg height, @arg width for the matrix shape, and a @arg default_value of all elements in the matrix
        mat(size_t height, size_t width, T default_value)
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
        mat(MATRIX_TYPES matrix_type, size_t n, T scalar)
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
        
        mat(MATRIX_TYPES matrix_type, size_t n) : mat(matrix_type,n,0)
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

        // ============================== scalar return methods ==============================

        /// @returns the dot product of two std::vector<typename std::vector<T>::const_iterator>> :=
        /// it accepts a vector of iterators that points to row or column elements or a matrix
        static T dot(std::vector<typename std::vector<T>::const_iterator> iter_tuple1, std::vector<typename std::vector<T>::const_iterator> iter_tuple2)
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
            if(row_index < 0 ^ row_index > width)
            {
                std::cerr<<"\n\nERROR : std::vector<typename std::vector<T>::const_iterator> row_iterators(size_t row_index)\n";
                std::cerr<<"\tthe given row index is out of bound\n";
                exit(1);
            }

            std::vector<typename std::vector<T>::const_iterator> row_iterator;
            for(size_t i=0; i<width; ++i) row_iterator.push_back(matrix[row_index].begin()+i);
            return row_iterator;
        }

        /// @returns std::vector<std::vector<T>> of a row
        std::vector<std::vector<T>> row(size_t row_index) const
        {
            if(row_index < 0 ^ row_index > width)
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

        // ============================== COLUMN ==============================

        /// @returns std::vector<typename std::vector<T>::const_iterator> of a column
        std::vector<typename std::vector<T>::const_iterator> column_iterators(size_t column_index) const
        {
            if(column_index < 0 ^ column_index > height)
            {
                std::cerr<<"\n\nERROR : std::vector<typename std::vector<T>::const_iterator> column_iterators(size_t column_index)\n";
                std::cerr<<"\tthe given column index is out of bound\n";
                exit(1);
            }

            std::vector<typename std::vector<T>::const_iterator> column_iterator;
            for(size_t i=0; i<height; ++i) column_iterator.push_back(matrix[i].begin()+column_index);
            return column_iterator;
        }

        /// @returns std::vector<std::vector<T>> of a column
        std::vector<std::vector<T>> column(size_t column_index) const
        {
            if(column_index < 0 ^ column_index > height)
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

        // ============================== SCALAR MATRIX OPERATIONS ==============================

        /// scales the matrix itself, changing it's own value
        void scale(SCALAR_OPERATIONS scalar_operation, T scalar)
        {
            auto scalar_function = [](SCALAR_OPERATIONS scalar_operation, const T scalar, typename std::vector<T>::iterator index)->void
            {
                switch(scalar_operation)
                {
                case ADD: (*index) += scalar; break;
                case SUB: (*index) -= scalar; break;
                case MUL: (*index) *= scalar; break;
                case DIV: (*index) /= scalar; break;
                default:
                    std::cerr<<"\n\nERROR : void scale(SCALAR_OPERATIONS scalar_operation, T scalar="<<scalar_operation<<")\n";
                    std::cerr<<"\tSCALAR_OPERATIONS has invalid argument value, the valid SCALAR_OPERATION values are: ADD, SUB, MULL, and DIV\n";
                    exit(1);
                }
            };

            for(size_t i=0; i<height; ++i)
            {
                for(size_t j=0; j<width; ++j)
                {
                    scalar_function(scalar_operation,scalar,(*(matrix.begin()+i)).begin()+j);
                }
            }
        }

        // ============================== MATRIX OPERATIONS ==============================

        /// @returns element by element addition
        mat operator+(const mat& that) const
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

        /// @returns element by element subtraction
        mat operator-(const mat& that) const
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
                for(size_t j=0; j<width; ++j) answer.matrix[i][j]-=that.matrix[i][j];
            }

            return answer;
        }

        /// @returns matrix multiplication
        mat operator*(const mat& that) const
        {
            if(this->width!=that.width || this->height!=that.height)
            {
                std::cerr<<"\n\nERROR : mat operator-(const mat& that) const\n";
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
                for(size_t j=0; j<answer.height; ++j)
                {
                    answer.matrix[i][j] = mat::dot((row_tuple_iter[i]),(col_tuple_iter[j]));
                }
            }

            return answer;
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
}

#endif

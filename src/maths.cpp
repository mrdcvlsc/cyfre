#include "cyfre.h"
#include <string>

namespace cyfre
{
    matrix_int64 matrix_int64::scale_mul(i64 scalar) const{
        vector<i64> answer = _matrix;
        size_t matrix_size = _matrix.size();
        for(size_t i=0; i<matrix_size; ++i){
            answer[i]*=scalar;
        }
        return matrix_int64(width,height,answer);
    }

    matrix_int64 matrix_int64::scale_add(i64 scalar) const{
        vector<i64> answer = _matrix;
        size_t matrix_size = _matrix.size();
        for(size_t i=0; i<matrix_size; ++i){
            answer[i]+=scalar;
        }
        return matrix_int64(width,height,answer);
    }

    matrix_int64 matrix_int64::scale_sub(i64 scalar) const{
        vector<i64> answer = _matrix;
        size_t matrix_size = _matrix.size();
        for(size_t i=0; i<matrix_size; ++i){
            answer[i]-=scalar;
        }
        return matrix_int64(width,height,answer);
    }

    matrix_int64 matrix_int64::scale_div(i64 scalar) const{
        vector<i64> answer = _matrix;
        size_t matrix_size = _matrix.size();
        for(size_t i=0; i<matrix_size; ++i){
            answer[i]/=scalar;
        }
        return matrix_int64(width,height,answer);
    }

    matrix_int64 matrix_int64::transpose() const{
        matrix_int64 answer(height,width);
        size_t ci = 0;
        for(size_t j=0; j<width; ++j){
            for(size_t i=0; i<height; ++i){
                answer._matrix[ci] = this->operator()(i,j);
                ++ci;    
            }
        }
        return answer;
    }

    i64 matrix_int64::trace() const{
        if(height!=width){
            cerr<<"ERROR : trace() - Matrix is not a square, cannot be traced...\n";
            exit(1);
        }
        i64 answer = 0;
        for(size_t i=0; i<height; ++i){
            answer+=this->operator()(i,i);
        }
        return answer;
    }

    i64 matrix_int64::sum() const{
        i64 answer = 0;
        size_t n = _matrix.size();
        for(size_t i=0; i<n; ++i){
            answer+=_matrix[i];
        }
        return answer;
    }

    size_t matrix_int64::area() const{
        return width*height;
    }
}
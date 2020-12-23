#include "cyfre.h"

namespace cyfre
{
    void matrix_int64::view() const{
        for(size_t i=0; i<this->height; ++i){
            for(size_t j=0; j<this->width; ++j)
                cout<<this->operator()(i,j)<<' ';
            cout<<'\n';
        }
    }

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
        for(size_t i=0; i<height; ++i){
            for(size_t j=0; j<width; ++j){
                answer+=this->operator()(i,j);
            }
        }
        return answer;
    }

    size_t matrix_int64::area() const{
        return width*height;
    }

    void matrix_int64::status(string name) const{
        cout<<"Matrix : "<<name<<'\n';
        cout<<"Area : "<<this->area()<<'\n';
        cout<<"Dimensions : "<<this->height<<'x'<<this->width<<'\n';
    }

    i64 matrix_int64::det() const{
        matrix_int64 a = *this;
		matrix_int64 l = a, u = a;
		long long int i = 0, j = 0, k = 0, n = a.height;
		//lower
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (j < i)
				l(j,i) = 0;
				else {
					l(j,i) = a(j,i);
					for (k = 0; k < i; k++) {
					l(j,i) = l(j,i) - l(j,k) * u(k,i);
					}
				}
			}
			//upper
			for (j = 0; j < n; j++) {
				if (j < i)
				u(i,j) = 0;
				else if (j == i)
				u(i,j) = 1;
				else {
					u(i,j) = a(i,j) / l(i,i);
					for (k = 0; k < i; k++) {
					u(i,j) = u(i,j) - ((l(i,k) * u(k,j)) / l(i,i));
					}
				}
			}
		}

		long long int det1u = 1, det2l = 1;
		for(long long int i = 0; i < n; ++i){
				det1u *= u(i,i);
				det2l *= l(i,i);
		}
		
		return det1u*det2l;
	}
}
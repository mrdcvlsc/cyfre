#include "cyfre.h"
namespace cyfre
{
	matrix_int64 matrix_int64::operator+(const matrix_int64& rmat) const{
		if(this->width!=rmat.width || this->height!=rmat.height){
			cerr<<"ERROR : addition of two matrix shape do not match...\n";
			exit(1);
		}
		matrix_int64 answer = *this;
		size_t tmpsize = answer._matrix.size();
		for(size_t i=0; i<tmpsize; ++i){
			answer._matrix[i] = answer._matrix[i] + rmat._matrix[i];
		}
		return answer;
	}

	matrix_int64 matrix_int64::operator-(const matrix_int64& rmat) const{
		if(this->width!=rmat.width || this->height!=rmat.height){
			cerr<<"ERROR : subtraction of two matrix shape do not match...\n";
			exit(1);
		}
		matrix_int64 answer = *this;
		size_t tmpsize = answer._matrix.size();
		for(size_t i=0; i<tmpsize; ++i){
			answer._matrix[i] = answer._matrix[i] - rmat._matrix[i];
		}
		return answer;
	}

	matrix_int64 matrix_int64::operator*(const matrix_int64& rmat) const{
		if(this->width!=rmat.height){
			cout<<"matrix 1 widht : "<<width<<'\n';
			cout<<"matrix 2 height: "<<rmat.height<<'\n';
			cerr<<"ERROR : multiplication of incompatible matrix shapes; \n";
			cerr<<"\tMatrix1 width/no.of_columns is not equal to the height/no.of_rows of Matrix2...\n";
			exit(1);
		}
		matrix_int64 answer(height,rmat.width);
		
		vector<vector<i64>>A;
		vector<vector<i64>>B;

		for(size_t i=0; i<height; ++i){
			A.push_back(this->row(i));
		}

		for(size_t i=0; i<rmat.width; ++i){
			B.push_back(rmat.col(i));
		}

		for(size_t i=0; i<answer.height; ++i){
			for(size_t j=0; j<answer.width; ++j){
				answer(i,j) = dot_product_i64(A[i],B[j]);
			}
		}

		return answer;
	}
}
#include "cyfre.h"

namespace cyfre
{

	i64 dot_product_i64(vector<i64> a, vector<i64> b){
		size_t length = a.size();
		if(length!=b.size()){
            cout<<"array1 length : "<<a.size()<<'\n';
            cout<<"array2 length : "<<b.size()<<'\n';
			cerr<<"ERROR : dot multiplication, array don't have the same lenght...";
			exit(1); 
		}
		
		i64 summation = 0;
		for(size_t i=0; i<length; ++i){
			summation+=(a[i]*b[i]);
		}
		return summation;
	}

	matrix_int64 hadamard(matrix_int64 a, matrix_int64 b){
		if(a.height==b.height && a.width==b.width){
			matrix_int64 answer(a.width,a.height);
			for(size_t i=0; i<a.height; ++i){
				for(size_t j=0; j<a.width; ++j){
					answer(i,j) = a(i,j) * b(i,j);
				}
			}
			return answer;
		}
		else{
			cerr<<"ERROR : hadamard() - the matrix is not a square matrix\n";
			exit(1);
		}
		return matrix_int64(1);
	}
}
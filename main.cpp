#include <iostream>
#include <chrono>
#include <vector>
//#include "array_matrix.h"
#include "cyfre.h"

using namespace std;
using namespace std::chrono;

int main(){

	cyfre::matrix_int32 
		mat1({{1,2,3},
		      {4,5,6},
		      {7,8,9}}),

		mat2({{9,8,7},
		      {6,5,4},
		      {3,2,1}});

	cyfre::matrix_int32 answer = mat1 + mat2;

	for(size_t i=0; i<answer.height; ++i){
		for(size_t j=0; j<answer.width; ++j)
			cout<<answer(i,j)<<' ';
		cout<<'\n';
	}
	cout<<endl;
	/*
	dimensions *a = new matrix_int64(4);
	dimensions *b = new matrix_float64(5);

	a->_matrix[0][0];
	array_matrix<int> mymatrix1(5);
	array_matrix<float> mymatrix2(2,5);
	array_matrix<double> mymatrix3(5,4);

	cout<<mymatrix1.value()<<endl<<endl;
	cout<<mymatrix2.value()<<endl<<endl;
	cout<<mymatrix3.value()<<endl<<endl;
	*/

	return 0;
}
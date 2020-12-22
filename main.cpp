#include <iostream>
#include <chrono>
#include <vector>

//#include "array_matrix.h"
#include "cyfre.h"

using namespace std;
using namespace std::chrono;

int main(){

	cyfre::matrix_int64 
		mat1({{6,5},
		      {1,3},
		      {3,7}}),

		mat2({{6,1,8},
		      {2,8,3}});

	mat2(2,2) = 777;

	mat1.status("mat1");
	mat2.status("mat2");
	
	cyfre::matrix_int64 answer = mat1 * mat2;

	for(size_t i=0; i<answer.height; ++i){
		for(size_t j=0; j<answer.width; ++j)
			cout<<answer(i,j)<<' ';
		cout<<'\n';
	}
	cout<<endl;

	answer = answer.scalar(2);

	answer.view();

	vector<cyfre::i64> a = {3,1,8};
	vector<cyfre::i64> b = {4,2,3};

	cout<<"dot product answer : "<<cyfre::dot_product_i64(a,b)<<endl;
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
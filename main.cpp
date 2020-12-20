#include <iostream>
#include <chrono>
//#include "array_matrix.h"
#include "cyfre.h"

using namespace std;
using namespace std::chrono;

int main(){

	cyfre::matrix_int32 obj(3,4,{ 
		2, 4, 6,
	    8, 5, 3,
	    7, 2, 1,
	    3, 1, 9
	});

	cyfre::matrix_int32 arrays({1,2,3,4,5,6,7,8,9,10});
	
	cyfre::array_view(arrays.row(0));


	size_t cnt=0;
	for(int i=0;i<obj.height;++i){
		for(int j=0;j<obj.width;++j){
			cout<<obj(i,j)<<' ';
		}
		cout<<'\n';
	}

	vector<long long int> rows = obj.row(1);

	cyfre::array_view(rows);
	cyfre::array_view(obj.col(1));

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
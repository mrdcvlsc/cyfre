#include <iostream>
#include <chrono>
#include <vector>
#include "cyfre.h"

using namespace std;
using namespace std::chrono;

int main(){

	cyfre::matrix_int64 
		mymatrix({{1,2,2},
		      	  {1,1,1},
		     	  {1,1,1}});

	cyfre::matrix_int64 squared = mymatrix * mymatrix;

	squared.view();

	cout<<"\nTRACE VALUE : "<<squared.trace();

	squared = hadamard(squared,mymatrix);

	cout<<"\nhadamard multipication : \n";
	squared.view();
	cout<<"\nSUM OF ELEMENTS = "<<squared.sum();

	cyfre::matrix_int64 test(
		{{1,2},
		 {3,4}}
	),
	test2({
		{2,2},
		{2,2}
	});

	cout<<"\n\ndet = "<<test.det()<<endl;

	cout<<"mult test : \n";
	test = cyfre::hadamard(test,test2);
	test.view();

	return 0;
}
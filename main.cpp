#include <iostream>
#include <chrono>
#include <vector>
#include "cyfre.h"

using namespace std;
using namespace std::chrono;

int main(){

	cyfre::matrix_int64 test2(4,"scalar",1), test3(5,"fill",77), test4(6,"diag",{1,2,3,4,5,6});
	
	test2.view(), cout<<endl<<endl;
	test3.view(), cout<<endl<<endl;
	test4.view(), cout<<endl<<endl;
	return 0;
}
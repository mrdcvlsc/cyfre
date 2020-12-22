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
}
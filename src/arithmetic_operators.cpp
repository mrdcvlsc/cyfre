#include "cyfre.h"
namespace cyfre
{
	matrix_int32 matrix_int32::operator+(const matrix_int32& rmat) const{
		if(this->width!=rmat.width || this->height!=rmat.height){
			cerr<<"ERROR : addition of two matrix shape do not match...\n";
			exit(1);
		}
		matrix_int32 answer = *this;
		size_t tmpsize = answer._matrix.size();
		for(size_t i=0; i<tmpsize; ++i){
			answer._matrix[i] = answer._matrix[i] + rmat._matrix[i];
		}
		return answer;
	}

	matrix_int32 matrix_int32::operator-(const matrix_int32& rmat) const{
		if(this->width!=rmat.width || this->height!=rmat.height){
			cerr<<"ERROR : subtraction of two matrix shape do not match...\n";
			exit(1);
		}
		matrix_int32 answer = *this;
		size_t tmpsize = answer._matrix.size();
		for(size_t i=0; i<tmpsize; ++i){
			answer._matrix[i] = answer._matrix[i] - rmat._matrix[i];
		}
		return answer;
	}
}
#include "cyfre.h"

namespace cyfre
{
	matrix_int32::matrix_int32(size_t w)
	{
		this->width = this->height = w;
		_matrix.assign(w*w,0);
	}

	matrix_int32::matrix_int32(size_t width, size_t height)
	{
		this->width = width;
		this->height = height;
		_matrix.assign(width*height,0);
	}

	matrix_int32::matrix_int32(vector<long long int> _matrix){
		width = _matrix.size();
		height = 1;
		this->_matrix = _matrix;
	}

	matrix_int32::matrix_int32(size_t swidth, vector<long long int> _matrix){

		if(swidth*swidth!=_matrix.size())
		{
			cerr<<"matrix_int32 : Object creation failed\n";
			cerr<<"ERROR in array size, make sure that your swidth and height match the number of elements your array have\n";
			cerr<<"parameters : size_t swidth, vector<long long int> _matrix\n";
			exit(1);
		}
		this->height = this->width = swidth;
		this->_matrix = _matrix;
	}

	matrix_int32::matrix_int32(size_t width, size_t height, vector<long long int> _matrix){

		if(width*height!=_matrix.size())
		{
			cerr<<"matrix_int32 : Object creation failed\n";
			cerr<<"ERROR in array size, make sure that your width and height match the number of elements your array have\n";
			cerr<<"parameters : size_t width, size_t height, vector<long long int> _matrix\n";
			exit(1);
		}
		this->width = width;
		this->height = height;
		this->_matrix = _matrix;
	}
}
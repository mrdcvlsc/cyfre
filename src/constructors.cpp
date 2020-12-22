#include "cyfre.h"

namespace cyfre
{
	matrix_int64::matrix_int64(size_t w) // N x N
	{
		this->width = this->height = w;
		_matrix.assign(w*w,0);
	}

	matrix_int64::matrix_int64(size_t width, size_t height) // N x M
	{
		this->width = width;
		this->height = height;
		_matrix.assign(width*height,0);
	}

	matrix_int64::matrix_int64(vector<i64> _matrix){ // 1 x N
		width = _matrix.size();
		height = 1;
		this->_matrix = _matrix;
	}

	matrix_int64::matrix_int64(size_t swidth, vector<i64> _matrix){ // N x N

		if(swidth*swidth!=_matrix.size())
		{
			cerr<<"matrix_int64 : Object creation failed\n";
			cerr<<"ERROR in array size, make sure that your swidth and height match the number of elements your array have\n";
			cerr<<"parameters : size_t swidth, vector<i64> _matrix\n";
			exit(1);
		}
		this->height = this->width = swidth;
		this->_matrix = _matrix;
	}

	matrix_int64::matrix_int64(size_t width, size_t height, vector<i64> _matrix){ // N x M

		if(width*height!=_matrix.size())
		{
			cerr<<"matrix_int64 : Object creation failed\n";
			cerr<<"ERROR in array size, make sure that your width and height match the number of elements your array have\n";
			cerr<<"parameters : size_t width, size_t height, vector<i64> _matrix\n";
			exit(1);
		}
		this->width = width;
		this->height = height;
		this->_matrix = _matrix;
	}

	matrix_int64::matrix_int64(vector<vector<i64>> array2d){ // 2d vector input
		this->width = array2d[0].size();
		this->height = array2d.size();
		for(size_t i=0; i<this->height; ++i)
		{
			_matrix.insert(_matrix.end(),array2d[i].begin(),array2d[i].end());
		}
	}
}
#include "cyfre.h"

namespace cyfre
{
	// zero fills
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

	// values fills
	matrix_int64::matrix_int64(size_t w, i64 values) // N x N
	{
		this->width = this->height = w;
		_matrix.assign(w*w,values);
	}

	matrix_int64::matrix_int64(size_t w, string type, i64 values) // scalar
	{
		this->width = this->height = w;

		 if(type=="fill"){
			_matrix.assign(w*w,values);
		 }
		else if(type=="scalar"){
			_matrix.assign(w*w,0);
			for (size_t i = 0; i < width; i++)
			{
				this->operator()(i,i) = values;
			}
		}
		else{
			cerr<<"ERROR : constructor matrix type 2nd argument invalid - the only available arguments are \"fill\", \"scalar\", \"diag\"\n";
			exit(1);
		}
	}

	matrix_int64::matrix_int64(size_t w, string type, vector<i64> diagonal_values){
		if(type!="diag"){
			cerr<<"ERROR : constructor matrix type 2nd argument invalid - the only available arguments are \"fill\", \"scalar\", \"diag\"\n";
			exit(1);
		}
		if(w!=diagonal_values.size()){
			cerr<<"ERROR : constructor matrix \"diag\" type - 'size w' did not match 'diagonal_values size'\n";
			exit(1);
		}

		this->width = this->height = w;
		_matrix.assign(w*w,0);

		for(size_t i=0; i<w; ++i){
			this->operator()(i,i) = diagonal_values[i];
		}
	}

	matrix_int64::matrix_int64(size_t width, size_t height, i64 values) // N x M
	{
		this->width = width;
		this->height = height;
		_matrix.assign(width*height,values);
	}

	// exact values
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
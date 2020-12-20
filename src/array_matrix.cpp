#include "array_matrix.h"
			
dimensions::dimensions(size_t s)
{	
	_height = _width = s;
}

dimensions::dimensions(size_t w, size_t h)
{
	_width = w;
	_height = h;
}

matrix_int64::matrix_int64(size_t s): dimensions(s)
{
	_matrix = new long long int*[s];
	for(size_t i=0; i<s; ++i)
	{
		_matrix[i] = new long long int[s];
		memset(_matrix[i],0,sizeof(_matrix[i]));
	}
}

matrix_int64::matrix_int64(size_t w, size_t h): dimensions(w,h)
{
	_matrix = new long long int*[h];
	for(size_t i=0; i<h; ++i)
	{
		_matrix[i] = new long long int[w];
		memset(_matrix[i],0,sizeof(_matrix[i]));
	}
}

matrix_int64::~matrix_int64()
{
	for (size_t i=0; i<_height; i++)
	{
   		delete[] _matrix[i];
	}
	delete[] _matrix;
}

matrix_float64::matrix_float64(size_t s): dimensions(s)
{
	
	_matrix = new long double*[s];
	for(size_t i=0; i<s; ++i)
	{
		_matrix[i] = new long double[s];
		memset(_matrix[i],0,sizeof(_matrix[i]));
	}
}

matrix_float64::matrix_float64(size_t w, size_t h): dimensions(w,h)
{
	_matrix = new long double*[h];
	for(size_t i=0; i<h; ++i)
	{
		_matrix[i] = new long double[w];
		memset(_matrix[i],0,sizeof(_matrix[i]));
	}
}

matrix_float64::~matrix_float64()
{
	for (size_t i=0; i<_height; i++)
	{
   		delete[] _matrix[i];
	}
	delete[] _matrix;
}
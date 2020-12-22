#ifndef CYFRE_H
#define	CYFRE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace cyfre
{
	typedef long long int i64;
	typedef double fltpnt;

	i64 dot_product_i64(vector<i64> a, vector<i64> b);

	class matrix_int64
	{
	public:
		vector<i64> _matrix;
		size_t width;
		size_t height;

		// constructors
		matrix_int64(size_t w); // N x N
		matrix_int64(size_t width, size_t height); // N x M
		matrix_int64(vector<i64> _matrix); // vector input, matrix as height of 1 or 1 row only
		matrix_int64(size_t swidth, vector<i64> _matrix); // N x N and vector input,
		matrix_int64(size_t width, size_t height, vector<i64> _matrix); // N x M and vector input
		matrix_int64(vector<vector<i64>> array2d); // 2d vector input
		
		// add 2d array constructor

		// add type constructor
		/*
		    Square Matrix
		    Symmetric Matrix
		    Triangular Matrix
		    Diagonal Matrix
		    Identity Matrix
		    Orthogonal Matrix
		*/

		// operators
		matrix_int64 scalar(i64 multiplyier) const;

		matrix_int64 operator+(const matrix_int64& rmat) const;
		matrix_int64 operator-(const matrix_int64& rmat) const;
		matrix_int64 operator*(const matrix_int64& rmat) const;

		i64& operator()(size_t i, size_t j);
		i64 operator()(size_t i, size_t j) const;

		// row and columns
		vector<i64> row(size_t i) const;
		vector<i64> col(size_t i) const;

		// displays
		void status(string name) const;
		void view() const;
		size_t area() const;
	};
}
#endif
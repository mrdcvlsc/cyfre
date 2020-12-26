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

	class matrix_int64
	{
	public:
		vector<i64> _matrix;
		size_t width;
		size_t height;

		/** constructors : START **/

		// zero fill
		matrix_int64(size_t w); // N x N
		matrix_int64(size_t width, size_t height); // N x M
		
		// value set fill
		matrix_int64(size_t w, string type, i64 values); // fill or scalar/identity creation
		matrix_int64(size_t w, string type, vector<i64> diagonal_values); // diagonal matrix
		matrix_int64(size_t width, size_t height,  i64 values); // N x M

		// exact values
		matrix_int64(vector<i64> _matrix); // vector input, matrix as height of 1 or 1 row only
		matrix_int64(size_t swidth, vector<i64> _matrix); // N x N and vector input
		matrix_int64(size_t width, size_t height, vector<i64> _matrix); // N x M and vector input
		matrix_int64(vector<vector<i64>> array2d); // 2d vector input

		/** constructors : END  **/

		// add type constructor
		/*
		    Square Matrix
		    Symmetric Matrix
		    Triangular Matrix
		    Diagonal Matrix
		    Identity Matrix
		    Orthogonal Matrix
		*/

		// arithmetic operators
		matrix_int64 operator+(const matrix_int64& rmat) const;
		matrix_int64 operator-(const matrix_int64& rmat) const;
		matrix_int64 operator*(const matrix_int64& rmat) const;

		// indexing operator
		i64& operator()(size_t i, size_t j);
		i64 operator()(size_t i, size_t j) const;

		// row and columns
		vector<i64> row(size_t i) const;
		vector<i64> col(size_t i) const;

		// displays
		void status(string name) const;
		void view() const;

		// scalar operations
		matrix_int64 scale_mul(i64 scalar) const;
		matrix_int64 scale_add(i64 scalar) const;
		matrix_int64 scale_sub(i64 scalar) const;
		matrix_int64 scale_div(i64 scalar) const;

		// maths
		i64 trace() const;
		matrix_int64 transpose() const;
		i64 sum() const;
		size_t area() const;

		// complex algorithms
		i64 det() const;
		
		
	};

	// outer functions functions
	i64 dot_product_i64(vector<i64> a, vector<i64> b);
	matrix_int64 hadamard(matrix_int64 a, matrix_int64 b);

}
#endif
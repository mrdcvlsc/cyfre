#ifndef CYFRE_H
#define	CYFRE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace cyfre
{
	template<typename T>
	void array_view(T arr){
		for(auto e: arr)
			cout<<e<<' ';
		cout<<'\n';
	}

	class matrix_int32
	{
	public:
		vector<long long int> _matrix;
		size_t width;
		size_t height;

		matrix_int32(size_t w);
		matrix_int32(size_t width, size_t height);
		matrix_int32(vector<long long int> _matrix);
		matrix_int32(size_t swidth, vector<long long int> _matrix);
		matrix_int32(size_t width, size_t height, vector<long long int> _matrix);
		
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

		long long int& operator()(size_t i, size_t j);

		vector<long long int> row(size_t i);
		vector<long long int> col(size_t i);
	};
}
#endif
#include "cyfre.h"

namespace cyfre
{

	vector<long long int> matrix_int32::row(size_t i)
	{
		if(i>height-1)
		{
			cerr<<"index row "<<i<<" out of bound, range is only between 0-"<<height-1<<'\n';
			exit(1);
		}
		return {_matrix.begin()+(i*width), _matrix.begin()+(i*width)+width};
	}

}
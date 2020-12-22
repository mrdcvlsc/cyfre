#include "cyfre.h"

namespace cyfre
{

	vector<i64> matrix_int64::row(size_t i) const
	{
		if(i>height-1)
		{
			cerr<<"index row "<<i<<" out of bound, range is only between 0-"<<height-1<<'\n';
			exit(1);
		}
		return {_matrix.begin()+(i*width), _matrix.begin()+(i*width)+width};
	}

}
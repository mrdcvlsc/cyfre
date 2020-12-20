#include "cyfre.h"

namespace cyfre
{
	vector<long long int> matrix_int32::col(size_t i) const
	{
		if(i>width-1){
			cerr<<"index column "<<i<<" out of bound, range is only between 0-"<<width-1<<'\n';
			exit(1);
		}
		vector<long long int> column;
		for(size_t ix = 0, columnJump = width; ix < height; ++ix)
		{
			column.push_back(_matrix[i+(columnJump*ix)]);
		}
		return column;
	}
}
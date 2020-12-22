#include "cyfre.h"

namespace cyfre
{
	i64& matrix_int64::operator()(size_t i, size_t j){
		return  _matrix[(i*width)+j];
	}

	i64 matrix_int64::operator()(size_t i, size_t j) const{
		return  _matrix[(i*width)+j];
	}
}
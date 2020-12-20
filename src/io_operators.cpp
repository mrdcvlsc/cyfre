#include "cyfre.h"

namespace cyfre
{
	long long int& matrix_int32::operator()(size_t i, size_t j){
		return  _matrix[(i*width)+j];
	}
}
#include "cyfre.h"
namespace cyfre
{

	// LUdecomposition
    i64 matrix_int64::det() const
    {
        matrix_int64 a=*this;
		matrix_int64 l=a, u=a;
		i64 i=0, j=0, k=0, n=a.height;
		for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				if(j<i)
					l(j,i) = 0;
				else{
					l(j,i) = a(j,i);
					for (k=0; k<i; k++) {
						l(j,i) = l(j,i) - l(j,k) * u(k,i);
					}
				}
			}
			for(j=0; j<n; j++) {
				if(j<i)
					u(i,j) = 0;
				else if(j==i)
					u(i,j) = 1;
				else{
					u(i,j) = a(i,j) / l(i,i);
					for (k = 0; k < i; k++) {
						u(i,j) = u(i,j) - ((l(i,k) * u(k,j)) / l(i,i));
					}
				}
			}
		}

		i64 det1u = 1, det2l = 1;
		for(i64 i = 0; i < n; ++i){
				det1u *= u(i,i);
				det2l *= l(i,i);
		}
		return det1u*det2l;
	}
}
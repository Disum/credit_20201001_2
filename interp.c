#include "interp.h"

double interp(int n, double x0, double *x, double *y)
{
	int i, j;
	double res = y[0];

	for( i = 0; i<(n - 1); i++ )
	{
		for( j = 0; j<(n - i - 1); j++ )
			y[j] = (x0 - x[i])*( y[j + 1] - y[j] )/( x[j + i + 1] - x[j] );

		res += y[0];
	}

	return res;
}

#include <math.h>
#include "f_integral.h"

static int count = 0;

int get_count_f_integral(void)
{
	return count;
}

int f_integral(double x, double t, double u, double *res)
{
	double val = x*t + 1/(1 + u*u*t*t);

	++count;

	if( val<0 )
		return F_INTEGRAL_ERR;

	*res = sqrt(val);
	return F_INTEGRAL_SUCCESS;
}

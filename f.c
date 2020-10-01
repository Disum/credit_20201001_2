#include <math.h>
#include "f.h"
#include "integrate.h"
#include "f_integral.h"

static int count = 0;

int f(double x, double eps, double *r)
{
	double integral;

	count++;

	if( integrate1(x, eps, &integral)==INTEGRATE_ERR )
		return F_ERR;

	*r =  integral - (x - 1)*(x - 1) + ((double)1)/2;
	return F_SUCCESS;
}

int get_count_f(void)
{
	return count;
}

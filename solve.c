#include <math.h>
#include "solve.h"
#include "interp.h"
#include "heapsort.h"
#include "f.h"
int p(double a, double b);
#define MAX_IT 1e16

int p(double a, double b)
{
	if( fabs(a)>fabs(b) )
		return 1;

	if( fabs(a)<fabs(b) )
		return -1;

	return 0;
}

int solve(int (*f)(double, double, double *), double a, double b, double eps, double *res)
{
	int it, i, j;
	double x_new, y_new, x[3], y[3], x_tmp[3], f_val;

	x[0] = a;
	x[1] = (a + b)/2;
	x[2] = b;
	for( i = 0; i<3; i++ )
	{
		if( f(x[i], eps, &f_val)!=F_SUCCESS )
			return SOLVE_NOT_FOUND;
		y[i] = f_val;
	}

	for( i = 0; i<3; i++ )
	{
		if( fabs(y[i])<eps )
		{
			*res = x[i];
			return 0;
		}
	}

	for( i = 0; i<3; i++ )
		for( j = i + 1; j<3; j++ )
			if( y[i]<=y[j] && y[i]>=y[j] )
				return SOLVE_NOT_FOUND;

	heapsort(x, y, 3, &p);

	for( it = 1; it<MAX_IT; it++ )
	{
		for( i = 0; i<3; i++ )
			x_tmp[i] = x[i];

		x_new = interp(3, 0, y, x_tmp);
		if( f(x_new, eps, &f_val)!=F_SUCCESS )
			return SOLVE_NOT_FOUND;
		y_new = f_val;

		if( fabs(y_new)<eps )
		{
			*res = x_new;
			return it;
		}

		for( i = 0; i<3; i++ )
		{
			if( (y_new<=y[i]) && (y_new>=y[i]) )
				return SOLVE_NOT_FOUND;
		}

		for( i = 2; i>=0; i-- )
		{
			if( fabs(y_new)>=fabs(y[i]) )
			{
				for( j = 2; j>(i + 1); j-- )
				{
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}

				x[i + 1] = x_new;
				y[i + 1] = y_new;

				break;
			}
		}
		if( i==-1 )
		{
			for( j = 2; j>0; j-- )
			{
				x[j] = x[j - 1];
				y[j] = y[j - 1];
			}

			x[0] = x_new;
			y[0] = y_new;
		}
	}

	return SOLVE_NOT_FOUND;
}

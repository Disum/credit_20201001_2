#include <math.h>
#include "integrate.h"
#include "f_integral.h"
#define N 1e7

// Интеграл по du
int integrate1(double x, double eps, double *r)
{
	int n, i;
	double a = 0, b = x, h = b - a, simp1, simp2, fa, fb, f, sum1, sum2;

	if( integrate2(x, a, eps, &fa)==INTEGRATE_ERR )
		return INTEGRATE_ERR;
	if( integrate2(x, b, eps, &fb)==INTEGRATE_ERR )
		return INTEGRATE_ERR;

	sum1 = 0;
	if( integrate2(x, a + h, eps, &f)==INTEGRATE_ERR )
		return INTEGRATE_ERR;
	simp1 = h*fa/3 + 4*h*f/3 + h*fb/3;
	h /= 2;
	for( n = 1; n<N; n *= 2 )
	{
		for( i = 0, sum2 = 0; i<n; i++ )
		{
			if( integrate2(x, a + 2*i*h + h, eps, &f)==INTEGRATE_ERR )
				return INTEGRATE_ERR;
			sum2 += f;
		}
		sum2 *= h;
		simp2 = h*fa/3 + 2*sum1/3 + 4*sum2/3 + h*fb/3;

		if( fabs(simp2 - simp1)<eps )
		{
			*r = simp2;
			return n;
		}

		sum1 = (sum1 + sum2)/2;
		simp1 = simp2;
		h /= 2;
	}

	return INTEGRATE_ERR;
}

// Интеграл по dt
int integrate2(double x, double u, double eps, double *r)
{
	int n, i;
	double a = 0, b = 1, h = b - a, simp1, simp2, fa, fb, f, sum1, sum2;

	if( f_integral(x, a, u, &fa)!=F_INTEGRAL_SUCCESS )
		return INTEGRATE_ERR;
	if( f_integral(x, b, u, &fb)!=F_INTEGRAL_SUCCESS )
		return INTEGRATE_ERR;

	sum1 = 0;
	if( f_integral(x, a + h, u, &f)!=F_INTEGRAL_SUCCESS )
		return INTEGRATE_ERR;
	simp1 = h*fa/3 + 4*h*f/3 + h*fb/3;
	h /= 2;
	for( n = 1; n<N; n *= 2 )
	{
		for( i = 0, sum2 = 0; i<n; i++ )
		{
			if( f_integral(x, a + 2*i*h + h, u, &f)!=F_INTEGRAL_SUCCESS )
				return INTEGRATE_ERR;
			sum2 += f;
		}
		sum2 *= h;
		simp2 = h*fa/3 + 2*sum1/3 + 4*sum2/3 + h*fb/3;

		if( fabs(simp2 - simp1)<eps )
		{
			*r = simp2;
			return n;
		}

		sum1 = (sum1 + sum2)/2;
		simp1 = simp2;
		h /= 2;
	}

	return INTEGRATE_ERR;
}

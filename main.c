#include <stdio.h>
#include <time.h>
#include <math.h>
#include "solve.h"
#include "f.h"
#define ERROR_READ (-1)
#define ERROR_CALCULATE (-2)
#define BEGIN 0
#define END 5
#define NUM (1e2)

int main(int argc, char **argv)
{
	double a = BEGIN, h = ((double)(END - BEGIN))/NUM, eps, x, b = a + h, f_a, f_b, f_val;
	int it;
	clock_t time_beg;

	if( argc!=2 )
	{
		fprintf(stderr, "Error! Usage: %s eps\n", argv[0]);
		return ERROR_READ;
	}
	if( sscanf(argv[1], "%lf", &eps)!=1 || eps<=0 )
	{
		fprintf(stderr, "Error! Can not read eps>0!\n");
		return ERROR_READ;
	}

	time_beg = clock();
	if( f(a, eps, &f_a)!=F_SUCCESS )
	{
		fprintf(stderr, "Error calculate in x = %.16e\n", a);
		return ERROR_CALCULATE;
	}
	if( f(b, eps, &f_b)!=F_SUCCESS )
	{
		fprintf(stderr, "Error calculate in x = %.16e\n", b);
		return ERROR_CALCULATE;
	}
	for( ; b<END; a += h, b += h )
	{
		if( f_a*f_b<=0 )
		{
			it = solve(&f, a, b, eps, &x);
			if( it!=SOLVE_NOT_FOUND )
				if( f(x, eps, &f_val)==F_SUCCESS )
					printf("x = %.16e\t|f(x)| = %.16e\tit = %d\n", x, fabs(f_val), it);
		}

		f_a = f_b;
		if( f(b, eps, &f_b)!=F_SUCCESS )
		{
			fprintf(stderr, "Error calculate in x = %.16e\n", b);
			return ERROR_CALCULATE;
		}
	}
	printf("Time: %.2lf seconds\n", (double)(clock() - time_beg)/CLOCKS_PER_SEC);

	return 0;
}

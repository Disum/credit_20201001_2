#ifndef F_H
#define F_H

enum F_CODES {
	F_ERR,
	F_SUCCESS
};

int f(double x, double eps, double *r);
int get_count_f(void);

#endif

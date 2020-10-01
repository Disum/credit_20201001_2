#ifndef SOLVE_H
#define SOLVE_H

#define SOLVE_NOT_FOUND (-1)

int solve(int (*f)(double, double, double *), double a, double b, double eps, double *res);

#endif

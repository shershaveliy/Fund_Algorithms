#ifndef FUNCTION_H
#define FUNCTION_H


double compute_trapezoid(double start, double end, int segments, double (*func)(double));

double compute_integral(double start, double end, double eps, double (*func)(double));

double function_a(double x);

double integral_a(double eps);

double function_b(double x);

double integral_b(double eps);

double function_c(double x);

double integral_c(double eps);

double function_d(double x);

double integral_d(double eps);

#endif
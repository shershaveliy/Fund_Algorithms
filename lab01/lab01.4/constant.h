#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_ITERATIONS 7000

long long factorial(int n);
long long coefficient_C(int n, int k);
bool findPrime(int limit, int* current_prime);

double e_limit(double epsilon);
double e_series(double epsilon);
double e_equation(double epsilon);

double pi_limit(double epsilon);
double pi_series(double epsilon);
double pi_equation(double epsilon);

double ln2_limit(double epsilon);
double ln2_series(double epsilon);
double ln2_equation(double epsilon);

double sqrt2_limit(double epsilon);
double sqrt2_product(double epsilon);
double sqrt2_equation(double epsilon);

double gamma_limit(double epsilon);
double gamma_series(double epsilon);
double gamma_equation(double epsilon);

#endif
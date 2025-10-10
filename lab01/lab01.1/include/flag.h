#include "status.h"

#ifndef FLAG_H
#define FLAG_H

Status find_multiples(int n, int multiples[], int* count);
Status check_prime(int n, int* is_prime);
Status to_hex(int n, char digits[], int* count);
Status power_table(int n, long long table[10][10], int* rows, int* cols);
Status sum(int n, int* result);
Status factorial(int n, long long* result);

#endif
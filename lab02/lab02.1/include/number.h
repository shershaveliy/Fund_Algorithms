#ifndef NUMBER_H
#define NUMBER_H

#include "status.h"
#include <stdbool.h>

Status check_all(bool** results, int base, int count, ...);
static Status check_one(bool* result, int base, double number);
static long long find_gcd(long long a, long long b);

#endif
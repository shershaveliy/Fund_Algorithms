#include <stdio.h>
#include "../include/flag.h"
#include "../include/status.h"

Status find_multiples(int n, int multiples[], int* count) {
    if (n < 0) {
        return NEGATIVE_NUMBER;
    }
    
    if (n == 0) {
        return DIVISION_BY_ZERO;
    }
    
    if (n > 100) {
        return NUMBER_TOO_LARGE_FOR_MULTIPLES;
    }
    
    int cnt = 0;
    int i = n;
    while (i <= 100) {
        multiples[cnt++] = i;
        i += n;
    }
    *count = cnt;
    
    return OK;
}

Status check_prime(int n, int* is_prime) {
    if (n < 0) {
        return NEGATIVE_NUMBER;
    }
    
    if (n < 2) {
        *is_prime = -1;
    }
    else if (n == 2) {
        *is_prime = 1;
    }
    else if (n % 2 == 0) {
        *is_prime = 0;
    }
    else {
        int prime = 1;
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                prime = 0;
                break;
            }
        }
        *is_prime = prime;
    }
    
    return OK;
}

Status to_hex(int n, char digits[], int* count) {
    if (n == 0) {
        digits[0] = '0';
        *count = 1;
        return OK;
    } 
    
    unsigned int temp;
    if (n < 0) {
        temp = (unsigned int)n;
    }
    else {
        temp = n;
    }
    
    char temp_digits[20];
    int cnt = 0;
    
    while (temp > 0) {
        int digit = temp % 16;
        temp_digits[cnt] = (digit < 10) ? '0' + digit : 'A' + digit - 10;
        temp /= 16;
        cnt++;
    }
    
    for (int i = 0; i < cnt; i++) {
        digits[i] = temp_digits[cnt - 1 - i];
    }
    *count = cnt;
    
    return OK;
}

Status power_table(int n, long long table[10][10], int* rows, int* cols) {
    if (n < 0) {
        return NEGATIVE_NUMBER;
    }
    
    if (n > 10) {
        return NUMBER_TOO_LARGE_FOR_POWERS;
    }
    
    *rows = 10;
    *cols = n;
    
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= n; j++) {
            long long ln = 1;
            for (int m = 1; m <= j; m++) {
                ln *= i;
            }
            table[i-1][j-1] = ln;
        }
    }
    
    return OK;
}

Status sum(int n, int* result) {
    if (n >= 0) {
        *result = n * (n + 1) / 2;
    } else {
        int abs_n = -n;
        *result = 1 - (abs_n * (abs_n + 1) / 2);
    }
    return OK;
}

Status factorial(int n, long long* result) {
    if (n < 0) {
        return NEGATIVE_NUMBER;
    }
    
    if (n > 20) {
        return NUMBER_TOO_LARGE_FOR_FACTORIAL;
    }
    
    if (n == 0) {
        *result = 1;
    }
    else {
        long long fact = 1;
        for (int i = 1; i <= n; i++) {
            fact *= i;
        }
        *result = fact;
    }
    
    return OK;
}
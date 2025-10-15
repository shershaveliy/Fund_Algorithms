#include "../include/number.h"
#include "../include/status.h"
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

static long long find_gcd(long long a, long long b){
    while(b != 0){
        long long temp = b; //Алгоритм Евклида тут
        b = a % b;
        a = temp;
    }
    return a;
}

static Status check_one(bool* result, int base, double number){
    const long long scale = 1000000000000LL;

    if(base < 2) return ERROR_INVALID_BASE;

    if(number <= 1 / scale || number >= 1 - 1 / scale) return ERROR_INVALID_NUMBER;

    // Дробь в деление целых
    long long numerator = llround(number * scale);
    long long denominator = scale;

    // Сокращаем
    long long divisor = find_gcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;

    long long temp = denominator;
    while (temp > 1){
        long long common = find_gcd(temp, base);
        if (common == 1) break;
        temp /= common;
    }

    *result = (temp == 1);
    return OK;
}

Status check_all(bool** results, int base, int count, ...){

    *results = (bool *)malloc(count * sizeof(bool));

    if(*results == NULL) return ERROR_MEMORY;

    va_list args;
    va_start(args, count);//Инициализация

    for(int i = 0; i < count; i++){
        double number = va_arg(args, double);
        Status status = check_one(&(*results)[i], base, number);

        if(status != OK){
            va_end(args);
            free(*results);
            *results = NULL;
            return status;
        }
    }

    va_end(args);
    return OK;
}

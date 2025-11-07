#include "../include/number.h"
#include "../include/status.h"
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DENOMINATOR 1e15
#define MIN_EPSILON 1e-15

static long long find_gcd(long long a, long long b){
    while(b != 0){
        long long temp = b; //Алгоритм Евклида тут
        b = a % b;
        a = temp;
    }
    return a;
}

long long inint(double number, long long *denominator) {
    while (*denominator <= MAX_DENOMINATOR / 10 && fabs(number - round(number)) >= MIN_EPSILON) {
        number *= 10;
        (*denominator) *= 10;
    }
    return llround(number);
}



static Status check_one(bool* result, int base, double number){
    const long long scale = 1000000000000;

    if(base < 2) return ERROR_INVALID_BASE;

    if(number <= 1 / scale || number >= 1 - 1 / scale) return ERROR_INVALID_NUMBER;
    
    //Википедия: Обыкновенная дробь a/b (где a и b — целые, b ≠ 0) имеет конечное представление 
    // в системе счисления с основанием N тогда и только тогда, когда знаменатель b 
    // (после сокращения дроби) не имеет простых делителей, кроме тех, которые входят 
    //в разложение основания N на простые множители.

    // Дробь в деление целых
    long long denominator = 1;
    long long numerator = inint(number, &denominator);

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

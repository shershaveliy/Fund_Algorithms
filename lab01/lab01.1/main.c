#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "include/flag.h"
#include "include/status.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        print_status(INVALID_ARGS_COUNT);
        return 1;
    }

    char* number = argv[1];
    char* flag = argv[2];

    if (flag[0] != '-' && flag[0] != '/') {
        print_status(INVALID_FLAG_FORMAT);
        return 1;
    }

    char* endptr;
    errno = 0;
    long num = strtol(number, &endptr, 10);
    
    if (errno != 0 || endptr == number || *endptr != '\0') {
        print_status(INVALID_NUMBER);
        return 1;
    }
    
    if (num < INT_MIN || num > INT_MAX) {
        print_status(INVALID_NUMBER);
        return 1;
    }
    
    int n = (int)num;

    char flag_type = flag[1];
    
    switch(flag_type) {
        case 'h': {
            printf("Поиск кратных чисел для %d до 100.\n", n);
            int multiples[100];
            int count;
            Status status = find_multiples(n, multiples, &count);
            if (status != OK) {
                print_status(status);
            } else if (count == 0) {
                printf("Нет чисел меньше 100, кратных введенному числу\n");
            } else {
                for (int i = 0; i < count; i++) {
                    printf("%d ", multiples[i]);
                }
                printf("\n");
            }
            break;
        }
        case 'p': {
            printf("Проверка, является ли %d простым числом.\n", n);
            int is_prime;
            Status status = check_prime(n, &is_prime);
            if (status != OK) {
                print_status(status);
            } else {
                if (is_prime == -1) {
                    printf("Не простое и не составное\n");
                } else if (is_prime == 1) {
                    printf("Простое\n");
                } else {
                    printf("Составное\n");
                }
            }
            break;
        }
        case 's': {
            printf("Преобразование %d в шестнадцатеричные цифры.\n", n);
            char digits[20];
            int count;
            Status status = to_hex(n, digits, &count);
            if (status != OK) {
                print_status(status);
            } else {
                for (int i = 0; i < count; i++) {
                    printf("%c", digits[i]);
                    if (i < count - 1) printf(" ");
                }
                printf("\n");
            }
            break;
        }
        case 'e': {
            printf("Таблица степеней для оснований 1-10, показателей 1-%d.\n", n);
            long long table[10][10];
            int rows, cols;
            Status status = power_table(n, table, &rows, &cols);
            if (status != OK) {
                print_status(status);
            } else {
                for (int i = 0; i < rows; i++) {
                    printf("%2d:", i + 1);
                    for (int j = 0; j < cols; j++) {
                        printf("%12lld", table[i][j]);
                    }
                    printf("\n");
                }
            }
            break;
        }
        case 'a': {
            printf("Вычисление суммы чисел от 1 до %d.\n", n);
            int result;
            Status status = sum(n, &result);
            if (status != OK) {
                print_status(status);
            } else {
                printf("%d\n", result);
            }
            break;
        }
        case 'f': {
            printf("Вычисление факториала числа %d.\n", n);
            long long result;
            Status status = factorial(n, &result);
            if (status != OK) {
                print_status(status);
            } else {
                printf("%lld\n", result);
            }
            break;
        }
        default:
            print_status(UNKNOWN_FLAG);
            return 1;
    }

    return 0;
}
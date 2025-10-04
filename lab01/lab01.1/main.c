#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flag.h"

int main(int argc, char* argv[]){
    if(argc < 3) {
        printf("Неверный ввод. Введите число и флаг\n");
        return 1;
    }

    char* number = argv[1];
    char* flag = argv[2];

    if(flag[0] != '-' && flag[0] != '/') {
        printf("Ошибка: флаг должен начинаться с '-' или '/'\n");
        return 1;
    }

    if(atoi(number) < 0){
        printf("Программа принимает только неотрицательные числа\n");
        return 1;
    }

    int n = atoi(number);
    
    char flag_type = flag[1];
    
    switch(flag_type) {
        case 'h':
            find_multiples(n);
            break;
        case 'p':
            check_prime(n);
            break;
        case 's':
            to_hex(n);
            break;
        case 'e':
            power_table(n);
            break;
        case 'a':
            sum(n);
            break;
        case 'f':
            factorial(n);
            break;
        default:
            printf("Неизвестный флаг: %s\n", flag);
            return 1;
    }

    return 0;
}
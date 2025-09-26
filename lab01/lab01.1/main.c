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

    if(argv[1] < 0){
        printf("Программа принимает только неотрицательные числа\n");
        return 1;
    }

    int n = atoi(number);
    

    if (strcmp(flag, "-h") == 0){
        find_multiples(n);
    }
    else if(strcmp(flag, "-p") == 0){
        check_prime(n);
    }
    else if(strcmp(flag, "-s") == 0){
        to_hex(n);
    }
    else if(strcmp(flag, "-e") == 0){
        power_table(n);
    }
    else if(strcmp(flag, "-a") == 0){
        sum(n);
    }
    else if(strcmp(flag, "-f") == 0){
        factorial(n);
    }
    else {
        printf("Неизвестный флаг: %s\n", flag);
        return 1;
    }

    return 0;
}
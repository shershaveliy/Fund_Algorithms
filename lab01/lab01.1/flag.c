#include <stdio.h>
#include "flag.h"

void find_multiples(int n) {
    printf("Поиск кратных чисел для %d до 100.\n", n);
    if(n == 0){
        printf("Нелязя делить на ноль\n");
    }
    else if(n > 100){
        printf("Нет чисел меньше 100, кратных введенному числу\n");
    }
    else{
        int i = n;
        while(i <= 100){
            printf("%d ", i);
            i += n;
        }
        printf("\n");
    }
}

void check_prime(int n) {
    printf("Проверка, является ли %d простым числом.\n", n);
    if(n < 2) {
        printf("Не простое и не составное\n");
    }
    else if(n == 2) {
        printf("Простое\n");
    }
    else if(n % 2 == 0){
        printf("Составное\n");
    }
    else{
        int is_prime = 1;
        for(int i = 3; i * i <= n; i += 2){
            if(n % i == 0){
                is_prime = 0;
                break;
            }
        }
        printf("%s\n", is_prime ? "Простое" : "Составное");
    }
}

void to_hex(int n) {
    printf("Преобразование %d в шестнадцатеричные цифры.\n", n);
    if (n == 0) {
        printf("0");
    } 
    else {
        int temp = n;
        char digits[20];
        int count = 0;
        
        while (temp > 0) {
            int digit = temp % 16;
            digits[count] = (digit < 10) ? '0' + digit : 'A' + digit - 10;
            temp /= 16;
            count++;
        }
        
        for (int i = count - 1; i >= 0; i--) {
            printf("%c", digits[i]);
            if (i > 0) printf(" ");
        }
    }
    printf("\n");
}

void power_table(int n) {
    printf("Таблица степеней для оснований 1-10, показателей 1-%d.\n", n);
    if(n > 10) {
        printf("Число для этого флага должно быть не больше 10\n");
    }
    else{
        for(int i = 1; i <= 10; i++){
            printf("%2d:", i);
            for(int j = 1; j <= n; j++){
                long long ln = 1;
                for(int m = 1; m <= j; m++){
                    ln *= i;
                }
                printf("%12lld", ln);
            }
            printf("\n");   
        }
    }
}

void sum(int n) {
    printf("Вычисление суммы чисел от 1 до %d.\n", n);
    int result = n * (n + 1) / 2;
    printf("%d\n", result);
}

void factorial(int n) {
    printf("Вычисление факториала числа %d.\n", n);
    if(n < 0  || n > 20) {
        printf("Нет факториала отрицательного числа или число слишком большое\n");
    }
    else if(n == 0) {
        printf("1\n");
    }
    else{
        long long result = 1;
        for(int i = 1; i <= n; i++){
            result *= i;
        }
        printf("%lld\n", result);
    }
}
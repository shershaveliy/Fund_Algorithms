#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Использование: %s <точность>\n", argv[0]);
        printf("Пример: %s 0.0001\n", argv[0]);
        return 1;
    }
    
    double eps = atof(argv[1]);

    
    if (eps <= 0) {
        printf("Ошибка: точность должна быть положительным числом\n");
        return 2;
    }
    
    printf("Вычисление интегралов с точностью %g\n\n", eps);
    
    printf("a) %.8f\n", integral_a(eps));
    printf("b) %.8f\n", integral_b(eps));
    printf("c) %.8f\n", integral_c(eps));
    printf("d) %.8f\n", integral_d(eps));
    
    return 0;
}
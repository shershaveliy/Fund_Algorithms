#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/status.h"
#include "include/function.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        print_status(INVALID_ARGS_COUNT);
        return 1;
    }
    
    char* endptr;
    errno = 0;
    double epsilon = strtod(argv[1], &endptr);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || epsilon < 0) {
        print_status(INVALID_NUMBER);
        return 1;
    }
    if(epsilon != 0 && fabs(epsilon) < 1e-19){
        print_status(INVALID_NUMBER_DOUBLE);
        return 1;
    }
    
    printf("Вычисление интегралов с точностью %s\n\n", argv[1]);
    
    printf("a) %.20f\n", integral_a(epsilon));
    printf("b) %.20f\n", integral_b(epsilon));
    printf("c) %.20f\n", integral_c(epsilon));
    printf("d) %.20f\n", integral_d(epsilon));
    
    return 0;
}
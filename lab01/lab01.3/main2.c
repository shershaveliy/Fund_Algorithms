#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include "include/status.h"
#include "include/operations.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        print_status(INVALID_ARGS_COUNT);
        return 1;
    }

    char* flag = argv[1];

    if (flag[0] != '-' && flag[0] != '/') {
        print_status(INVALID_FLAG_FORMAT);
        return 1;
    }
    
    switch (flag[1]) {
        case 'q': {
            if (argc != 6) {
                print_status(INVALID_ARGS_COUNT);
                return 1;
            }
            
            char* endptr;
            errno = 0;
            double epsilon = strtod(argv[2], &endptr);
            if (errno != 0 || endptr == argv[2] || *endptr != '\0' || epsilon < 0) {
                print_status(INVALID_NUMBER);
                return 1;
            }
            if(epsilon != 0 && fabs(epsilon) < 1e-19){
                print_status(INVALID_NUMBER_DOUBLE);
                return 1;
            }

            
            double coefficients[3];
            for (int i = 0; i < 3; i++) {
                errno = 0;
                coefficients[i] = strtod(argv[3 + i], &endptr);
                if (errno != 0 || endptr == argv[3 + i] || *endptr != '\0') {
                    print_status(INVALID_NUMBER);
                    return 1;
                }
                if (coefficients[i] != 0 && fabs(coefficients[i]) < 1e-19) { 
                    print_status(INVALID_NUMBER_DOUBLE);
                    return 1;
                }
            }
            
            double a = coefficients[0];
            double b = coefficients[1];
            double c = coefficients[2];

            quadro(a, b, c, epsilon);
            


            break;
        }
            
        case 'm': {
            if (argc != 4) {
                print_status(INVALID_ARGS_COUNT);
                return 1;
            }
            
            // Парсинг чисел
            char* endptr;
            int numbers[2];
            for (int i = 0; i < 2; i++) {
                errno = 0;
                long num = strtol(argv[2 + i], &endptr, 10);
                if (errno != 0 || endptr == argv[2 + i] || *endptr != '\0' || 
                    num < INT_MIN || num > INT_MAX || num <= 0) {
                    print_status(INVALID_NUMBER);
                    return 1;
                }
                numbers[i] = (int)num;
            }
            
            bool is_multiple = check_multiple(numbers[0], numbers[1]);
            
            if (is_multiple) {
                printf("Число %d кратно %d\n", numbers[0], numbers[1]);
            } else {
                printf("Число %d не кратно %d\n", numbers[0], numbers[1]);
            }
            break;
        }
            
        case 't': {
            if (argc != 6) {
                print_status(INVALID_ARGS_COUNT);
                return 1;
            }
            
            char* endptr;
            errno = 0;
            double epsilon = strtod(argv[2], &endptr);
            if (errno != 0 || endptr == argv[2] || *endptr != '\0' || epsilon < 0) {
                print_status(INVALID_NUMBER);
                return 1;
            }
            if (epsilon != 0 && fabs(epsilon) < 1e-19) {
                    print_status(INVALID_NUMBER_DOUBLE);
                    return 1;
                }
            
            // Парсинг сторон
            double sides[3];
            for (int i = 0; i < 3; i++) {
                errno = 0;
                sides[i] = strtod(argv[3 + i], &endptr);
                if (errno != 0 || endptr == argv[3 + i] || *endptr != '\0') {
                    print_status(INVALID_NUMBER);
                    return 1;
                }
                if (sides[i] != 0 && fabs(sides[i]) < 1e-19) {
                    print_status(INVALID_NUMBER_DOUBLE);
                    return 1;
                }
            }
            
            bool is_right_triangle = triangle(sides[0], sides[1], sides[2], epsilon);
            
            printf("Стороны: %.20f, %.20f, %.20f\n", sides[0], sides[1], sides[2]);
            
            if (is_right_triangle) {
                printf("Числа могут быть длинами сторон прямоугольного треугольника\n");
            } else {
                printf("Числа не могут быть длинами сторон прямоугольного треугольника\n");
            }
            break;
        }
            
        default:
            print_status(UNKNOWN_FLAG);
            return 1;
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../include/operations.h"

bool check_double(double x1, double x2, double epsilon) {
    return fabs(x1 - x2) < epsilon;
}

void quadro_resh(double a, double b, double c, double epsilon){
    if (check_double(a, 0.0, epsilon) && check_double(b, 0.0, epsilon) && check_double(c, 0.0, epsilon)) {
        printf("Решений бесконечно много\n");
        return;
    }

    if (check_double(a, 0.0, epsilon)) {
        if (check_double(b, 0.0, epsilon)) {
            printf("Решений нет\n");
        }
        else {
            double x = -c / b;
            printf("Один корень: x = %.20f\n", x);
        }
        return;
    }

    double D = b * b - 4 * a * c;
    
    if (check_double(D, 0.0, epsilon)){
        double x = -b / (2 * a);
        printf("Один корень: x = %.20f\n", x);
    }
    else if (D < 0) {
        printf("Действительных корней нет\n");
    }
    else {
        double x1 = (-b + sqrt(D)) / (2 * a);
        double x2 = (-b - sqrt(D)) / (2 * a);
        printf("Два корня: x1 = %.20f, x2 = %.20f\n", x1, x2);
    }
}

// Функция для флага -q
void quadro(double a, double b, double c, double epsilon) {


    printf("Эпсилон: %.20f\n", epsilon);
    printf("Коэффициенты: a=%.20f, b=%.20f, c=%.20f\n\n", a, b, c);
    
    int count = 1;
    
    // a, b, c
    printf("Перестановка %d: a=%.20f, b=%.20f, c=%.20f\n", count, a, b, c);
    quadro_resh(a, b, c, epsilon);
    printf("\n");
    
    // a, c, b (если b ≠ c)
    if (!check_double(b, c, epsilon)) {
        count++;
        printf("Перестановка %d: a=%.20f, c=%.20f, b=%.20f\n", count, a, c, b);
        quadro_resh(a, c, b, epsilon);
        printf("\n");
    }
    
    // b, a, c (если a ≠ b)
    if (!check_double(a, b, epsilon)) {
        count++;
        printf("Перестановка %d: b=%.20f, a=%.20f, c=%.20f\n", count, b, a, c);
        quadro_resh(b, a, c, epsilon);
        printf("\n");
        
        // b, c, a (если a ≠ c)
        if (!check_double(a, c, epsilon)) {
            count++;
            printf("Перестановка %d: b=%.20f, c=%.20f, a=%.20f\n", count, b, c, a);
            quadro_resh(b, c, a, epsilon);
            printf("\n");
        }
    }
    
    // c, a, b (если b ≠ c и a ≠ c)
    if (!check_double(b, c, epsilon) && !check_double(a, c, epsilon)) {
        count++;
        printf("Перестановка %d: c=%.20f, a=%.20f, b=%.20f\n", count, c, a, b);
        quadro_resh(c, a, b, epsilon);
        printf("\n");
        
        // c, b, a (если a ≠ b)
        if (!check_double(a, b, epsilon)) {
            count++;
            printf("Перестановка %d: c=%.20f, b=%.20f, a=%.20f\n", count, c, b, a);
            quadro_resh(c, b, a, epsilon);
            printf("\n");
        }
    }
}

bool check_multiple(int num1, int num2) {
    return (num1 % num2 == 0);
}

bool triangle(double a, double b, double c, double epsilon) {
    double sides[3] = {a, b, c};
    
    double max_side = sides[0];
    int max_index = 0;
    
    for (int i = 1; i < 3; i++) {
        if (sides[i] > max_side) {
            max_side = sides[i];
            max_index = i;
        }
    }
    
    double sum_squares = 0.0;
    for (int i = 0; i < 3; i++) {
        if (i != max_index) {
            sum_squares += sides[i] * sides[i];
        }
    }
    
    double hypotenuse_square = max_side * max_side;
    
    // Проверка услови я
    return check_double(sum_squares, hypotenuse_square, epsilon);
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "operations.h"

bool check_double(double x1, double x2, double epsilon) {
    return fabs(x1 - x2) < epsilon;
}

void quadro_resh(double a, double b, double c, double epsilon) {
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
            printf("Один корень: x = %f\n", x);
        }
        return;
    }

    double D = b * b - 4 * a * c;
    
    if (check_double(D, 0.0, epsilon)) {
        double x = -b / (2 * a);
        printf("Один корень: x = %f\n", x);
    }
    else if (D < 0) {
        printf("Действительных корней нет\n");
    }
    else {
        double x1 = (-b + sqrt(D)) / (2 * a);
        double x2 = (-b - sqrt(D)) / (2 * a);
        printf("Два корня: x1 = %f, x2 = %f\n", x1, x2);
    }
}

// Функция для флага -q
void quadro(char *argv[]) {
    double epsilon = atof(argv[2]);
    double a = atof(argv[3]);
    double b = atof(argv[4]);
    double c = atof(argv[5]);

    if (a < 0.0 || b < 0.0 || c < 0.0 ) {
        printf("Ошибка: числа должны быть неотрицательными\n");
        return;
    }
    
    printf("Эпсилон: %f\n", epsilon);
    printf("Коэффициенты: a=%f, b=%f, c=%f\n\n", a, b, c);
    
    int count = 1;
    
    // a, b, c
    printf("Перестановка %d: a=%f, b=%f, c=%f\n", count, a, b, c);
    quadro_resh(a, b, c, epsilon);
    printf("\n");
    
    // a, c, b (если b ≠ c)
    if (!check_double(b, c, epsilon)) {
        count++;
        printf("Перестановка %d: a=%f, c=%f, b=%f\n", count, a, c, b);
        quadro_resh(a, c, b, epsilon);
        printf("\n");
    }
    
    // b, a, c (если a ≠ b)
    if (!check_double(a, b, epsilon)) {
        count++;
        printf("Перестановка %d: b=%f, a=%f, c=%f\n", count, b, a, c);
        quadro_resh(b, a, c, epsilon);
        printf("\n");
        
        // b, c, a (если a ≠ c)
        if (!check_double(a, c, epsilon)) {
            count++;
            printf("Перестановка %d: b=%f, c=%f, a=%f\n", count, b, c, a);
            quadro_resh(b, c, a, epsilon);
            printf("\n");
        }
    }
    
    // c, a, b (если b ≠ c и a ≠ c)
    if (!check_double(b, c, epsilon) && !check_double(a, c, epsilon)) {
        count++;
        printf("Перестановка %d: c=%f, a=%f, b=%f\n", count, c, a, b);
        quadro_resh(c, a, b, epsilon);
        printf("\n");
        
        // c, b, a (если a ≠ b)
        if (!check_double(a, b, epsilon)) {
            count++;
            printf("Перестановка %d: c=%f, b=%f, a=%f\n", count, c, b, a);
            quadro_resh(c, b, a, epsilon);
            printf("\n");
        }
    }
}

void check_multiple(char *argv[]){
    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);
    
    if (num1 <= 0 || num2 <= 0) {
        printf("Ошибка: оба числа должны быть больше 0\n");
        return;
    }


    if (num1 % num2 == 0) {
        printf("Число %d кратно %d\n", num1, num2);
    }
    else {
        printf("Число %d не кратно %d\n", num1, num2);
    }
}

void triangle(char *argv[]){
    double epsilon = atof(argv[2]);
    
    for (int i = 3; i <= 5; i++) {
        if (atof(argv[i]) <= 0) {
            printf("Ошибка: все стороны должны быть положительными\n");
            return;
        }
    }
    
    double sides[3];

    for (int i = 0; i < 3; i++) {
        sides[i] = atof(argv[i + 3]);
    }
    
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
    
    double hypotenuse = max_side * max_side;
    
    printf("Стороны: %f, %f, %f\n", sides[0], sides[1], sides[2]);
    printf("Гипотенуза: %f\n", max_side);
    printf("Сумма квадратов катетов: %f\n", sum_squares);
    printf("Квадрат гипотенузы: %f\n", hypotenuse);
    

    if (check_double(sum_squares, hypotenuse, epsilon)) {
        printf("Числа могут быть длинами сторон прямоугольного треугольника\n");
    }
    else {
        printf("Числа не могут быть длинами сторон прямоугольного треугольника\n");
    }
}
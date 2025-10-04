#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "function.h"

// Вычисление интеграла методом трапеций для заданного числа разбиений
double compute_trapezoid(double start, double end, int segments, double (*func)(double)) {
    double step = (end - start) / segments;
    double total = 0.5 * (func(start) + func(end));

    for (int idx = 1; idx < segments; idx++) {
        total += func(start + idx * step);
    }

    return step * total;
}



// Вычисление интеграла с заданной точностью
double compute_integral(double start, double end, double eps, double (*func)(double)) {
    int segments = 1;
    double previous_value = 0;
    double current_value = compute_trapezoid(start, end, segments, func);
    
    do {
        segments *= 2;
        previous_value = current_value;
        current_value = compute_trapezoid(start, end, segments, func);
    } while (fabs(current_value - previous_value) >= eps);
    
    return current_value;
}

// Функция для интеграла a: ln(1+x)/x
double function_a(double x) {
    if (fabs(x) < 1e-14) {
        return 1.0;
    }
    return log(1.0 + x) / x;
}

// Вычисление интеграла a
double integral_a(double eps) {
    return compute_integral(0.0, 1.0, eps, function_a);
}

// Функция для интеграла b: e^(-x²/2)
double function_b(double x) {
    return exp(-(x * x) / 2.0);
}

// Вычисление интеграла b
double integral_b(double eps) {
    return compute_integral(0.0, 1.0, eps, function_b);
}

// Функция для интеграла c: -ln(1-x)
double function_c(double x) {
    return -log(1.0 - x);
}

// Вычисление интеграла c с обработкой особенности
double integral_c(double eps) {
    double cutoff = 1.0 - eps;
    if (eps > 0.1) {
        cutoff = 0.9;
    }
    double main_part = compute_integral(0.0, cutoff, eps, function_c);
    double remaining = (1.0 - cutoff) * (1.0 - log(1.0 - cutoff));
    return main_part + remaining;
}

// Функция для интеграла d: x^x
double function_d(double x) {
    return pow(x, x);
}

// Вычисление интеграла d
double integral_d(double eps) {
    return compute_integral(0.0, 1.0, eps, function_d);
}

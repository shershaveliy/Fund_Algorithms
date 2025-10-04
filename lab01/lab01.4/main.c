#include "constant.h"

void test(double epsilon) {
    
    printf("Число e:\n");
    printf("  Как предел:        %.10f\n", e_limit(epsilon));
    printf("  Как сумма ряда:    %.10f\n", e_series(epsilon));
    printf("  Из уравнения:      %.10f\n", e_equation(epsilon));
    printf("  Эталонное значение: 2.7182818284\n\n");
    
    printf("Число π:\n");
    printf("  Как предел:        %.10f\n", pi_limit(epsilon));
    printf("  Как сумма ряда:    %.10f\n", pi_series(epsilon));
    printf("  Из уравнения:      %.10f\n", pi_equation(epsilon));
    printf("  Эталонное значение: 3.1415926535\n\n");
    
    printf("Ln2:\n");
    printf("  Как предел:        %.10f\n", ln2_limit(epsilon));
    printf("  Как сумма ряда:    %.10f\n", ln2_series(epsilon));
    printf("  Из уравнения:      %.10f\n", ln2_equation(epsilon));
    printf("  Эталонное значение: 0.6931471805\n\n");
    
    printf("√2:\n");
    printf("  Как предел:        %.10f\n", sqrt2_limit(epsilon));
    printf("  Как произведение:  %.10f\n", sqrt2_product(epsilon));
    printf("  Из уравнения:      %.10f\n", sqrt2_equation(epsilon));
    printf("  Эталонное значение: 1.4142135623\n\n");
    
    printf("Постоянная эйлера:\n");
    printf("  Как предел:        %.10f\n", gamma_limit(epsilon));
    printf("  Как сумма ряда:    %.10f\n", gamma_series(epsilon));
    printf("  Из уравнения:      %.10f\n", gamma_equation(epsilon));
    printf("  Эталонное значение: 0.5772156649\n");
}

int main() {
    double epsilon;
    
    printf("Введите точность вычислений (например, 0.0001): ");
    if (scanf("%lf", &epsilon) != 1) {
        printf("Ошибка ввода! Используется точность по умолчанию: 1e-8\n");
        epsilon = 1e-8;
    }
    
    // Проверка корректности введенной точности
    if (epsilon <= 0) {
        printf("Точность должна быть положительной! Используется значение по умолчанию: 1e-8\n");
        epsilon = 1e-8;
    }
    
    test(epsilon);
    
    return 0;
}
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "constant.h"

#define MAX_ITERATIONS 7000

long long coefficient_C(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    
    // Cимметрия для уменьшения k
    if (k > n - k) {
        k = n - k;
    }
    
    // Вычисляем C(n,k) = n*(n-1)*...*(n-k+1) / k!
    long long result = 1;
    for (int i = 1; i <= k; i++) {
        if (result > LLONG_MAX / (n - i + 1)) {
            printf("Переполнение при вычислении C(%d,%d)\n", n, k);
            return 0;
        }
        result = result * (n - i + 1) / i;
    }
    return result;
}

long long factorial(int n) {
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;
    
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        if (result > LLONG_MAX / i) {
            printf("Переполнение при вычислении %d!\n", n);
            return 0;
        }
        result *= i;
    }
    return result;
}

bool findPrime(int limit, int* current_prime) {
    if (*current_prime < 2 && limit >= 2) {
        *current_prime = 2;
        return true;
    }
    
    int candidate = (*current_prime % 2 == 0) ? *current_prime + 1 : *current_prime + 2;
    
    while (candidate <= limit) {
        if (candidate % 2 == 0) {
            candidate++;
            continue;
        }
        
        bool is_prime = true;
        for (int n = 3; n * n <= candidate; n += 2) {
            if (candidate % n == 0) {
                is_prime = false;
                break;
            }
        }
        
        if (is_prime) {
            *current_prime = candidate;
            return true;
        }
        
        candidate += 2;
    }
    
    return false;
}

// Вычисление e
double e_limit(double epsilon) {
    double previous = 0.0, current = 0.0;
    unsigned long n = 0;
    
    do {
        n++;
        previous = current;
        double base = 1.0 + 1.0 / n;
        current = pow(base, n);
    } while (fabs(current - previous) >= epsilon && n < MAX_ITERATIONS);
    
    return current;
}

double e_series(double epsilon) {
    double sum = 1.0, term = 1.0;
    unsigned long n = 0;
    
    do {
        n++;
        term /= n;
        sum += term;
    } while (fabs(term) >= epsilon && n < MAX_ITERATIONS);//Цикл идет до достижения заданной точности
    
    return sum;
}

double e_equation(double epsilon) {
    // ln(x) = 1
    double l = 2.0, r = 3.0;
    while (r - l > epsilon) {
        double mid = (l + r) / 2;
        if (log(mid) > 1.0) r = mid;
        else l = mid;
    }
    return (l + r) / 2;
}

// вычисление π
double pi_limit(double epsilon) {
    double current = 1.0, previous = 0.0;
    unsigned long n = 0;
    double product = 1.0;
    
    do {
        n++;
        previous = current;
        
        // вычислять рекуррентно чтобы избежать переполнения:
        // term(n) = term(n-1) * (4 * n^2) / ((4 * n^2 - 1)
        
        double term = (4.0 * n * n) / (4.0 * n * n - 1.0);
        product *= term;
        current = 2.0 * product;
        
        n++;
        
        if (!isfinite(current)) {
            printf("Переполнение на шаге n = %lu\n", n);
            return 0;
        }
        
    } while (fabs(current - previous) >= epsilon && n < MAX_ITERATIONS);
    
    return current;
}
/*
double pi_limit(double epsilon) {
    double current = 1.0, previous = 0.0;
    unsigned long n = 0;
    
    do {
        n++;
        previous = current;
        
        double numerator = 16.0 * pow(n, 4); // n-й множитель = [16 × n^4] / [2n × (2n-1)]^2
        double denominator = pow(2 * n * (2 * n - 1), 2);
        current *= numerator / denominator;
    
        if (!isfinite(current)) {
            printf("Переполнение на шаге n = %lu\n", n);
            return 0;
        }
        
    } while (fabs(current - previous) >= epsilon * n && n < MAX_ITERATIONS);
    // Учитываю замедление сходимости O(1/n), чтобы не зацикливаться на микро-изменениях
    return current / n;
} при epsilon например 0.0000001 переполнение но при 0.001 все идеально
*/

double pi_series(double epsilon) {
    double current = 0.0, previous = 0.0;
    unsigned long n = 0;
    
    do {
        n++;
        previous = current;
        
        double sign = (n % 2 == 1) ? 1.0 : -1.0;
        double denominator = 2.0 * n - 1.0;
        current += 4.0 * sign / denominator;
    // Ряд Лейбница: π/4 = 1 - 1/3 + 1/5 - 1/7 + ... поэтому умножаем на 4
    } while (fabs(current - previous) >= epsilon && n < MAX_ITERATIONS);
    
    return current;
}

double pi_equation(double epsilon) {
    // cos(x/2) = 0
    double l = 3.0, r = 3.2;
    while (r - l > epsilon) {
        double mid = (l + r) / 2;
        if (cos(mid/2) > 0) l = mid;
        else r = mid;
    }
    return (l + r) / 2;
}
// вычисление ln2
double ln2_limit(double epsilon) {
    double previous = 0.0, current = 0.0;
    unsigned long n = 0;
    
    do { // n(2^(1/n) - 1) = ln(2)
        n++;
        previous = current;
        double power_term = pow(2.0, 1.0 / n) - 1.0;
        current = n * power_term;
    } while (fabs(current - previous) >= epsilon && n < MAX_ITERATIONS);
    
    return current;
}

double ln2_series(double epsilon) {
    double current = 0.0, previous = 0.0;
    unsigned long n = 0;
    
    do { // ln(1+x) = x - x^2/2 + x^3/3 - ... при x=1 даёт 1 - 1/2 + 1/3 - ... = ln(2)
        n++;
        previous = current;
        
        double sign = (n % 2 == 1) ? 1.0 : -1.0;
        current += sign / n;
        
    } while (fabs(current - previous) >= epsilon && n < MAX_ITERATIONS);
    
    return current;
}

double ln2_equation(double epsilon) {
    // e^x = 2
    double l = 0.0, r = 1.0;
    
    while (r - l > epsilon) {
        double mid = (l + r) / 2;
        double exp_mid = 1.0 + mid;
        double term = mid;
        for (int i = 2; i < 20; i++) {
            term *= mid / i;
            exp_mid += term;
        }
        
        if (exp_mid > 2.0) {
            r = mid;  // Слишком большой x
        } else {
            l = mid;  // Слишком маленький x
        }
    }
    return (l + r) / 2;
}

// вычисление sqrt2
double sqrt2_limit(double epsilon) {
    double previous = 0.0, current = -0.5; // Начальное условие x0 = -0.5
    unsigned long iter = 0;
    
    do {
        iter++;
        previous = current;
        // x(n+1) = x(n) - x(n)^2/2 + 1
        current = previous - (previous * previous) / 2.0 + 1.0;
    } while (fabs(current - previous) >= epsilon && iter < MAX_ITERATIONS);
    
    return current;
}

double sqrt2_product(double epsilon) {
    double current = 1.0, previous = 0.0;
    unsigned long k = 1;
    
    do {
        previous = current;
        // Формула Виета: sqrt2 = 2 / (sqrt(1/2) × sqrt(1/2 + 1/2sqrt(1/2)) × ...)
        double term = 1.0;
        for (unsigned long i = 1; i <= k; i++) {
            term *= 2.0;
            term = sqrt(0.5 + 0.5 * term);
        }
        current = 2.0 / term;
        
        k++;
        
    } while (fabs(current - previous) >= epsilon && k < MAX_ITERATIONS);
    
    return current;
}

double sqrt2_equation(double epsilon) {
    // x^2 = 2
    double l = 1.0, r = 2.0;
    while (r - l > epsilon) {
        double mid = (l + r) / 2;
        if (mid * mid > 2.0) r = mid;
        else l = mid;
    }
    return (l + r) / 2;
}

// вычисление y это (постоянная Эйлера-Маскерони)
double gamma_limit(double epsilon) {
    // Использую метод через гармонические числа
    double previous = 0.0, current = 0.0;
    unsigned long n = 1;
    
    do {
        n++;
        previous = current;
        
        // Вычисляем H_n - ln(n), где H_n - n-е гармоническое число
        double harmonic = 0.0;
        for (unsigned long i = 1; i <= n; i++) {
            harmonic += 1.0 / i;
        }
        current = harmonic - log(n);
        
    } while (fabs(current - previous) >= epsilon && n < MAX_ITERATIONS);
    
    return current;
}

double gamma_series(double epsilon) {

    double pi = pi_equation(epsilon);
    double sum = -pi * pi / 6.0; // Начальное значение: -π^2/6
    double previous = 0.0, before_previous = 0.0;
    unsigned long k = 1;
    
    do {
        k++;
        before_previous = previous;
        previous = sum;
        
        int sqrt_k = (int)sqrt(k);
        double term = 1.0 / (sqrt_k * sqrt_k) - 1.0 / k; // Член ряда: 1/[sqrt(k)]^2 - 1/k
        sum += term;
        
    } while ((fabs(sum - previous) >= epsilon || fabs(previous - before_previous) >= epsilon) && 
             k < MAX_ITERATIONS);
    
    return sum;
}

double gamma_equation(double epsilon) {
    double previous = 0.0, current = 0.0;
    int t = 1;
    double composition_prime = 1.0;
    int last_prime = 1;
    
    do { // y +-= -ln( ln t × П[p <= t] (p-1)/p )
        t++;
        previous = current;
        
        if (findPrime(t, &last_prime)) {
            composition_prime *= (last_prime - 1.0) / last_prime;
        }
        
        current = -log(log(t) * composition_prime);
        
    } while (fabs(current - previous) >= epsilon && t < MAX_ITERATIONS);
    
    return current;
}


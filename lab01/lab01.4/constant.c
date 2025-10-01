#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "constant.h"

#define MAX_ITERATIONS 10000000

long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        if (result > LLONG_MAX / i){
            printf("Переполнение при вычислении %d!\n", n);
            break;
        }
        result *= i;
    }
    return result;
}

long long compositionRange(int start, int end) {
    long long result = 1;
    for (int i = start; i <= end; i++) {
        if (result > LLONG_MAX / i){
            printf("Переполнение в диапазоне от %d до %d\n", start, end);
            break;
        }
        result *= i;
    }
    return result;
}

long long coefficient_C(int n, int k) {
    // C(n,k) = n! / (k! * (n-k)!)
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    
    // Симметрия C(n,k) = C(n,n-k)
    // C(n,k) = [(n-k+1) * ... *(n-1) * n] / [1 * 2 * ... * k]
    if (k > n - k){
        k = n - k;
    }
    
    return compositionRange(n - k + 1, n) / factorial(k);
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

double e_equation() {
    return exp(1.0);
}

// вычисление π
double pi_limit(double epsilon) {
    double current = 1.0, previous = 0.0;
    unsigned long n = 0;
    
    do {
        n++;
        previous = current;
        
        double numerator = 16.0 * pow(n, 4); // n-й множитель = [16 × n⁴] / [2n × (2n-1)]²
        double denominator = pow(2 * n * (2 * n - 1), 2);
        current *= numerator / denominator;
        
    } while (fabs(current - previous) >= epsilon * n && n < MAX_ITERATIONS);
    // Учитываю замедление сходимости O(1/n), чтобы не зацикливаться на микро-изменениях
    return current / n;
}

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

double pi_equation() {
    return acos(-1.0);
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
    
    do { // ln(1+x) = x - x²/2 + x³/3 - ... при x=1 даёт 1 - 1/2 + 1/3 - ... = ln(2)
        n++;
        previous = current;
        
        double sign = (n % 2 == 1) ? 1.0 : -1.0;
        current += sign / n;
        
    } while (fabs(current - previous) >= epsilon && n < MAX_ITERATIONS);
    
    return current;
}

double ln2_equation() {
    return log(2.0);
}

// вычисление √2
double sqrt2_limit(double epsilon) {
    double previous = 0.0, current = -0.5; // Начальное условие x0 = -0.5
    unsigned long iter = 0;
    
    do {
        iter++;
        previous = current;
        // x(n+1) = x(n) - x(n)²/2 + 1
        current = previous - (previous * previous) / 2.0 + 1.0;
    } while (fabs(current - previous) >= epsilon && iter < MAX_ITERATIONS);
    
    return current;
}

double sqrt2_product(double epsilon) {
    double current = 1.0, previous = 0.0;
    unsigned long iter = 1;
    
    do {// 2^(2^(-k))
        iter++;
        previous = current;
        
        double exponent = pow(2.0, -iter);
        current *= pow(2.0, exponent);
        
    } while (fabs(current - previous) >= epsilon && iter < MAX_ITERATIONS);
    
    return current;
}

double sqrt2_equation() {
    return sqrt(2.0);
}

// вычисление y это (постоянная Эйлера-Маскерони)
double gamma_limit(double epsilon) {
    double previous = 0.0, current = 0.0;
    int m = 1;
    
    do {
        m++;
        previous = current;
        current = 0.0;
        
        for (int k = 1; k <= m; k++) {
            long long comb = coefficient_C(m, k);
            double sign = (k % 2 == 0) ? 1.0 : -1.0;
            double log_factorial = 0.0;
            
            // Вычисление ln(k!)
            for (int i = 1; i <= k; i++) {
                log_factorial += log(i);
            }
            // Добавляем член: C(m,k) × (-1)^k × ln(k!) / k
            current += comb * sign * log_factorial / k;
        }
        
    } while (fabs(current - previous) >= epsilon && m < 100);
    
    return current;
}

double gamma_series(double epsilon) {

    double pi = pi_equation();
    double sum = -pi * pi / 6.0; // Начальное значение: -π²/6
    double previous = 0.0, before_previous = 0.0;
    unsigned long k = 1;
    
    do {
        k++;
        before_previous = previous;
        previous = sum;
        
        int sqrt_k = (int)sqrt(k);
        double term = 1.0 / (sqrt_k * sqrt_k) - 1.0 / k; // Член ряда: 1/[√k]² - 1/k
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


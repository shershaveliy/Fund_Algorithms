#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include "converting.h"

void runTest(int number, int r, const char* expected, const char* testName) {
    char buffer[65];
    decimalToBase2R(number, r, buffer);
    
    printf("Тест: %s\n", testName);
    printf("Вход: %d, основание 2^%d\n", number, r);
    printf("Ожидалось: %s\n", expected);
    printf("Получилось: %s\n", buffer);
    
    int success = 1;
    for (int i = 0; expected[i] != '\0' || buffer[i] != '\0'; i = increment(i)) {
        if (expected[i] != buffer[i]) {
            success = 0;
            break;
        }
    }
    
    printf("Result: %s\n\n", success ? "PASS" : "FAIL");
}

void testZero() {
    runTest(0, 1, "0", "Тест нуля");
}

void testPositiveNumbers() {
    runTest(5, 1, "101", "Положительное число основание 2^1");
    runTest(10, 2, "22", "Положительное число основание 2^2");
    runTest(15, 3, "17", "Положительное число основание 2^3");
    runTest(255, 4, "ff", "Положительное число основание 2^4");
    runTest(100, 5, "34", "Положительное число основание 2^5");
}

void testNegativeNumbers() {
    runTest(-5, 1, "-101", "Отрицательное число основание 2^1");
    runTest(-10, 2, "-22", "Отрицательное число основание 2^2");
    runTest(-15, 3, "-17", "Отрицательное число основание 2^3");
}

void testBoundaryValues() {
    runTest(INT_MAX, 1, "1111111111111111111111111111111", "MAX_INT основание 2^1");
    runTest(INT_MIN, 4, "-80000000", "MIN_INT основание 2^4");
    runTest(1, 1, "1", "Минимальное положительное");
    runTest(-1, 1, "-1", "Максимальное отрицательное");
}

void testInvalidBase() {
    char buffer[65];
    decimalToBase2R(10, 0, buffer);
    printf("Тест: Некорректное основание (0)\n");
    printf("Result: %s\n\n", buffer[0] == '\0' ? "PASS" : "FAIL");
    
    decimalToBase2R(10, 6, buffer);
    printf("Тест: Некорректное основание (6)\n");
    printf("Result: %s\n\n", buffer[0] == '\0' ? "PASS" : "FAIL");
}

void testSpecialCases() {
    runTest(1, 1, "1", "Единица в двоичной");
    runTest(2, 1, "10", "Двойка в двоичной");
    runTest(3, 1, "11", "Тройка в двоичной");
    runTest(16, 4, "10", "Степень двойки в старшем основании");
}

int main() {
    printf("Тесты для конвертации в систему счисления 2^r:\n\n");
    
    testZero();
    testPositiveNumbers();
    testNegativeNumbers();
    testBoundaryValues();
    testInvalidBase();
    testSpecialCases();
    
    printf("Конец :(\n");
    return 0;
}
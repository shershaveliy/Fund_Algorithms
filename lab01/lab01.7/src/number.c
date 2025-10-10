#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/number.h"

int find_min_base(const char* number) {
    if (number == NULL || *number == '\0') {
        return -1;
    }

    const char* ptr = number;
    int max_digit = 1; // Минимальная цифра - 1 (цифра 0 не влияет на основание)
    
    // Пропускаем знак минус если есть
    if (*ptr == '-') {
        ptr++;
    }
    
    // Пропускаем ведущие нули для определения значимых цифр
    while (*ptr == '0' && *(ptr + 1) != '\0') {
        ptr++;
    }
    
    // Если после ведущих нулей строка пуста, это число 0
    if (*ptr == '\0') {
        return 2; // Для числа 0 минимальное основание 2
    }
    
    // Находим максимальную цифру в числе
    while (*ptr != '\0') {
        char c = toupper(*ptr);
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            return -1; // Некорректный символ
        }
        
        if (digit > max_digit) {
            max_digit = digit;
        }
        
        ptr++;
    }
    
    // Минимальное основание = max_digit + 1, но не менее 2
    return (max_digit + 1 > 2) ? max_digit + 1 : 2;
}

char* remove_leading_zeros(const char* number) {
    if (number == NULL || *number == '\0') {
        char* result = malloc(1);
        result[0] = '\0';
        return result;
    }
    
    const char* ptr = number;
    int is_negative = 0;
    
    // Обрабатываем знак минус
    if (*ptr == '-') {
        is_negative = 1;
        ptr++;
    }
    
    // Пропускаем ведущие нули
    while (*ptr == '0' && *(ptr + 1) != '\0') {
        ptr++;
    }
    
    // Вычисляем длину результата
    int len = strlen(ptr);
    if (len == 0) {
        // Все цифры были нулями - возвращаем "0"
        char* result = malloc(2);
        strcpy(result, "0");
        return result;
    }
    
    // Выделяем память с учетом знака
    char* result = malloc(len + is_negative + 1);
    
    // Формируем результат
    if (is_negative) {
        result[0] = '-';
        strcpy(result + 1, ptr);
    } else {
        strcpy(result, ptr);
    }
    
    return result;
}

long long convert_to_decimal(const char* num_str, int base) {
    if (num_str == NULL || *num_str == '\0') {
        return 0;
    }
    
    long long result = 0;
    int sign = 1;
    const char* ptr = num_str;
    
    // Обрабатываем знак
    if (*ptr == '-') {
        sign = -1;
        ptr++;
    }
    
    // Конвертируем
    while (*ptr != '\0') {
        char c = toupper(*ptr);
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else {
            digit = c - 'A' + 10;
        }
        
        result = result * base + digit;
        ptr++;
    }
    
    return result * sign;
}

int is_valid_number_for_base(const char* number, int base) {
    if (number == NULL || *number == '\0' || base < 2 || base > 36) {
        return 0;
    }
    
    const char* ptr = number;
    
    // Пропускаем знак минус
    if (*ptr == '-') {
        ptr++;
    }
    
    // Проверяем каждую цифру
    while (*ptr != '\0') {
        char c = toupper(*ptr);
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            return 0; // Некорректный символ
        }
        
        if (digit >= base) {
            return 0; // Цифра превышает основание
        }
        
        ptr++;
    }
    
    return 1;
}
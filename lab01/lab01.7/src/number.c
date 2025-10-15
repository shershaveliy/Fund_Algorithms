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
    int max_digit = 1; // Минимальная цифра - 1
    
    if (*ptr == '-') {
        ptr++;
    }
    
    while (*ptr == '0' && *(ptr + 1) != '\0') {
        ptr++;
    }
    
    if (*ptr == '\0') {
        return 2;
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
    
    if (*ptr == '-') {
        is_negative = 1;
        ptr++;
    }
    
    while (*ptr == '0' && *(ptr + 1) != '\0') {
        ptr++;
    }
    
    int len = strlen(ptr);
    if (len == 0) {
        char* result = malloc(2);
        strcpy(result, "0");
        return result;
    }
    
    // Выделяем память с учетом знака
    char* result = malloc(len + is_negative + 1);
    
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
    
    if (*ptr == '-') {
        sign = -1;
        ptr++;
    }
    
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
    
    if (*ptr == '-') {
        ptr++;
    }
    
    while (*ptr != '\0') {
        char c = toupper(*ptr);
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            return 0; 
        
        if (digit >= base) {
            return 0;
        }
        
        ptr++;
    }
    
    return 1;
}
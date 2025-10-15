#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/status.h"
#include "../include/step.h"

int compare_numbers(const char* num1, const char* num2, int base){
    int sign1 = (num1[0] == '-') ? -1 : 1;
    int sign2 = (num2[0] == '-') ? -1 : 1;
    

    const char* abs_num1 = (num1[0] == '-') ? num1 + 1 : num1;
    const char* abs_num2 = (num2[0] == '-') ? num2 + 1 : num2;
    
    while(*abs_num1 == '0' && *(abs_num1 + 1) != '\0') abs_num1++;
    while(*abs_num2 == '0' && *(abs_num2 + 1) != '\0') abs_num2++;
    
    int len1 = strlen(abs_num1);
    int len2 = strlen(abs_num2);
    
    if(len1 != len2){
        int result = (len1 > len2) ? 1 : -1;
        return (sign1 > 0) ? result : -result;
    }
    
    for(int i = 0; i < len1; i++){
        char c1 = abs_num1[i];
        char c2 = abs_num2[i];
        
        int digit1, digit2;
        
        if(c1 >= '0' && c1 <= '9') digit1 = c1 - '0';
        else digit1 = c1 - 'A' + 10;
        
        if(c2 >= '0' && c2 <= '9') digit2 = c2 - '0';
        else digit2 = c2 - 'A' + 10;
        
        if(digit1 != digit2) {
            int result = (digit1 > digit2) ? 1 : -1;
            return (sign1 > 0) ? result : -result;
        }
    }
    
    return 0;
}

long long convert_to_decimal(const char* num_str, int base){
    long long result = 0;
    int sign = 1;
    const char* ptr = num_str;
    
    // Знак
    if(*ptr == '-'){
        sign = -1;
        ptr++;
    }
    
    while(*ptr != '\0'){
        char c = *ptr;
        int digit;
        
        if(c >= '0' && c <= '9'){
            digit = c - '0';
        }
        else{
            digit = c - 'A' + 10;
        }
        
        result = result * base + digit;
        ptr++;
    }
    
    return result * sign;
}

char* decimal_to_base(long long num, int base){
    if (num == 0){
        char* result = malloc(2);
        strcpy(result, "0");
        return result;
    }
    
    int is_negative = 0;
    unsigned long long abs_num;
    if (num < 0){
        is_negative = 1;
        abs_num = -num;
    }
    else{
        abs_num = num;
    }
    

    int len = 0;
    unsigned long long temp = abs_num;
    while (temp > 0){
        len++;
        temp /= base;
    }
    if (is_negative) len++; // Место для знака минус
    
    char* result = malloc(len + 1);
    result[len] = '\0';
    
    int index = len - 1;
    while (abs_num > 0){
        int digit = abs_num % base;
        if (digit < 10) {
            result[index] = '0' + digit;
        } 
        else{
            result[index] = 'A' + (digit - 10);
        }
        abs_num /= base;
        index--;
    }
    

    if (is_negative){
        result[0] = '-';
    }
    
    return result;
}
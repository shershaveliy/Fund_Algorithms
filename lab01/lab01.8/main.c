#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/status.h"
#include "include/step.h"


int is_valid_number(const char* str, int base) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    const char* ptr = str;
    if (*ptr == '-') {
        ptr++;
    }
    
    if (*ptr == '\0') {
        return 0;
    }
    
    while (*ptr != '\0') {
        char c = *ptr;
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            return 0;
        }
        
        if (digit >= base) {
            return 0;
        }
        
        ptr++;
    }
    
    return 1;
}

int main() {
    int base;
    printf("Введите основание системы счисления: ");
    
    if (scanf("%d", &base) != 1) {
        print_status(INVALID_THE_NUMBER_SYSTEM);
        return 1;
    }
    
    if (base < 2 || base > 36) {
        print_status(INVALID_THE_NUMBER_SYSTEM);
        return 1;
    }
    
    printf("Вводите числа в этой системе счисления,\nпри завершении введите ключевое слово 'STOP'\n");
    
    char** numbers = NULL;
    int count = 0;
    int capacity = 10;
    
    numbers = malloc(capacity * sizeof(char*));
    if (numbers == NULL) {
        print_status(INVALID_MEMORY_ALLOCATION);
        free(numbers);
        return 1;
    }
    
    char input[100];
    
    while (1) {
        if (scanf("%99s", input) != 1) {
            print_status(NUMBER_TOO_LARGE);
            continue;
        }
        
        if (strcmp(input, "STOP") == 0) {
            break;
        }
        
        // Проверяем корректность числа
        if (!is_valid_number(input, base)) {
            print_status(INVALID_NUMBER);
            continue;
        }
        
        if (count >= capacity) {
            capacity *= 2;
            char** new_numbers = realloc(numbers, capacity * sizeof(char*));
            if (new_numbers == NULL) {
                print_status(INVALID_MEMORY_REALLOCATION);
                free(numbers);
                free(new_numbers);
                return 1;
            }
            numbers = new_numbers;
        }
        
        // Копия строки
        numbers[count] = malloc(strlen(input) + 1);
        if (numbers[count] == NULL) {
            print_status(INVALID_MEMORY_ALLOCATION);
            for (int i = 0; i <= count; i++) {
                free(numbers[i]);
            }
            free(numbers);
            return 1;
        }
        strcpy(numbers[count], input);
        count++;
    }
    
    if (count == 0) {
        printf("Не введено ни одного числа\n");
        free(numbers);
        return 1;
    }
    
    int max_index = 0;
    for (int i = 1; i < count; i++) {
        if (compare_numbers(numbers[i], numbers[max_index], base) > 0) {
            max_index = i;
        }
    }
    
    printf("\nМаксимальное число: %s\n", numbers[max_index]);
    

    long long decimal_max = convert_to_decimal(numbers[max_index], base);
    printf("В десятичной системе: %lld\n", decimal_max);
    

    printf("Представление в различных системах счисления:\n");
    
    int target_bases[] = {9, 18, 27, 36};
    for (int i = 0; i < 4; i++) {
        char* converted = decimal_to_base(decimal_max, target_bases[i]);
        printf("Основание %d: %s\n", target_bases[i], converted);
        free(converted);
    }
    
    for (int i = 0; i <= count; i++) {
        free(numbers[i]);
    }
    free(numbers);
    
    return 0;
}
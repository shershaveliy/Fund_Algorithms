#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/file.h"
#include "../include/number.h"

int process_file(const char* input_filename, const char* output_filename) {
    FILE* input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Ошибка: не удалось открыть входной файл '%s'\n", input_filename);
        return 1;
    }

    FILE* output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Ошибка: не удалось создать выходной файл '%s'\n", output_filename);
        fclose(input_file);
        return 1;
    }

    char buffer[1024];
    int line_number = 0;

    while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
        line_number++;
        
        // Разбиваем строку на токены
        char* token = strtok(buffer, " \t\n\r");
        
        while (token != NULL) {
            if (strlen(token) == 0) {
                token = strtok(NULL, " \t\n\r");
                continue;
            }

            // Находим минимальное основание
            int min_base = find_min_base(token);
            
            if (min_base >= 2 && min_base <= 36) {
                char* cleaned_number = remove_leading_zeros(token);
                
                long long decimal_value = convert_to_decimal(cleaned_number, min_base);
                
                fprintf(output_file, "%s %d %lld\n", cleaned_number, min_base, decimal_value);
                
                free(cleaned_number);
            } else {
                fprintf(stderr, "Предупреждение: строка '%s' не является корректным числом (строка %d)\n", 
                        token, line_number);
            }
            
            token = strtok(NULL, " \t\n\r");
        }
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}
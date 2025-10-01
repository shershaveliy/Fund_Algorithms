#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operations.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Ошибка: не указан флаг. Используйте -q, -m или -t\n");
        printf("Пример: %s -q 0.0001 1 -3 2\n", argv[0]);
        return 1;
    }

    char* flag = argv[1];
    
    if (flag[0] != '-' && flag[0] != '/') {
        printf("Ошибка: флаг должен начинаться с '-' или '/'\n");
        return 1;
    }

    char flag_char = flag[1];
    
    switch (flag_char) {
        case 'q':
            if (argc != 6) {
                printf("Ошибка: для флага -q требуется 5 параметров\n");
                printf("Использование: %s -q epsilon a b c\n", argv[0]);
                return 1;
            }
            quadro(argv);
            break;
            
        case 'm':
            if (argc != 4) {
                printf("Ошибка: для флага -m требуется 2 параметра\n");
                printf("Использование: %s -m number1 number2\n", argv[0]);
                return 1;
            }
            check_multiple(argv);
            break;
            
        case 't':
            if (argc != 6) {
                printf("Ошибка: для флага -t требуется 5 параметров\n");
                printf("Использование: %s -t epsilon side1 side2 side3\n", argv[0]);
                return 1;
            }
            triangle(argv);
            break;
            
        default:
            printf("Ошибка: неизвестный флаг '%c'\n", flag_char);
            printf("Доступные флаги: -q, -m, -t\n");
            return 1;
    }

    return 0;
}
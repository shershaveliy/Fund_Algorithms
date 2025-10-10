#include "../include/status.h"
#include <stdio.h>

const char* get_status_message(Status status) {
    switch (status) {
        case OK: return "OK";
        case INVALID_MEMORY_ALLOCATION: return "Ошибка выделения памяти";
        case INVALID_MEMORY_REALLOCATION: return "Ошибка перевыделения памяти";
        case INVALID_NUMBER: return "Некорректно введено число, имеются символы недопустимые символы для данной системы счисления";
        case NEGATIVE_NUMBER: return "Число должно быть неотрицательным";
        case DIVISION_BY_ZERO: return "Деление на ноль";
        case NUMBER_TOO_LARGE: return "Число слишком большое";
        case INVALID_THE_NUMBER_SYSTEM: return "Некорректно введена система основания, должно быть в деапозоне от 2 до 36";
        default: return "Неизвестная ошибка";
    }
}

void print_status(Status status) {
    if (status != OK) {
        fprintf(stderr, "Ошибка: %s\n", get_status_message(status));
    }
}
#include "../include/status.h"
#include <stdio.h>

const char* get_status_message(Status status) {
    switch (status) {
        case OK: return "OK";
        case INVALID_ARGS_COUNT: return "Неверное количество аргументов";
        case INVALID_FLAG_FORMAT: return "Неверный формат флага";
        case INVALID_NUMBER: return "Некорректное число";
        case NEGATIVE_NUMBER: return "Число должно быть неотрицательным";
        case DIVISION_BY_ZERO: return "Деление на ноль";
        case NUMBER_TOO_LARGE_FOR_MULTIPLES: return "Число слишком большое для поиска кратных";
        case NUMBER_TOO_LARGE_FOR_POWERS: return "Число должно быть от 0 до 10";
        case NUMBER_TOO_LARGE_FOR_FACTORIAL: return "Число должно быть от 0 до 20";
        case UNKNOWN_FLAG: return "Неизвестный флаг";
        default: return "Неизвестная ошибка";
    }
}

void print_status(Status status) {
    if (status != OK) {
        fprintf(stderr, "Ошибка: %s\n", get_status_message(status));
    }
}
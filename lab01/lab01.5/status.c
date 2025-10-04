#include "status.h"
#include <stdio.h>

const char* getStatusMessage(Status status) {
    switch (status) {
        case OK: return "OK";
        case INVALID_ARGS_COUNT: return "Неверное количество аргументов";
        case INVALID_FLAG: return "Неверный формат флага";
        case CANT_OPEN_INPUT_FILE: return "Не удалось открыть входной файл";
        case CANT_CREATE_OUTPUT_FILE: return "Не удалось создать выходной файл";
        case UNKNOWN_FLAG: return "Неизвестный флаг";
        default: return "Неизвестная ошибка";
    }
}

void printStatus(Status status) {
    fprintf(stderr, "Ошибка: %s\n", getStatusMessage(status));
}
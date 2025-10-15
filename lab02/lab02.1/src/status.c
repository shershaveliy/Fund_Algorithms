#include "../include/status.h"
#include <stdio.h>

const char* get_status_message(Status status) {
    switch (status) {
        case OK: return "OK";
        case ERROR_INVALID_BASE: return "Неверное основание системы счисления";
        case ERROR_INVALID_NUMBER: return "Число вне диапазона (0;1)";
        case ERROR_MEMORY: return "Ошибка памяти";
        default: return "Неизвестная ошибка";
    }
}

void print_status(Status status) {
    if (status != OK) {
        fprintf(stderr, "Ошибка: %s\n", get_status_message(status));
    }
}
#include "../include/status.h"
#include <stdio.h>

const char* get_status_message(Status status){
    switch (status){
        case OK: return "OK";
        case ERROR_FILE_NOT_FOUND: return "Файл не найден";
        case ERROR_MEMORY: return "Ошибка памяти";
        case ERROR_INVALID_DATA: return "Неверный формат данных";
        case ERROR_STUDENT_NOT_FOUND: return "Студент не найден";
        case ERROR_NO_TRACE_FILE: return "Файл трассировки не указан";
        default: return "Неизвестная ошибка";
    }
}

void print_status(Status status){
    if (status != OK) {
        fprintf(stderr, "Ошибка: %s\n", get_status_message(status));
    }
}
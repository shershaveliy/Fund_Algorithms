#ifndef STATUS_H
#define STATUS_H

typedef enum {
    OK = 0,
    INVALID_ARGS_COUNT,
    INVALID_FLAG_FORMAT,
    INVALID_NUMBER,
    INVALID_NUMBER_DOUBLE,
    NEGATIVE_NUMBER,
    DIVISION_BY_ZERO,
    NUMBER_TOO_LARGE_FOR_MULTIPLES,
    NUMBER_TOO_LARGE_FOR_POWERS,
    NUMBER_TOO_LARGE_FOR_FACTORIAL,
    UNKNOWN_FLAG
} Status;

const char* get_status_message(Status status);
void print_status(Status status);

#endif
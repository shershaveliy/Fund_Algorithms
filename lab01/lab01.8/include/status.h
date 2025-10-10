#ifndef STATUS_H
#define STATUS_H

typedef enum {
        OK = 0,
        INVALID_MEMORY_ALLOCATION,
        INVALID_MEMORY_REALLOCATION,
        INVALID_NUMBER,
        NEGATIVE_NUMBER,
        DIVISION_BY_ZERO,
        NUMBER_TOO_LARGE,
        INVALID_THE_NUMBER_SYSTEM,
    
} Status;

const char* get_status_message(Status status);
void print_status(Status status);

#endif
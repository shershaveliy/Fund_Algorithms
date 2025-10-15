#ifndef STATUS_H
#define STATUS_H

typedef enum {
    OK = 0,
    ERROR_INVALID_BASE,
    ERROR_INVALID_NUMBER,
    ERROR_MEMORY
} Status;

void print_status(Status status);

#endif
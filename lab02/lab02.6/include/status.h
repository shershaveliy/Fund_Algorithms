#ifndef STATUS_H
#define STATUS_H

typedef enum{
    OK = 0,
    ERROR_FILE_NOT_FOUND,
    ERROR_MEMORY,
    ERROR_INVALID_DATA,
    ERROR_STUDENT_NOT_FOUND,
    ERROR_NO_TRACE_FILE
} Status;

const char* get_status_message(Status status);
void print_status(Status status);

#endif
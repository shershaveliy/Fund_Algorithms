#ifndef STATUS_H
#define STATUS_H

typedef enum {
    OK,
    INVALID_ARGS_COUNT,
    INVALID_FLAG,
    CANT_OPEN_INPUT_FILE,
    CANT_CREATE_OUTPUT_FILE,
    UNKNOWN_FLAG
} Status;

void printStatus(Status status);
const char* getStatusMessage(Status status);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flag.h"
#include "status.h"

void Usage() {
    printf("Надо ввести: <программа> <флаг> <входной файл> [выходной файл]\n");
}

const char* getBasename(const char* path) {
    const char* lastSlash = strrchr(path, '/');
    const char* lastWinslash = strrchr(path, '\\');
    const char* basename = path;
    
    if (lastSlash != NULL) {
        basename = lastSlash + 1;
    }
    if (lastWinslash != NULL) {
        basename = lastWinslash + 1;
    }
    
    return basename;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printStatus(INVALID_ARGS_COUNT);
        Usage();
        return 1;
    }

    char* flag = argv[1];
    char* inputFile = argv[2];
    char* outputFile = NULL;
    int outputFileAllocated = 0; // Динам память


    if ((flag[0] != '-' && flag[0] != '/') || flag[1] == '\0') {
        printStatus(INVALID_FLAG);
        Usage();
        return 1;
    }

    if (flag[1] == 'n') {
        if (argc < 4) {
            printStatus(INVALID_ARGS_COUNT);
            Usage();
            return 1;
        }
        outputFile = argv[3];
    }
    else {

        const char* basename = getBasename(inputFile);
        outputFile = malloc(strlen(basename) + 5);
        if (outputFile == NULL) {
            printStatus(CANT_CREATE_OUTPUT_FILE);
            return 1;
        }
        sprintf(outputFile, "out_%s", basename);
        outputFileAllocated = 1;
    }

    FILE* fin = fopen(inputFile, "r");
    if (fin == NULL) {
        if (outputFileAllocated) {
            free(outputFile);
        }
        printStatus(CANT_OPEN_INPUT_FILE);
        return 1;
    }

    FILE* fout = fopen(outputFile, "w");
    if (fout == NULL) {
        fclose(fin);
        if (outputFileAllocated) {
            free(outputFile);
        }
        printStatus(CANT_CREATE_OUTPUT_FILE);
        return 1;
    }

    char operation;
    if (flag[1] == 'n') {
        operation = flag[2];
    } else {
        operation = flag[1];
    }

    Status result = OK;
    switch (operation) {
        case 'd':
            DFlag(fin, fout);
            break;
        case 'i':
            IFlag(fin, fout);
            break;
        case 's':
            SFlag(fin, fout);
            break;
        case 'a':
            AFlag(fin, fout);
            break;
        default:
            result = UNKNOWN_FLAG;
            printStatus(UNKNOWN_FLAG);
            Usage();
            break;
    }

    fclose(fin);
    fclose(fout);
    
    if (outputFileAllocated) {
        free(outputFile);
    }

    return (result == OK) ? 0 : 1;
}
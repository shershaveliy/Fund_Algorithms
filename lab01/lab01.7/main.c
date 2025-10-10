#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/file.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <входной_файл> <выходной_файл>\n", argv[0]);
        return 1;
    }

    return process_file(argv[1], argv[2]);
}
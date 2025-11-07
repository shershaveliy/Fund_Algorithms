#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "include/readFiles.h"

int main(void) {
/*
    char path[200];

    printf("Введите путь к входному файлу:\n");
    scanf("%s", path);

    FILE * fin = fopen(path, "r");
    if (!fin) {
        printf("Ошибка: не удалось открыть файл.");
        return 1;
    }

    printf("Введите путь к выходному файлу:\n");
    scanf("%s", path);

    FILE * fout = fopen(path, "w");
    if (!fout) {
        printf("Ошибка: не удалось открыть файл.");
        return 1;
    }
*/
    const char *input = "in.txt";
    const char *output = "out.txt";

    FILE *fin = fopen(input, "r");
    FILE *fout = fopen(output, "w");

    if (!fin || !fout) {
        printf("Ошибка открытия файлов\n");
        return 1;
    }

    format_files(fin, fout);

    fclose(fin);
    fclose(fout);
    printf("Готово!\n");
    return 0;
}

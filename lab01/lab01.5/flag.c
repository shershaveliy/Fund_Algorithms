#include "flag.h"
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

void DFlag(FILE* fin, FILE* fout) {
    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        if (!isdigit(ch)) {
            fputc(ch, fout);
        }
    }
}

void IFlag(FILE* fin, FILE* fout) {
    int ch;
    int latinCount = 0;
    while ((ch = fgetc(fin)) != EOF) {
        if (ch == '\n') {
            fprintf(fout, "%d\n", latinCount);
            latinCount = 0;
        }
        else if (isalpha(ch)) {
            latinCount++;
        }
    }
    if (latinCount > 0) {
        fprintf(fout, "%d\n", latinCount);
    }
}

void SFlag(FILE* fin, FILE* fout) {
    int ch;
    int count = 0;
    while ((ch = fgetc(fin)) != EOF) {
        if (ch == '\n') {
            fprintf(fout, "%d\n", count);
            count = 0;
        }
        else if (!isalpha(ch) && !isdigit(ch) && !isspace(ch)) {
            count++;
        }
    }
    if (count > 0) {
        fprintf(fout, "%d\n", count);
    }
}

void AFlag(FILE* fin, FILE* fout) {
    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        if (isdigit(ch)) {
            fputc(ch, fout);
        }
        else{
            fprintf(fout, "%02X", (unsigned char)ch);
        }
        if(ch == '\n'){
            fprintf(fout, "\n");
        }
    }
}
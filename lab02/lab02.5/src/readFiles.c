#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "../include/readFiles.h"

#define TARGET_LENGTH 80

typedef struct {
    int end_pos;// позиция конца слова
    int spaces;// количество пробелов после слова
} WordInfo;


void add_spaces(WordInfo words[], int word_count){
    int spaces_to_add = TARGET_LENGTH - words[word_count - 1].end_pos;

    int gaps = word_count - 1; // Промежутки
    if (gaps <= 0) return;

    int base = spaces_to_add / gaps;
    int extra = spaces_to_add % gaps;

    for (int i = 0; i < gaps; i++){
        words[i].spaces += base;
    }
    for (int i = 0; i < extra; i++){
        words[i].spaces++;
    }
}

// Форматирование строки
void fill_line(char tmp[TARGET_LENGTH + 2], char *buffer, WordInfo *words, int word_count){

    tmp[TARGET_LENGTH + 1] = '\0';
    char *p = tmp;
    int prev_end = 0;

    for (int i = 0; i < word_count; i++){
        buffer[words[i].end_pos] = '\0';
        //копир слово в буффер tmp и ставим пробелы после него
        strcpy(p, buffer + prev_end);
        p += words[i].end_pos - prev_end;
        memset(p, ' ', words[i].spaces);
        p += words[i].spaces;
        prev_end = words[i].end_pos;
        //возвращ пробел в исходный буфер
        buffer[words[i].end_pos] = ' ';
    }

    *p = '\n';
    p++;
    *p = '\0';
}

//Перенос остатка в начало буфера 
void move_remainder(char tmp[TARGET_LENGTH + 2], char *buffer, WordInfo *words, int word_count, int *count, int c){

    int last_end = words[word_count - 1].end_pos;
    buffer[TARGET_LENGTH] = c; //Вот почему была потеря знака
    buffer[TARGET_LENGTH + 1] = '\0';
    strcpy(tmp, buffer);

    while (tmp[last_end] == ' '){
        last_end++; // Пропуск пробелов после последнего целого слова
    }
    strcpy(buffer, tmp + last_end);

    *count = TARGET_LENGTH + 1 - last_end;
}


void format_files(FILE *fin, FILE *fout){
    int prev = '\n';
    int c;
    char buffer[TARGET_LENGTH + 2];
    buffer[TARGET_LENGTH + 1] = '\0';
    int count = 0;

    WordInfo words[TARGET_LENGTH];
    words[0].end_pos = -1;
    int word_count = 0;

    while ((c = fgetc(fin)) != EOF){
        //Естественное разбиение
        if (c == '\n' || (count == TARGET_LENGTH && isspace((unsigned char)c) && !isspace((unsigned char)prev))){

            if (count > 0){
                buffer[count] = '\n';
                buffer[count + 1] = '\0';
                fputs(buffer, fout);
            }

            count = 0;
            buffer[0] = '\0';
            word_count = 0;
            c = 0;
        }

        else if (count == TARGET_LENGTH){
            if (word_count == 0){
                // одно большое слово ровно 80 символов
                buffer[count] = '\n';
                buffer[count + 1] = '\0';
                fputs(buffer, fout);
                count = 0;
                continue;
            }

            if (word_count > 1) add_spaces(words, word_count);

            char tmp[TARGET_LENGTH + 2];
            fill_line(tmp, buffer, words, word_count);
            fputs(tmp, fout);
            move_remainder(tmp, buffer, words, word_count, &count, c);

            c = 0;
            word_count = 0;
        }
        //Добавление символа
        else if (!(count == 0 && isspace((unsigned char)c))) {
            if (!isspace((unsigned char)prev) && isspace((unsigned char)c)) {
                words[word_count].end_pos = count;
                words[word_count].spaces = 0;
                word_count++;
            }
            buffer[count++] = c;
        }

        prev = c;
    }

    buffer[count] = '\0';
    fputs(buffer, fout);
}
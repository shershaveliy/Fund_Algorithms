#include "../include/overscanf.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>


static int handle_standard_specifier_scanf(const char **format, va_list args, FILE *stream, const char **str, bool is_stream){
    const char *specifiers = "diuoxXfFeEgGaAcspn[]";  // добавил [] для сканирования наборов
    char format_buf[32] = {0};
    char *buf = format_buf;
    
    *buf++ = '%';
    
    const char *p = *format;
    
    // 1. Флаги: * (подавление присваивания)
    if (*p == '*'){
        *buf++ = *p++;
    }
    
    // 2. Ширина (число)
    while (*p >= '0' && *p <= '9'){
        *buf++ = *p++;
    }
    
    //Модификаторы размера: h, hh, l, ll, L, j, z, t
    if (*p == 'h'){
        *buf++ = *p++;
        if (*p == 'h'){
            *buf++ = *p++;
        }
    }
    else if (*p == 'l'){
        *buf++ = *p++;
        if (*p == 'l'){
            *buf++ = *p++;
        }
    }
    else if (*p == 'L' || *p == 'j' || *p == 'z' || *p == 't'){
        *buf++ = *p++;
    }
    
    //Копируем спецификатор
    if (*p && strchr(specifiers, *p)){
        *buf++ = *p++;
        
        // Особый случай: сканирование наборов [abc] или [^abc]
        if (*(p-1) == '['){
            // Копируем всё до закрывающей ]
            while (*p && *p != ']'){
                if (buf < format_buf + sizeof(format_buf) - 1){
                    *buf++ = *p++;
                } else {
                    break;  // защита от переполнения
                }
            }
            if (*p == ']'){
                *buf++ = *p++;  // копируем закрывающую ]
            }
        }
    }
    
    *buf = '\0';
    *format = p;
    
    if (is_stream)
        return vfscanf(stream, format_buf, args);
    else
        return vsscanf(*str, format_buf, args);
}

int overfscanf(FILE *stream, const char *format, ...){
    va_list args;
    va_start(args, format);

    int total_read = 0;
    const char *p = format;

    while (*p){
        if (*p != '%'){ 
            fgetc(stream);
            p++;
            continue;
        }

        p++;
        if (*p == '%'){
            fgetc(stream);
            p++; continue;
        }

        int read = 0;
        va_list args_copy;
        va_copy(args_copy, args);

        if ((p[0] == 'R' && p[1] == 'o') ||
            (p[0] == 'Z' && p[1] == 'r') ||
            (p[0] == 'C' && (p[1] == 'v' || p[1] == 'V'))){
            read = handle_custom_specifier_scan(&p, args_copy, stream, NULL, true);
        }
        else{
            read = handle_standard_specifier_scanf(&p, args_copy, stream, NULL, true);
        }

        if (read > 0) total_read += read;
        else break;//Ошибка чтения
    }

    va_end(args);
    return total_read;
}

int oversscanf(const char *str, const char *format, ...){
    va_list args;
    va_start(args, format);

    int total_read = 0;
    const char *p = format;
    const char *input_ptr = str;

    while (*p){
        if (*p != '%'){
            input_ptr++;
            p++;
            continue;
        }

        p++;
        if (*p == '%'){
            input_ptr++;
            p++;
            continue;
        }

        int read = 0;
        va_list args_copy;
        va_copy(args_copy, args);

        if ((p[0] == 'R' && p[1] == 'o') ||
            (p[0] == 'Z' && p[1] == 'r') ||
            (p[0] == 'C' && (p[1] == 'v' || p[1] == 'V'))){
            read = handle_custom_specifier_scan(&p, args_copy, NULL, &input_ptr, false);
        }
        else{
            read = handle_standard_specifier_scanf(&p, args_copy, NULL, &input_ptr, false);
        }
        va_end(args_copy);

        if (read > 0) total_read += read;
        else break;
    }

    va_end(args);
    return total_read;
}
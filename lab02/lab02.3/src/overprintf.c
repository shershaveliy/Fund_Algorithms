#include "../include/overprintf.h"
#include <string.h>

//Идем по строке до % начинаем обработку, возвращаем количество
// записанных символов или отриц число при ошибке
int overfprintf(FILE *stream, const char *format, ...){
    va_list args;
    va_start(args, format);
    
    int total_written = 0;
    const char *p = format;
    
    while (*p){
        if (*p != '%'){
            fputc(*p, stream);
            total_written++;
            p++;
            continue;
        }
        
        p++;
        
        if (*p == '%'){
            // Случай '%%'
            fputc('%', stream);
            total_written++;
            p++;
            continue;
        }
        
        char buffer[256];
        int written = 0;
        
        if ((p[0] == 'R' && p[1] == 'o') || (p[0] == 'Z' && p[1] == 'r') ||
            (p[0] == 'C' && (p[1] == 'v' || p[1] == 'V')) ||
            (p[0] == 't' && p[1] == 'o') || (p[0] == 'T' && p[1] == 'O') ||
            (p[0] == 'm' && (p[1] == 'i' || p[1] == 'u' || p[1] == 'd' || p[1] == 'f'))) {
            written = handle_custom_specifier(&p, args, buffer);
        } 
        else{
            written = handle_standard_specifier(&p, args, buffer);
        }
        
        if (written > 0){
            fwrite(buffer, 1, written, stream);
            total_written += written;
        }
    }
    
    va_end(args);
    return total_written;
}

int oversprintf(char *str, const char *format, ...){
    va_list args;
    va_start(args, format);
    
    char *dest = str;
    const char *p = format;
    
    while (*p) {
        if (*p != '%'){
            *dest++ = *p++;
            continue;
        }
        
        p++;
        
        if (*p == '%'){
            *dest++ = '%';
            p++;
            continue;
        }
        
        char buffer[256];
        int written = 0;
        
        if ((p[0] == 'R' && p[1] == 'o') || (p[0] == 'Z' && p[1] == 'r') ||
            (p[0] == 'C' && (p[1] == 'v' || p[1] == 'V')) ||
            (p[0] == 't' && p[1] == 'o') || (p[0] == 'T' && p[1] == 'O') ||
            (p[0] == 'm' && (p[1] == 'i' || p[1] == 'u' || p[1] == 'd' || p[1] == 'f'))) {
            written = handle_custom_specifier(&p, args, buffer);
        }
        else{
            written = handle_standard_specifier(&p, args, buffer);
        }
        
        if (written > 0){
            memcpy(dest, buffer, written);
            dest += written;
        }
    }
    
    *dest = '\0';
    va_end(args);
    return dest - str;
}


//Копируем весь спецификатор вместе с % в буфер чтобы передать в vsprintf
int handle_standard_specifier(const char **format, va_list args, char *buffer){
    const char *p = *format;
    char formatbuf[32];
    char *buf = formatbuf;
    
    *buf++ = '%';
    
    // Копируем все флаги, ширину, точность, модификаторы
    while (*p) {
        // Флаги
        if (*p == '-' || *p == '+' || *p == ' ' || *p == '0' || *p == '#') {
            *buf++ = *p++;
            continue;
        }
        
        // Ширина (цифры или *)
        if (*p == '*' || (*p >= '0' && *p <= '9')) {
            do {
                *buf++ = *p++;
            } while (*p >= '0' && *p <= '9');
            continue;
        }
        
        // Точность
        if (*p == '.') {
            *buf++ = *p++;
            // После точки могут быть цифры или *
            if (*p == '*') {
                *buf++ = *p++;
            } else {
                while (*p >= '0' && *p <= '9') {
                    *buf++ = *p++;
                }
            }
            continue;
        }
        
        // Модификаторы длины
        if (*p == 'h' || *p == 'l' || *p == 'L' || *p == 'j' || *p == 'z' || *p == 't') {
            *buf++ = *p++;
            // Может быть два символа (hh, ll)
            if ((*p == 'h' && *(p-1) == 'h') || (*p == 'l' && *(p-1) == 'l')) {
                *buf++ = *p++;
            }
            continue;
        }
        
        // Спецификаторы
        if (strchr("diuoxXfFeEgGaAcspn", *p)) {
            *buf++ = *p++;
            break;
        }
        
        // Неизвестный символ - завершаем
        break;
    }
    
    *buf = '\0';
    *format = p;
    
    return vsprintf(buffer, formatbuf, args);
}
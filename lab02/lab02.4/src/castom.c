#include "../include/overscanf.h"
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

static int read_token(FILE *stream, const char **str, bool is_stream, char *buf, size_t buf_size){
    int c;
    size_t i = 0;
    
    if (is_stream){
        //Пропускаем пробелы в начале
        while ((c = fgetc(stream)) != EOF && isspace((unsigned char)c));
        if (c == EOF) return 0;
        ungetc(c, stream); // Вернули указатель за символ

        while (i < buf_size - 1 && (c = fgetc(stream)) != EOF && !isspace((unsigned char)c)){
            buf[i++] = (char)c;
        }
    }
    else{
        const char *s = *str;
        while (*s && isspace((unsigned char)*s)){
            s++;
        }
        if (!*s) return 0;

        while (i < buf_size - 1 && *s && !isspace((unsigned char)*s)){
            buf[i++] = *s++;
        }
        *str = s;
    }

    buf[i] = '\0';
    printf("DEBUG: read_token -> '%s'\n", buf); 
    return 1;
}

static int roman_to_int(const char *s){

    struct{
        char c;
        int v;
    } map[] = {
        {'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}
    };

    int total = 0, prev = 0;
    for (const char *p = s; *p; p++){
        char c = toupper((unsigned char)*p);
        int val = 0;
        for (int i = 0; i < 7; i++){
            if (map[i].c == c){
                val = map[i].v;
                break;
            }
        }
        if (val == 0) break;
        //Если текущая цифра больше предыдущей, значит это вычитательная комбинация.
        total += (val > prev) ? val - 2 * prev : val;
        prev = val;
    }
    return total;
}

static int handle_ro(FILE *stream, const char **str, va_list args, bool is_stream){
    int *out = va_arg(args, int *);
    char buf[64];
    if (!read_token(stream, str, is_stream, buf, sizeof(buf))) return 0;
    *out = roman_to_int(buf);
    return 1;
}

static unsigned int zeckendorf_to_uint(const char *s){
    unsigned int fib[46] = {1, 2};
    for (int i = 2; i < 46; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    unsigned int result = 0;
    size_t len = strlen(s);

    if (len > 0 && s[len - 1] == '1') len--;

    // Проверяем на соседние единицы
    for (size_t i = 0; i < len - 1; i++) {
        if (s[i] == '1' && s[i + 1] == '1') {
            // Найдены две единицы подряд - невалидное представление
            return 0; // или можно вернуть ошибку
        }
    }

    // Читаем слева направо, младший бит слева
    for (size_t i = 0; i < len && i < 46; i++) {
        if (s[i] == '1') {
            result += fib[i];
        }
    }
    return result;
}

static int handle_zr(FILE *stream, const char **str, va_list args, bool is_stream){
    unsigned int *out = va_arg(args, unsigned int *);
    char buf[128];
    if (!read_token(stream, str, is_stream, buf, sizeof(buf))) return 0;
    *out = zeckendorf_to_uint(buf);
    return 1;
}


static int base_to_int(const char *s, int base, int is_upper){
    int sign = 1;
    if (*s == '-'){ 
        sign = -1; 
        s++; 
    }
    else if (*s == '+') s++;

    long long result = 0;

    while (*s){
        char c = *s;
        s++;
        int d = -1; //Невалидная цифра
        if (c >= '0' && c <= '9') d = c - '0';
        else if (!is_upper && c >= 'a' && c <= 'z') d = c - 'a' + 10;
        else if (is_upper && c >= 'A' && c <= 'Z') d = c - 'A' + 10;
        if (d < 0 || d >= base) break;
        if (result > (INT_MAX - d) / base)
            return sign == 1 ? INT_MAX : INT_MIN; //Переполнение
        result = result * base + d;
    }
    return (int)(result * sign);
}

static int handle_cv(FILE *stream, const char **str, va_list args, bool is_stream, int is_upper){
    int *out = va_arg(args, int *);
    int base = va_arg(args, int);
    if (base < 2 || base > 36) base = 10;

    char buf[128];
    if (!read_token(stream, str, is_stream, buf, sizeof(buf))) return 0;

    *out = base_to_int(buf, base, is_upper);
    return 1;
}


int handle_custom_specifier_scan(const char **format, va_list args, FILE *stream, const char **str, bool is_stream){
    const char *p = *format;
    va_list args_copy;
    va_copy(args_copy, args);

    int res = 0;
    if (p[0] == 'R' && p[1] == 'o'){
        *format += 2;
        res = handle_ro(stream, str, args_copy, is_stream);
    }
    else if (p[0] == 'Z' && p[1] == 'r'){
        *format += 2;
        res = handle_zr(stream, str, args_copy, is_stream);
    }
    else if (p[0] == 'C' && p[1] == 'v'){
        *format += 2;
        res = handle_cv(stream, str, args_copy, is_stream, 0);
    }
    else if (p[0] == 'C' && p[1] == 'V'){
        *format += 2;
        res = handle_cv(stream, str, args_copy, is_stream, 1);
    }

    va_end(args_copy);
    return res;
}

#include "../include/overprintf.h"
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

static void reverse_string(char *str, int len){

    int i = 0, j = len - 1;
    while(i < j){
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

static void byte_to_binary(unsigned char byte, char *buffer){

    for(int i = 7; i >= 0; i--){
        //сравниваем двоисное представление byte & маску, где только i-й бит равен 1, остальные 0.
        *buffer++ = (byte & (1 << i)) ? '1' : '0';
    }
    *buffer = '\0';
}


static int handle_rim(va_list args, char *buffer){

    int num = va_arg(args, int);

    if(num <= 0 || num > 3999){
        return sprintf(buffer, "%d", num);
    }
    
    struct{
        int value; const char *numeral;
    } numerals[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    
    char *p = buffer;
    int remaining = num;
    
    //Проходим по numerals если число больше чем элемент numerals
    //запускаем цикл while: записываем римские буквы в буффер, вычитаем значение
    //буквы из нашего числа
    for (int i = 0; i < 13; i++){
        while (remaining >= numerals[i].value){
            const char *numeral = numerals[i].numeral;
            while (*numeral){
                *p++ = *numeral++;
            }
            remaining -= numerals[i].value;
        }
    }
    
    *p = '\0';
    return p - buffer; //Возвращ длину рез
}


static int handle_zeckendorf(va_list args, char *buffer){
    unsigned int num = va_arg(args, unsigned int);
    
    if(num == 0){
        strcpy(buffer, "01");
        return 2;
    }
    
    unsigned int fib[46] = {1, 2};
    int count = 2;
    
    for(int i = 2; i < 46; i++){
        fib[i] = fib[i - 1] + fib[i - 2];
        if(fib[i] > num || fib[i] < fib[i-1]) break;
        count++;
    }
    
    char temp[64]; // Временный буфер (старшие разряды слева)
    char *p = temp;
    unsigned int remaining = num;
    
    *p++ = '1';
    int i = count - 1;
    int flag = 1; 
    while(i >= 0){
        if(fib[i] <= remaining && flag == 1){
            *p++ = '1';
            remaining -= fib[i];
            flag = 0;
            i--;
        }
        else{
            *p++ = '0';
            flag = 1;
            i--;
        }
    }
    
    *p = '\0';
    
    int len = p - temp;
    char *dest = buffer;
    for(int j = len - 1; j >= 0; j--) {
        *dest++ = temp[j];
    }
    *dest = '\0';
    
    return len;
}

static int convert_to_base(int num, int base, bool is_upper, char *result) {
    if (base < 2 || base > 36) base = 10;

    if (num == 0) {
        result[0] = '0';
        result[1] = '\0';
        return 1;
    }

    char temp[65];
    int i = 0;

    int is_negative = (num < 0);
    unsigned int n = is_negative ? -num : num;

    while (n > 0) {
        int rem = n % base;
        char c;

        if (rem < 10) c = '0' + rem;
        else c = (is_upper ? 'A' : 'a') + (rem - 10);

        temp[i++] = c;
        n /= base;
    }
    if (is_negative) temp[i++] = '-';
    reverse_string(temp, i);

    memcpy(result, temp, i);
    result[i] = '\0';
    return i;
}

static long long convert_from_base(const char *str, int base, bool is_upper) {
    if (base < 2 || base > 36) base = 10;

    unsigned long long result = 0;
    int is_negative = 0;

    while (isspace((unsigned char)*str)) str++;

    if (*str == '-') {
        is_negative = 1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str) {
        char c = *str;
        int digit;

        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (!is_upper && c >= 'a' && c <= 'z') {
            digit = c - 'a' + 10;
        } else if (is_upper && c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            break; // Некорректный символ
        }

        if (digit >= base) break; // Цифра недопустима в этой системе

        result = result * base + digit;
        str++;
    }

    return is_negative ? -(long long)result : (long long)result;
}

// Перевод из десятичной в заданную систему счисления %Cv/%CV
static int handle_cv(const char **format, va_list args, char *buffer) {
    int is_upper = 0;
    if ((*format)[0] == 'C' && (*format)[1] == 'V') {
        is_upper = 1;
    }
    (*format) += 2;

    int num = va_arg(args, int);
    int base = va_arg(args, int);

    return convert_to_base(num, base, is_upper, buffer);
}

// Перевод в десятичную %to / %TO 
static int handle_to(const char **format, va_list args, char *buffer) {
    int is_upper = 0;
    if ((*format)[0] == 'T' && (*format)[1] == 'O') {
        is_upper = 1;
    }
    (*format) += 2;

    const char *str = va_arg(args, const char *);
    int base = va_arg(args, int);

    long long result = convert_from_base(str, base, is_upper);
    return sprintf(buffer, "%lld", result);
}
//Дампы памяти
static int handle_memory_dump(const char **format, va_list args, char *buffer){

    char spec = (*format)[1];
    (*format) += 2;
    
    char *p = buffer;
    
    if(spec == 'i'){
        int value = va_arg(args, int);
        unsigned char *bytes = (unsigned char*)&value; //указатель на iый "блочок" памяти числа value
        for (int i = 0; i < 4; i++){
            if (i > 0) *p++ = ' ';
            byte_to_binary(bytes[i], p);
            p += 8;
        }
    }
    else if (spec == 'u'){
        unsigned int value = va_arg(args, unsigned int);
        unsigned char *bytes = (unsigned char*)&value;
        for (int i = 0; i < 4; i++){
            if (i > 0) *p++ = ' ';
            byte_to_binary(bytes[i], p);
            p += 8;
        }
    }
    else if (spec == 'd'){
        double value = va_arg(args, double);
        unsigned char *bytes = (unsigned char*)&value;
        for (int i = 0; i < 8; i++){
            if (i > 0) *p++ = ' ';
            byte_to_binary(bytes[i], p);
            p += 8;
        }
    }
    else if (spec == 'f'){
        double value = va_arg(args, double);
        float fvalue = (float)value;
        unsigned char *bytes = (unsigned char*)&fvalue;
        for (int i = 0; i < 4; i++){
            if (i > 0) *p++ = ' ';
            byte_to_binary(bytes[i], p);
            p += 8;
        }
    }
    
    *p = '\0';
    return p - buffer;
}

int handle_custom_specifier(const char **format, va_list args, char *buffer){

    const char *p = *format;
    
    if(p[0] == 'R' && p[1] == 'o'){
        *format += 2;
        return handle_rim(args, buffer);
    }
    else if (p[0] == 'Z' && p[1] == 'r'){
        *format += 2;
        return handle_zeckendorf(args, buffer);
    }
    else if (p[0] == 'C' && (p[1] == 'v' || p[1] == 'V')){
        return handle_cv(format, args, buffer);
    }
    else if (p[0] == 't' && p[1] == 'o'){
        return handle_to(format, args, buffer);
    }
    else if (p[0] == 'T' && p[1] == 'O'){
        return handle_to(format, args, buffer);
    }
    else if (p[0] == 'm' && (p[1] == 'i' || p[1] == 'u' || p[1] == 'd' || p[1] == 'f')){
        return handle_memory_dump(format, args, buffer);
    }
    
    return 0;
}



#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include "../include/errors.h"

#define MAX_ERRNO 140

char *strerror(int errnum){
    if (errnum < 0 || errnum > MAX_ERRNO){
        return "Unknown error";
    }

    return (char *)(error_messages[errnum]);
}

void *memchr(const void *str, int c, size_t n){

    const unsigned char *str1 = (const unsigned char*)str;
    unsigned char newc = (unsigned char)c;

    for(size_t i = 0; i < n; i++){
        if(str1[i] == newc){
            return (void *)(str1 + i);
        }
    }
    return NULL;
}

int memcmp(const void *str1, const void *str2, size_t n){
    const unsigned char *str11 = (const unsigned char *)str1;
    const unsigned char *str22 = (const unsigned char *)str2;

    for(size_t i = 0; i < n; i++){
        if(str11[i] != str22[i]){
            return str11[i] - str22[i];
        }
    }
    return 0;
}

void *memcpy(void *dest, const void *src, size_t n){
    const char *src1 = (const char *)src;
    char *dest1 = (char *)dest;

    for(size_t i = 0; i < n; i++){
        dest1[i] = src1[i]; 
    }
    return dest;
}

void *memset(void *str, int c, size_t n){
    unsigned char *str1 = (unsigned char *)str;
    unsigned char newc = (unsigned char)c;
    for(size_t i = 0; i < n; i++){
        str1[i] = newc;
    }
    return str;

}

char *strncat(char *dest, const char *src, size_t n){
    char *d = dest;

    while(*d != '\0'){
    }
    for(size_t i = 0; i < n && src[i] != '\0'; i++ ){
        *d = src[i];
        d++;
    }
    *d = '\0';
    return dest;
}

char *strchr(const char *str, int c){
    char newc = (char)c;
    while(*str != '\0'){
        if(*str == newc){
            return (char *)str;
        }
        str++;
    }

    if(newc == '\0'){
        return (char *)str;
    }
    
    return NULL;
}

int strncmp(const char *str1, const char *str2, size_t n){
    for(size_t i = 0; i < n; i++){
        unsigned char str11 = str1[i];
        unsigned char str22 = str2[i];

        if(str11 != str22){
            return str11 - str22;
        }

        if (str11 == '\0'){
            return 0;
        }
    }
    return 0;
}

char *strncpy(char *dest, const char *src, size_t n){
    size_t i;
    for(i = 0; i < n && src[i] != '\0'; i++){
        dest[i] = src[i];
    }
    for( ; i < n; i++){
        dest[i] = '\0';
    }
    return dest;
}

size_t strcspn(const char *str1, const char *str2){
    size_t count = 0;
    for(size_t i = 0; str1[i] != '\0'; i++){
        for(size_t j = 0; str2[j] != '\0'; j++){
            if(str1[i] == str2[j]){
                return count;
            }
        }
        count++;
    }
    return count;
}

size_t strlen(const char *str){
    size_t count = 0;
    for(size_t i = 0; str[i] != '\0'; i++){
        count++;
    }
    return count;
}

char *strpbrk(const char *str1, const char *str2){
    for(size_t i = 0; str1[i] != '\0'; i++){
        for(size_t j = 0; str2[j] != '\0'; j++){
            if(str1[i] == str2[j]){
                return (char *)(str1 + i);
            }
        }
    }
    return NULL;
}

char *strrchr(const char *str, int c){
    const char *str1 = str;
    const char *last = NULL;
    char newc = (char)c;
    
    while(*str1 != '\0'){
        if(*str1 == newc){
            last = str1;
        }
        str1++;
    }
    
    if (newc == '\0') {
        return (char *)str1;
    }
    
    return (char *)last;
}

char *strstr(const char *haystack, const char *needle){
    if(*needle == '\0') return (char *)haystack;
    
    for(size_t i = 0; haystack[i] != '\0'; i++){
        int flag = 1;
        if(haystack[i] == needle[0]){
            for(size_t j = 1; needle[j] != '\0'; j++){
                if(haystack[i + j] != needle[j]){
                    flag = 0;
                    break;
                }
            }
            if(flag == 1) return (char *)(haystack + i);
        }
    }
    return NULL;
}

// Разделитель
static int delimiter(char c, const char *delim){
    const char *d = delim;
    while(*d != '\0'){
        if(c == *d){
            return 1;
        }
        d++;
    }
    return 0;
}

char *strtok(char *str, const char *delim){
    static char *saved = NULL;
    char *start;
    
    if(str != NULL){
        saved = str;
    }
    
    if(saved == NULL || *saved == '\0'){
        return NULL;
    }
    
    start = saved;
    while(*start != '\0' && delimiter(*start, delim)) {
        start++;
    }
    
    if(*start == '\0'){
        saved = NULL;
        return NULL;
    }
    
    char *end = start;
    while(*end != '\0' && !delimiter(*end, delim)) {
        end++;
    }
    
    if(*end == '\0'){
        saved = NULL;
    }
    else{
        *end = '\0';
        saved = end + 1;
    }
    
    return start;
}
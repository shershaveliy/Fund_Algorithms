#include <stdio.h>
#include <string.h>
#include "include/file.h"

int main() {
    
    printf("strlen: %zu %zu\n", strlen("hello"), strlen(""));
    
    char str1[] = "Hello World";
    printf("memchr: %s\n", memchr(str1, 'W', 11) ? "Found" : "NULL");
    
    char a1[] = "abc", a2[] = "abd";
    printf("memcmp: %d\n", memcmp(a1, a2, 3));
    
    char src[] = "Source", dest[20];
    memcpy(dest, src, 7);
    printf("memcpy: %s\n", dest);
    
    char buf[10];
    memset(buf, 'A', 5);
    buf[5] = '\0';
    printf("memset: %s\n", buf);
    
    char dest1[20] = "Hello";
    strncat(dest1, " World", 6);
    printf("strncat: %s\n", dest1);
    
    printf("strchr: %s\n", strchr("Hello", 'e') ? "Found" : "NULL");
    
    printf("strncmp: %d\n", strncmp("abc", "abd", 2));
    
    char dest2[10];
    strncpy(dest2, "Hello", 5);
    dest2[5] = '\0';
    printf("strncpy: %s\n", dest2);
    
    printf("strcspn: %zu\n", strcspn("hello", "eo"));
    
    printf("strpbrk: %s\n", strpbrk("Hello World", "or") ? "Found" : "NULL");
    
    printf("strrchr: %s\n", strrchr("Hello World", 'o') ? "Found" : "NULL");
    
    printf("strstr: %s\n", strstr("Hello World", "World") ? "Found" : "NULL");
    
    char text[] = "apple,banana;orange test";
    printf("strtok: ");
    char *token = strtok(text, ",; ");
    while (token != NULL) {
        printf("%s ", token);
        token = strtok(NULL, ",; ");
    }
    printf("\n");
    
    printf("Edge: %d %zu\n", memcmp("a", "a", 0), strlen(""));
    
    return 0;
}
# Фунды ЛР-2
```c
// Реализация strstr.
#include <stdio.h>

char * my_strstr(const char * haystack, const char[]needle){//Одно и то же

    // Проверка на пустую подстроку
    if (*needle == '\0') {
        return (char *)haystack;
    }
    
    // Проходим по всей строке
    while (*haystack != '\0') {
        const char *h = haystack;
        const char *n = needle;
        
        // Сравниваем символы пока они совпадают
        while (*h != '\0' && *n != '\0' && *h == *n) {
            h++;
            n++;
        }
        
        // Если дошли до конца needle - подстрока найдена
        if (*n == '\0') {
            return (char *)haystack;
        }
        
        // Если needle не найден, переходим к следующему символу в haystack
        haystack++;
    }
    
    return NULL;
}

```
```c
// Функции можно передавать как аргументы.
int sign(int a){
    if(a > 0) return 1;
    if(a < 0 ) return -1;
    return 0; 
}

int my_sqrt(int a){
    return (int)aqrt(a);
}

int math1(int x, int(*func)(int)){
    return  func(x);
}

int main(){
    int x = 0;
    int (*operations[2])(int) = {sign, my_sqrt};
    for( int i = 0, i < 2, i++){
        res = math1(x, operations[i]);
        printf("%d", res);
    }
    return 0;
}
```
```c
#include <stdarg.h>

int Find_max(int count, ... ){
    if(count <= 0) return INT_MIN;
    va_list args; // новый тип данных
    va_start(args, count);
    int max = va_arg(args, int);

    for(int i = 0; i < count; i++){
        int cur = va_arg(args, int);
        if(cur > max) max = cur;
    }
    va_end(args);
    return max;
}
```
# Фунды ЛР-1

```

int i  5;

printf("%d%d%d", i--, i, i++); // Какая-то фигня, не прописана стандартом. В зависимости от компилятора будут выводиться разные значения. Так делать нельзя.

```

В языке Си всего 7 структур. 

```
Вывести сумму чисел от 1 до n.

#include <stdio.h>

int main(void) {
    int n = 0, sum = 0; // Почему лучше сделать так, а не оставить просто int n?
    scanf("%d", &n);
    for (int i = 1; i<=n; i++){
        sum += i
    }
    printf("%d", sum);
    return 0;
}
```
for( ; ; ){...} Отработает нормально

если будет слишком большое n будет переполнение
```
Является ли число простым

#include <stdio.h>
#include <stdbool.h>
// Нужна для использования корня, но мы тут его использовать не будем, поэтому не пишем #include <math.h>

bool isPrime(int n){
    if(n == 2){
        return true; //if сработает и без скобок, потому что одно условие
    }

    if(n % 2 == 0){
        return false;
    }

    for(int i = 3; i * i < n, i+=2){
        if( n % i == 0){
            return false;
        }
    }
    return true;
}

int main(void){

    int n = 0;
    scanf("%d", &n);
    bool is_prime = isPrime;

    if(is_prime){
        printf("Это простое число");
    }
    else{
        printf("Это не простое число");
    }

    return 0;
}
```

## Указатели
В Си в функцию переменные передаются по значению, а не по ссылке. Указатели решают эту проблему. 

```
Функция по обмену значений двух переменных

void swap( int *a, int *b){
    int tmp;
    tmp = *a; //в tmp записываем значение a
    *a = *b;
    *b = tmp;
}

int main(){
    int a = 0, b = 0;
    scanf("%d%d", &a, &b);
    swap(&a, &b);
    return 0;
}
```

## Массивы
```
Найти минимальный элемент в статическом массиве

#include <stdio.h>

int main(void){

    int arr[5]; //Способ задания массива. Если не указана длина, память не выделится, не скомпилируется

    printf("%d", arr[0]); //Выведется мусор тк не инециированны значения в массиве, но если int arr[5] = {}; то выведутся нули, arr[5] = {3, 5, } выведется 3,5,0,0,0. arr[5] = {[5] = 4} ...
    
    return 0;
}

int main(void){

    int n, int arr[n] = {}; Что произойдет в зависимости от разных стандартов в Си.

    printf("%d", arr[0]);
    return 0;
}
```
```
#include <stdio.h>

int main(void){

    int arr[] = {1, 2, 5, -3, 0};
    int min = arr[0]; // arr[n] эквивалентно *(arr+n)
    int n = 5;
    for( int i=1; i < n, i++){ // Что не так с sizeof?
        if(min > arr[i]){
            min = arr[i];
        }
    }
    return 0;
}
```
```
Развернуть массив

#include <stdio.h>

void reverseArray(int *array, int n){
    for( int i = 0, i = n / 2, i++){
        imp = array[i];
        array[i] = array[n-i-1];
        array[n-i-1] = tmp;
    }
}

int main(){
    int n = 10;
    int arr[10] = {};
    reverseArray(array,n);
    return 0;
}
```
## Строки

```
#include <stdio.h>

int main(void){
    char str[3];
    str[0] = 'a';
    str[1] = 'v';
    str[2] = '\0' // Обезательно должен быть терминирующий символ
    char str[] = "Hello";
}
```
```
#include <stdio.h>

int main(void){
    char str[] = "Hello";
    int len = 0;
    char *ptr =str;
    while(*ptr != '\0'){
        ptr++;
        len++;
    }
    return 0;
}
```
## Динамическое выделение памяти

#include <stdlib.h>

malloc возвращает указатель на воид

```
#include <stdio.h>
#include <stdlib.h>

void FillSguare(int *arr, size_t size){
    for(int i = 0; i < size; i++){
        *(arr + i) = i * i;
    }
}

int main(void){
    int n = 0;
    scanf(%d", &n);
    int *p = (int*)malloc(sizeof(int)*n); // мы так пишем, потому что в разных системах разные размеры переменных поэтому sizeof
    if(p = NULL){
        return -1;
    }
    FillSguare(p, n);
    for(int i = 0; i < n; ++i){
        printf("%d", *(p+i));
    }
    Free(p);
    return 0;
}
```
```
Считывание строки и запись ее в память

#include <stdio.h>
#include <stdlib.h>

#define BUFFER 10

char * readLine(){
    char *c = getchar();
    size_t size = BUFFER;
    char *p = (char *)malloc(BUFFER * sizeof(char));
    if(!p){
        return NULL;
    }
    while((c != \n) && (c != EOF)){
        *(p+n) = c;
        ++n;
        c = getchar();
        if (n==BUFFER){
            size += 2;
            char * p = (char *)realloc(p, n * 2);
        }
    
    }
    if (!p){
        return NULL;
    }
}

int main(void){

    return 0;
}
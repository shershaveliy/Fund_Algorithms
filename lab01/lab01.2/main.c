#include <stdio.h>
#include <stdlib.h>
#include "prime.h"

int main() {
    int v;
    printf("Введите количество запросов: ");
    scanf("%d", &v);
    if(v <= 0){
        printf("Введите определенное количество запросов.\n");
        return 1;
    }
    
    int *input = (int*)malloc(v * sizeof(int));
    int *output = (int*)malloc(v * sizeof(int));
    
    printf("Введите порядковые номера искомых простых чисел: \n");
    for (int i = 0; i < v; i++) {
        scanf("%d", &input[i]);
        if(input[i] < 1){
            printf("Порядковый номер всегда больше нуля\n");
            return 1;
        }
    }
    
    for (int i = 0; i < v; i++) {
        output[i] = find_prime(input[i]);
    }
    printf("\nРезультат поиска: \n");
    for (int i = 0; i < v; i++) {
        printf("%d\n", output[i]);
    }
    
    free(input);
    free(output);
    
    return 0;
}
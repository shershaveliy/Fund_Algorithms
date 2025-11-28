#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/heap.h"

DEFINE_HEAP(char*)

static char* string_copy(char* str){
    if (!str) return NULL;
    size_t len = strlen(str);
    char* copy = (char*)malloc(len + 1);
    if (copy) {
        strcpy(copy, str);
    }
    return copy;
}

static void string_free(char* str){
    free(str);
}

static int string_compare(char* a, char* b){
    return strcmp(a, b);
}

static void print_string_heap(const Heap* h, const char* title) {
    printf("%s: [", title);
    for (size_t i = 0; i < h->count; i++) {
        printf("\"%s\"", h->items[i]);
        if (i < h->count - 1) printf(", ");
    }
    printf("] (размер=%zu)\n", h->count);
}

static void test_string_operations(){
    printf("=== Тест 1: Базовые операции со строками ===\n");
    
    Heap h = heap_create(3, string_copy, string_free, string_compare);
    
    // Добавляем строки в произвольном порядке
    char* fruits[] = {"apple", "banana", "orange", "grape", "kiwi"};
    for (int i = 0; i < 5; i++) {
        heap_push(&h, fruits[i]);
        printf("Добавлен: \"%s\". Минимальный: \"%s\"\n", fruits[i], heap_top(&h));
    }
    
    print_string_heap(&h, "Куча после добавления всех строк");
    
    // Извлекаем строки в лексикографическом порядке
    printf("Извлекаем строки по порядку:\n");
    while (!heap_empty(&h)) {
        char* str = heap_pop(&h);
        printf("  \"%s\"\n", str);
        string_free(str); // Освобождаем строку после извлечения
    }
    
    heap_destroy(&h);
    printf("Тест пройден\n\n");
}

// Тест построения кучи из массива строк
static void test_build_string_heap(){
    printf("=== Тест 2: Построение кучи из массива строк ===\n");
    
    char* names[] = {"Peter", "Anna", "Ivan", "Maria", "Alexey"};
    printf("Исходный массив строк: [");
    for (int i = 0; i < 5; i++) {
        printf("\"%s\"%s", names[i], i < 4 ? ", " : "");
    }
    printf("]\n");
    
    Heap h = heap_build(names, 5, string_copy, string_free, string_compare);
    print_string_heap(&h, "Построенная куча");
    
    printf("Первая строка в лексикографическом порядке: \"%s\"\n", heap_top(&h));
    heap_destroy(&h);
    printf("Тест пройден\n\n");
}

// Тест с одинаковыми строками
static void test_duplicate_strings() {
    printf("=== Тест 3: Работа с одинаковыми строками ===\n");
    
    Heap h = heap_create(5, string_copy, string_free, string_compare);
    
    char* words[] = {"cat", "dog", "cat", "bird", "dog"};
    for (int i = 0; i < 5; i++) {
        heap_push(&h, words[i]);
    }
    
    print_string_heap(&h, "Куча с дубликатами");
    
    printf("Извлекаем уникальные строки:\n");
    char* prev = NULL;
    while (!heap_empty(&h)) {
        char* current = heap_pop(&h);
        if (!prev || strcmp(current, prev) != 0) {
            printf("  \"%s\"\n", current);
        }
        if (prev) string_free(prev);
        prev = current;
    }
    if (prev) string_free(prev);
    
    heap_destroy(&h);
    printf("Тест пройден\n\n");
}

int main() {
    printf("========== ТЕСТИРОВАНИЕ КУЧИ ДЛЯ СТРОК ==========\n\n");
    
    test_string_operations();
    test_build_string_heap();
    test_duplicate_strings();
    
    printf("========== ВСЕ ТЕСТЫ ПРОЙДЕНЫ ==========\n");
    return 0;
}
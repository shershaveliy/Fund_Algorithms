#include <stdio.h>
#include <stdlib.h>
#include "../include/heap.h"

DEFINE_HEAP(int)

static int int_compare(int a, int b){
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

static void print_int_heap(const Heap* h, const char* title){
    printf("%s: [", title);
    for (size_t i = 0; i < h->count; i++) {
        printf("%d", h->items[i]);
        if (i < h->count - 1) printf(", ");
    }
    printf("] (размер=%zu, вместимость=%zu)\n", h->count, h->max_count);
}

// Тест создания и проверки пустоты
static void test_create_and_empty(){
    printf("=== Тест 1: Создание и проверка пустоты ===\n");
    Heap h = heap_create(5, NULL, NULL, int_compare);
    print_int_heap(&h, "Новая куча");
    printf("Куча пуста? %s\n", heap_empty(&h) ? "Да" : "Нет");
    heap_destroy(&h);
    printf("Тест пройден\n\n");
}

// Тест добавления элементов
static void test_push_and_peek(){
    printf("=== Тест 2: Добавление элементов и просмотр вершины ===\n");
    Heap h = heap_create(3, NULL, NULL, int_compare);
    
    int values[] = {5, 2, 8, 1, 4};
    for (int i = 0; i < 5; i++) {
        heap_push(&h, values[i]);
        printf("Добавлен %d. Вершина: %d\n", values[i], heap_top(&h));
    }
    
    print_int_heap(&h, "Куча после добавления 5 элементов");
    heap_destroy(&h);
    printf("Тест пройден\n\n");
}

// Тест извлечения элементов
static void test_pop() {
    printf("=== Тест 3: Извлечение элементов ===\n");
    Heap h = heap_create(10, NULL, NULL, int_compare);
    
    int values[] = {10, 5, 15, 3, 7, 12, 1};
    for (int i = 0; i < 7; i++) {
        heap_push(&h, values[i]);
    }
    
    print_int_heap(&h, "Исходная куча");
    
    printf("Извлекаем элементы по порядку: ");
    while (!heap_empty(&h)) {
        printf("%d ", heap_pop(&h));
    }
    printf("\n");
    
    heap_destroy(&h);
    printf("Тест пройден\n\n");
}

// Тест построения кучи из массива
static void test_build_heap() {
    printf("=== Тест 4: Построение кучи из массива ===\n");
    
    int array[] = {9, 3, 7, 1, 5, 11, 2};
    printf("Исходный массив: [");
    for (int i = 0; i < 7; i++) {
        printf("%d%s", array[i], i < 6 ? ", " : "");
    }
    printf("]\n");
    
    Heap h = heap_build(array, 7, NULL, NULL, int_compare);
    print_int_heap(&h, "Построенная куча");
    
    printf("Минимальный элемент: %d\n", heap_top(&h));
    heap_destroy(&h);
    printf("Тест пройден\n\n");
}

// Тест сравнения куч
static void test_heap_equals(){
    printf("=== Тест 5: Сравнение куч ===\n");
    
    int arr1[] = {1, 3, 5};
    int arr2[] = {1, 3, 5};
    int arr3[] = {1, 4, 5};
    
    Heap h1 = heap_build(arr1, 3, NULL, NULL, int_compare);
    Heap h2 = heap_build(arr2, 3, NULL, NULL, int_compare);
    Heap h3 = heap_build(arr3, 3, NULL, NULL, int_compare);
    
    print_int_heap(&h1, "Куча h1");
    print_int_heap(&h2, "Куча h2");
    print_int_heap(&h3, "Куча h3");
    
    printf("h1 == h2? %s\n", heap_equals(&h1, &h2) ? "Да" : "Нет");
    printf("h1 == h3? %s\n", heap_equals(&h1, &h3) ? "Да" : "Нет");
    
    heap_destroy(&h1);
    heap_destroy(&h2);
    heap_destroy(&h3);
    printf("Тест пройден\n\n");
}

int main() {
    printf("========== ТЕСТИРОВАНИЕ КУЧИ ДЛЯ INT ==========\n\n");
    
    test_create_and_empty();
    test_push_and_peek();
    test_pop();
    test_build_heap();
    test_heap_equals();
    
    printf("========== ВСЕ ТЕСТЫ ПРОЙДЕНЫ ==========\n");
    return 0;
}
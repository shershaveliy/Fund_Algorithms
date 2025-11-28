#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/heap.h"

// Структура для тестирования
typedef struct{
    int id;
    char name[20];
    int priority;
} Task;

DEFINE_HEAP(Task)

// Функция копирования структуры Task
static Task task_copy(const Task t){
    Task copy;
    copy.id = t.id;
    copy.priority = t.priority;
    strcpy(copy.name, t.name);
    return copy;
}

// Функция сравнения задач по приоритету
static int task_compare(Task a, Task b){
    return a.priority - b.priority;
}

// Функция для печати задачи
static void print_task(Task t){
    printf("Task {id=%d, name=\"%s\", priority=%d}", t.id, t.name, t.priority);
}

// Функция для печати кучи задач
static void print_task_heap(const Heap* h, const char* title){
    printf("%s:\n", title);
    for (size_t i = 0; i < h->count; i++){
        printf("  [%zu] ", i);
        print_task(h->items[i]);
        printf("\n");
    }
    printf("  Размер: %zu\n", h->count);
}

static void test_struct_operations(){
    printf("=== Тест 1: Базовые операции со структурами ===\n");
    
    Heap h = heap_create(5, task_copy, NULL, task_compare);
    
    // Создаем задачи с разными приоритетами
    Task tasks[] = {
        {1, "Memory cleanup", 3},
        {2, "Rendering", 1},
        {3, "Data loading", 2},
        {4, "Network connection", 5},
        {5, "Input processing", 4}
    };
    
    // Добавляем задачи в кучу
    for (int i = 0; i < 5; i++){
        heap_push(&h, tasks[i]);
        printf("Добавлена: ");
        print_task(tasks[i]);
        printf(". Задача с высшим приоритетом: ");
        print_task(heap_top(&h));
        printf("\n");
    }
    
    print_task_heap(&h, "Куча после добавления всех задач");
    
    // Выполняем задачи в порядке приоритета
    printf("Выполняем задачи по приоритету:\n");
    while (!heap_empty(&h)) {
        Task next_task = heap_pop(&h);
        printf("  Выполняется: ");
        print_task(next_task);
        printf("\n");
    }
    
    heap_destroy(&h);
    printf("Тест пройден\n\n");
}

// Тест с одинаковыми приоритетами
static void test_same_priority(){
    printf("=== Тест 2: Задачи с одинаковым приоритетом ===\n");
    
    Heap h = heap_create(5, task_copy, NULL, task_compare);
    
    Task tasks[] = {
        {1, "Task A", 2},
        {2, "Task B", 1},
        {3, "Task C", 2},
        {4, "Task D", 1},
        {5, "Task E", 3}
    };
    
    for (int i = 0; i < 5; i++) {
        heap_push(&h, tasks[i]);
    }
    
    print_task_heap(&h, "Куча с одинаковыми приоритетами");
    
    printf("Порядок выполнения:\n");
    while (!heap_empty(&h)) {
        Task t = heap_pop(&h);
        printf("  ");
        print_task(t);
        printf("\n");
    }
    
    heap_destroy(&h);
    printf("Тест пройден\n\n");
}

// Тест построения кучи из массива структур
static void test_build_struct_heap(){
    printf("=== Тест 3: Построение кучи из массива структур ===\n");
    
    Task tasks[] = {
        {10, "Backup", 4},
        {11, "Log analysis", 1},
        {12, "System update", 3},
        {13, "Security check", 2},
        {14, "Reporting", 5}
    };
    
    printf("Исходный массив задач:\n");
    for (int i = 0; i < 5; i++) {
        printf("  ");
        print_task(tasks[i]);
        printf("\n");
    }
    
    Heap h = heap_build(tasks, 5, task_copy, NULL, task_compare);
    print_task_heap(&h, "Построенная куча задач");
    
    printf("Задача с наивысшим приоритетом: ");
    print_task(heap_top(&h));
    printf("\n");
    
    heap_destroy(&h);
    printf("Тест пройден\n\n");
}

int main() {
    printf("========== ТЕСТИРОВАНИЕ КУЧИ ДЛЯ СТРУКТУР ==========\n\n");
    
    test_struct_operations();
    test_same_priority();
    test_build_struct_heap();
    
    printf("========== ВСЕ ТЕСТЫ ПРОЙДЕНЫ ==========\n");
    return 0;
}
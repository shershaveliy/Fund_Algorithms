#include "../include/vector.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

DEFINE_VECTOR(char*)

// Функции для глубокого копирования и удаления строк
char* copy_string(char* str){
    if (str == NULL) return NULL;
    size_t len = strlen(str) + 1;
    char* copy = (char*)malloc(len);
    if (copy) {
        strcpy(copy, str);
    }
    return copy;
}

void delete_string(char* str){
    free(str);
}

int compare_string(char* str1, char* str2){
    if (str1 == NULL && str2 == NULL) return 0;
    if (str1 == NULL) return -1;
    if (str2 == NULL) return 1;
    return strcmp(str1, str2);
}

void test_create_and_push_string();
void test_get_and_delete_string();
void test_copy_and_compare_string();
void test_copy_vector_new_string();
void test_erase_and_delete_string();
void test_string_operations();

int main(void){
    printf("=== Тестирование вектора<string> ===\n\n");

    test_create_and_push_string();
    test_get_and_delete_string();
    test_copy_and_compare_string();
    test_copy_vector_new_string();
    test_erase_and_delete_string();
    test_string_operations();

    printf("=== Все тесты для string завершены успешно! ===\n");
    return 0;
}

void test_create_and_push_string() {
    printf("[TEST 1] Создание и добавление элементов\n");

    Vector v = create_vector_with_comparator(2, copy_string, delete_string, compare_string);
    printf("Создан вектор: capacity=%zu, size=%zu\n", v.capacity, v.size);

    push_back_vector(&v, "Hello");
    push_back_vector(&v, "World");
    push_back_vector(&v, "Test");
    push_back_vector(&v, "String");
    push_back_vector(&v, "Vector");

    printf("После добавлений: size=%zu, capacity=%zu\n", v.size, v.capacity);
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = '%s'\n", i, get_at_vector(&v, i));
    }

    assert(v.size == 5);
    assert(strcmp(get_at_vector(&v, 0), "Hello") == 0);
    assert(strcmp(get_at_vector(&v, 4), "Vector") == 0);

    delete_vector(&v);
    printf("Завершено\n\n");
}

void test_get_and_delete_string() {
    printf("[TEST 2] Получение и удаление элементов\n");

    Vector v = create_vector_with_comparator(0, copy_string, delete_string, compare_string);
    
    push_back_vector(&v, "Apple");
    push_back_vector(&v, "Banana");
    push_back_vector(&v, "Cherry");
    push_back_vector(&v, "Date");
    push_back_vector(&v, "Elderberry");

    printf("Исходный вектор: ");
    for (size_t i = 0; i < v.size; i++) printf("'%s' ", get_at_vector(&v, i));
    printf("\n");

    printf("Элемент с индексом 2: '%s'\n", get_at_vector(&v, 2));
    
    // Для несуществующего индекса получаем NULL
    char* result = get_at_vector(&v, 99);
    printf("Элемент с несуществующим индексом (99): '%s'\n", result == NULL ? "NULL" : result);

    assert(strcmp(get_at_vector(&v, 2), "Cherry") == 0);
    assert(get_at_vector(&v, 99) == NULL);

    printf("Удаляем элемент с индексом 1...\n");
    delete_at_vector(&v, 1);

    printf("После удаления: ");
    for (size_t i = 0; i < v.size; i++) printf("'%s' ", get_at_vector(&v, i));
    printf("\n");

    assert(v.size == 4);
    assert(strcmp(get_at_vector(&v, 1), "Cherry") == 0);

    delete_vector(&v);
    printf("Завершено\n\n");
}

void test_copy_and_compare_string() {
    printf("[TEST 3] Копирование и сравнение векторов\n");

    Vector v1 = create_vector_with_comparator(0, copy_string, delete_string, compare_string);
    push_back_vector(&v1, "First");
    push_back_vector(&v1, "Second");
    push_back_vector(&v1, "Third");

    Vector v2 = create_vector_with_comparator(0, copy_string, delete_string, compare_string);
    copy_vector(&v2, &v1);

    printf("v1: ");
    for (size_t i = 0; i < v1.size; i++) printf("'%s' ", get_at_vector(&v1, i));
    printf("\nv2: ");
    for (size_t i = 0; i < v2.size; i++) printf("'%s' ", get_at_vector(&v2, i));
    printf("\n");

    int are_equal = is_equal_vector(&v1, &v2);
    printf("Равны ли v1 и v2? %s\n", are_equal ? "Да" : "Нет");

    // Проверка равенства (должны быть равны, так как строки одинаковые)
    assert(are_equal == 1);

    push_back_vector(&v2, "Extra");
    printf("Добавили 'Extra' в v2.\n");
    are_equal = is_equal_vector(&v1, &v2);
    printf("Теперь равны? %s\n", are_equal ? "Да" : "Нет");

    assert(are_equal == 0);

    delete_vector(&v1);
    delete_vector(&v2);
    printf("Завершено\n\n");
}

void test_copy_vector_new_string() {
    printf("[TEST 4] Копирование с созданием нового вектора\n");

    Vector v = create_vector_with_comparator(0, copy_string, delete_string, compare_string);
    
    push_back_vector(&v, "Alpha");
    push_back_vector(&v, "Beta");
    push_back_vector(&v, "Gamma");
    push_back_vector(&v, "Delta");
    
    printf("Создан новый вектор v:\n");
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = '%s'\n", i, get_at_vector(&v, i));
    }

    Vector *v_copy = copy_vector_new(&v);
    assert(v_copy != NULL);
    
    printf("Создан новый вектор v_copy:\n");
    for (size_t i = 0; i < v_copy->size; i++) {
        printf("  v_copy[%zu] = '%s'\n", i, get_at_vector(v_copy, i));
    }

    assert(is_equal_vector(&v, v_copy) == 1);
    assert(v_copy->size == v.size);
    
    // Проверяем, что это действительно глубокое копирование
    // (изменение оригинала не должно влиять на копию)
    char* original_first = get_at_vector(&v, 0);
    char* copy_first = get_at_vector(v_copy, 0);
    assert(original_first != copy_first);
    assert(strcmp(original_first, copy_first) == 0);

    delete_vector(&v);
    free_vector(v_copy);

    printf("Завершено\n\n");
}

void test_erase_and_delete_string(){
    printf("[TEST 5] Очистка и удаление\n");

    Vector v = create_vector_with_comparator(0, copy_string, delete_string, compare_string);
    push_back_vector(&v, "One");
    push_back_vector(&v, "Two");
    push_back_vector(&v, "Three");

    printf("Перед очисткой: size=%zu, capacity=%zu\n", v.size, v.capacity);
    
    assert(get_at_vector(&v, 0) != NULL);
    assert(get_at_vector(&v, 1) != NULL);
    assert(get_at_vector(&v, 2) != NULL);
    
    erase_vector(&v);
    printf("После erase_vector: size=%zu, capacity=%zu\n", v.size, v.capacity);

    assert(v.size == 0);
    assert(v.capacity == 0);
    assert(v.data == NULL);

    delete_vector(&v);
    printf("Завершено\n\n");
}

void test_string_operations(){
    printf("[TEST 6] Дополнительные операции со строками\n");

    Vector v = create_vector_with_comparator(0, copy_string, delete_string, compare_string);
    push_back_vector(&v, "Short");
    push_back_vector(&v, "Medium length string");
    push_back_vector(&v, "Very long string with many characters and spaces");
    push_back_vector(&v, "");
    push_back_vector(&v, "Special chars: !@#$%^&*()");
    
    printf("Строки разного типа:\n");
    for (size_t i = 0; i < v.size; i++) {
        char* str = get_at_vector(&v, i);
        printf("  v[%zu] = '%s' (length: %zu)\n", i, str, strlen(str));
    }
    
    assert(strcmp(get_at_vector(&v, 0), "Short") == 0);
    assert(strcmp(get_at_vector(&v, 1), "Medium length string") == 0);
    assert(strcmp(get_at_vector(&v, 3), "") == 0);
    assert(strlen(get_at_vector(&v, 3)) == 0);
    
    delete_at_vector(&v, 1);
    assert(v.size == 4);
    assert(strcmp(get_at_vector(&v, 1), "Very long string with many characters and spaces") == 0);
    
    push_back_vector(&v, "New string");
    assert(v.size == 5);
    assert(strcmp(get_at_vector(&v, 4), "New string") == 0);
    
    delete_vector(&v);
    printf("Завершено\n\n");
}
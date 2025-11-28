#include "../include/vector.h"
#include <stdio.h>
#include <assert.h>

DEFINE_VECTOR(int)

int copy_int(int value){
    return value;
}

void delete_int(int value){
    (void)value;
}

void test_create_and_push_int();
void test_get_and_delete_int();
void test_copy_and_compare_int();
void test_copy_vector_new_int();
void test_erase_and_delete_int();
void test_edge_cases_int();

int main(void){
    printf("=== Тестирование вектора<int> ===\n\n");

    test_create_and_push_int();
    test_get_and_delete_int();
    test_copy_and_compare_int();
    test_copy_vector_new_int();
    test_erase_and_delete_int();
    test_edge_cases_int();

    printf("=== Все тесты для int завершены успешно! ===\n");
    return 0;
}

//Создание и добавление элементов
void test_create_and_push_int(){
    printf("[TEST 1] Создание и добавление элементов\n");

    Vector v = create_vector(2, copy_int, delete_int);
    printf("Создан вектор: capacity=%zu, size=%zu\n", v.capacity, v.size);

    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    push_back_vector(&v, 40);
    push_back_vector(&v, 50);

    printf("После добавлений: size=%zu, capacity=%zu\n", v.size, v.capacity);
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = %d\n", i, get_at_vector(&v, i));
    }

    // Проверки
    assert(v.size == 5);
    assert(v.capacity >= 5);
    assert(get_at_vector(&v, 0) == 10);
    assert(get_at_vector(&v, 4) == 50);

    delete_vector(&v); // Только очищаем содержимое, не освобождаем сам вектор
    printf("Завершено\n\n");
}

//Получение и удаление по индексу
void test_get_and_delete_int(){
    printf("[TEST 2] Получение и удаление элементов\n");

    Vector v = create_vector(0, copy_int, delete_int);
    for (int i = 1; i <= 5; i++) push_back_vector(&v, i * 10);

    printf("Исходный вектор: ");
    for (size_t i = 0; i < v.size; i++) printf("%d ", get_at_vector(&v, i));
    printf("\n");

    printf("Элемент с индексом 2: %d\n", get_at_vector(&v, 2));
    printf("Элемент с несуществующим индексом (99): %d\n", get_at_vector(&v, 99));

    assert(get_at_vector(&v, 2) == 30);
    assert(get_at_vector(&v, 99) == 0);

    printf("Удаляем элемент с индексом 1...\n");
    delete_at_vector(&v, 1);

    printf("После удаления: ");
    for (size_t i = 0; i < v.size; i++) printf("%d ", get_at_vector(&v, i));
    printf("\n");

    assert(v.size == 4);
    assert(get_at_vector(&v, 1) == 30); // Сдвинулось

    delete_vector(&v);
    printf("Завершено\n\n");
}

// Копирование и сравнение векторов
void test_copy_and_compare_int(){
    printf("[TEST 3] Копирование и сравнение векторов\n");

    Vector v1 = create_vector(0, copy_int, delete_int);
    push_back_vector(&v1, 100);
    push_back_vector(&v1, 200);
    push_back_vector(&v1, 300);

    Vector v2 = create_vector(0, copy_int, delete_int);
    copy_vector(&v2, &v1);

    printf("v1: ");
    for (size_t i = 0; i < v1.size; i++) printf("%d ", get_at_vector(&v1, i));
    printf("\nv2: ");
    for (size_t i = 0; i < v2.size; i++) printf("%d ", get_at_vector(&v2, i));
    printf("\n");

    printf("Равны ли v1 и v2? %s\n", is_equal_vector(&v1, &v2) ? "Да" : "Нет");

    assert(is_equal_vector(&v1, &v2) == 1);

    push_back_vector(&v2, 999);
    printf("Добавили 999 в v2.\n");
    printf("Теперь равны? %s\n", is_equal_vector(&v1, &v2) ? "Да" : "Нет");

    assert(is_equal_vector(&v1, &v2) == 0);

    delete_vector(&v1);
    delete_vector(&v2);
    printf("Завершено\n\n");
}

//Копирование с созданием нового вектора
void test_copy_vector_new_int() {
    printf("[TEST 4] Копирование с созданием нового вектора\n");

    Vector v = create_vector(0, copy_int, delete_int);
    for (int i = 1; i <= 4; i++) push_back_vector(&v, i * 25);
    
    printf("Создан новый вектор v:\n");
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = %d\n", i, get_at_vector(&v, i));
    }

    Vector *v_copy = copy_vector_new(&v);
    assert(v_copy != NULL);
    
    printf("Создан новый вектор v_copy:\n");
    for (size_t i = 0; i < v_copy->size; i++) {
        printf("  v_copy[%zu] = %d\n", i, get_at_vector(v_copy, i));
    }

    assert(is_equal_vector(&v, v_copy) == 1);
    assert(v_copy->size == v.size);

    delete_vector(&v);
    free_vector(v_copy);

    printf("Завершено\n\n");
}

// Очистка и удаление
void test_erase_and_delete_int(){
    printf("[TEST 5] Очистка и удаление\n");

    Vector v = create_vector(0, copy_int, delete_int);
    push_back_vector(&v, 314);
    push_back_vector(&v, 271);
    push_back_vector(&v, 141);

    printf("Перед очисткой: size=%zu, capacity=%zu\n", v.size, v.capacity);
    erase_vector(&v);
    printf("После erase_vector: size=%zu, capacity=%zu\n", v.size, v.capacity);

    assert(v.size == 0);
    assert(v.capacity == 0);
    assert(v.data == NULL);

    delete_vector(&v);
    printf("Завершено\n\n");
}

void test_edge_cases_int() {
    printf("[TEST 6] Граничные случаи\n");

    Vector v1 = create_vector(0, copy_int, delete_int);
    assert(v1.capacity == 1); // Должно быть минимум 1
    delete_vector(&v1);

    Vector v2 = create_vector(10, copy_int, delete_int);
    assert(v2.size == 0);
    assert(v2.capacity == 10);
    
    assert(get_at_vector(&v2, 0) == 0);
    
    delete_at_vector(&v2, 0); // Не должно падать
    
    delete_vector(&v2);
    printf("Завершено\n\n");
}
#include "../include/vector.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

DEFINE_VECTOR(double)

double copy_double(double value) {
    return value;
}

void delete_double(double value) {
    (void)value;
}

void test_create_and_push_double();
void test_get_and_delete_double();
void test_copy_and_compare_double();
void test_copy_vector_new_double();
void test_erase_and_delete_double();
void test_precision_double();

int main(void){
    printf("=== Тестирование вектора<double> ===\n\n");

    test_create_and_push_double();
    test_get_and_delete_double();
    test_copy_and_compare_double();
    test_copy_vector_new_double();
    test_erase_and_delete_double();
    test_precision_double();

    printf("=== Все тесты для double завершены успешно! ===\n");
    return 0;
}

/* === Создание и добавление элементов === */
void test_create_and_push_double() {
    printf("[TEST 1] Создание и добавление элементов\n");

    Vector v = create_vector(3, copy_double, delete_double);
    printf("Создан вектор: capacity=%zu, size=%zu\n", v.capacity, v.size);

    push_back_vector(&v, 1.1);
    push_back_vector(&v, 2.2);
    push_back_vector(&v, 3.3);
    push_back_vector(&v, 4.4);
    push_back_vector(&v, 5.5);

    printf("После добавлений: size=%zu, capacity=%zu\n", v.size, v.capacity);
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = %.2f\n", i, get_at_vector(&v, i));
    }

    assert(v.size == 5);
    assert(fabs(get_at_vector(&v, 0) - 1.1) < 1e-10);
    assert(fabs(get_at_vector(&v, 4) - 5.5) < 1e-10);

    delete_vector(&v);
    printf("Завершено\n\n");
}

/* === Получение и удаление по индексу === */
void test_get_and_delete_double() {
    printf("[TEST 2] Получение и удаление элементов\n");

    Vector v = create_vector(0, copy_double, delete_double);
    for (int i = 1; i <= 5; i++) push_back_vector(&v, i * 1.5);

    printf("Исходный вектор: ");
    for (size_t i = 0; i < v.size; i++) printf("%.2f ", get_at_vector(&v, i));
    printf("\n");

    printf("Элемент с индексом 2: %.2f\n", get_at_vector(&v, 2));
    printf("Элемент с несуществующим индексом (99): %.2f\n", get_at_vector(&v, 99));

    assert(fabs(get_at_vector(&v, 2) - 4.5) < 1e-10);
    assert(fabs(get_at_vector(&v, 99) - 0.0) < 1e-10); // default value

    printf("Удаляем элемент с индексом 1...\n");
    delete_at_vector(&v, 1);

    printf("После удаления: ");
    for (size_t i = 0; i < v.size; i++) printf("%.2f ", get_at_vector(&v, i));
    printf("\n");

    assert(v.size == 4);
    assert(fabs(get_at_vector(&v, 1) - 4.5) < 1e-10);

    delete_vector(&v);
    printf("Завершено\n\n");
}


void test_copy_and_compare_double() {
    printf("[TEST 3] Копирование и сравнение векторов\n");

    Vector v1 = create_vector(0, copy_double, delete_double);
    push_back_vector(&v1, 10.5);
    push_back_vector(&v1, 20.25);
    push_back_vector(&v1, 30.75);

    Vector v2 = create_vector(0, copy_double, delete_double);
    copy_vector(&v2, &v1);

    printf("v1: ");
    for (size_t i = 0; i < v1.size; i++) printf("%.2f ", get_at_vector(&v1, i));
    printf("\nv2: ");
    for (size_t i = 0; i < v2.size; i++) printf("%.2f ", get_at_vector(&v2, i));
    printf("\n");

    printf("Равны ли v1 и v2? %s\n", is_equal_vector(&v1, &v2) ? "Да" : "Нет");

    assert(is_equal_vector(&v1, &v2) == 1);

    push_back_vector(&v2, 999.99);
    printf("Добавили 999.99 в v2.\n");
    printf("Теперь равны? %s\n", is_equal_vector(&v1, &v2) ? "Да" : "Нет");

    assert(is_equal_vector(&v1, &v2) == 0);

    delete_vector(&v1);
    delete_vector(&v2);
    printf("Завершено\n\n");
}

void test_copy_vector_new_double() {
    printf("[TEST 4] Копирование с созданием нового вектора\n");

    Vector v = create_vector(0, copy_double, delete_double);
    for (int i = 1; i <= 4; i++) push_back_vector(&v, i * 2.5);
    
    printf("Создан новый вектор v:\n");
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = %.2f\n", i, get_at_vector(&v, i));
    }

    Vector *v_copy = copy_vector_new(&v);
    assert(v_copy != NULL);
    
    printf("Создан новый вектор v_copy:\n");
    for (size_t i = 0; i < v_copy->size; i++) {
        printf("  v_copy[%zu] = %.2f\n", i, get_at_vector(v_copy, i));
    }

    assert(is_equal_vector(&v, v_copy) == 1);
    assert(v_copy->size == v.size);

    delete_vector(&v);
    free_vector(v_copy);

    printf("Завершено\n\n");
}

void test_erase_and_delete_double() {
    printf("[TEST 5] Очистка и удаление\n");

    Vector v = create_vector(0, copy_double, delete_double);
    push_back_vector(&v, 3.14);
    push_back_vector(&v, 2.71);
    push_back_vector(&v, 1.41);

    printf("Перед очисткой: size=%zu, capacity=%zu\n", v.size, v.capacity);
    erase_vector(&v);
    printf("После erase_vector: size=%zu, capacity=%zu\n", v.size, v.capacity);

    assert(v.size == 0);
    assert(v.capacity == 0);
    assert(v.data == NULL);

    delete_vector(&v);
    printf("Завершено\n\n");
}

void test_precision_double() {
    printf("[TEST 6] Тестирование точности double\n");

    Vector v = create_vector(0, copy_double, delete_double);
    
    push_back_vector(&v, 0.123456789);
    push_back_vector(&v, 1.23456789e-10);
    push_back_vector(&v, 123456789.0);
    
    printf("Числа с разной точностью:\n");
    for (size_t i = 0; i < v.size; i++) {
        printf("  v[%zu] = %.15g\n", i, get_at_vector(&v, i));
    }
    
    assert(fabs(get_at_vector(&v, 0) - 0.123456789) < 1e-15);
    assert(fabs(get_at_vector(&v, 1) - 1.23456789e-10) < 1e-20);
    assert(fabs(get_at_vector(&v, 2) - 123456789.0) < 1e-6);
    
    delete_vector(&v);
    printf("Завершено\n\n");
}
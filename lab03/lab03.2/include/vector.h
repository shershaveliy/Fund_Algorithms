#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFINE_VECTOR(VECTOR_TYPE)\
typedef struct{\
    VECTOR_TYPE *data; /*указатель на массив элементов*/\
    size_t size;\
    size_t capacity;/*вместимость*/\
    VECTOR_TYPE (*CopyVoidPtr)(VECTOR_TYPE);/*копирование*/\
    void (*DeleteVoidPtr)(VECTOR_TYPE);/*удаление*/\
    int (*CompareVoidPtr)(VECTOR_TYPE, VECTOR_TYPE);/*сравнение*/\
} Vector;\
\
Vector create_vector(size_t initial_capacity, VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE), void (*DeleteFunc)(VECTOR_TYPE)){\
    Vector v;\
    v.size = 0;\
    v.capacity = initial_capacity > 0 ? initial_capacity : 1;\
    v.CopyVoidPtr = CopyFunc;\
    v.DeleteVoidPtr = DeleteFunc;\
    v.CompareVoidPtr = NULL;\
    v.data = (VECTOR_TYPE*)malloc(v.capacity * sizeof(VECTOR_TYPE));\
    if (!v.data){\
        v.capacity = 0;\
    }\
    return v;\
}\
\
Vector create_vector_with_comparator(size_t initial_capacity, VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE), void (*DeleteFunc)(VECTOR_TYPE), int (*CompareFunc)(VECTOR_TYPE, VECTOR_TYPE)){\
    Vector v = create_vector(initial_capacity, CopyFunc, DeleteFunc);\
    v.CompareVoidPtr = CompareFunc;\
    return v;\
}\
\
void erase_vector(Vector *v){\
    if (v && v->data){ /*проверка что не NULL*/\
        if (v->DeleteVoidPtr){\
            for (size_t i = 0; i < v->size; i++) {\
                v->DeleteVoidPtr(v->data[i]);\
            }\
        }\
        free(v->data);\
        v->data = NULL;\
        v->size = 0;\
        v->capacity = 0;\
    }\
}\
\
int is_equal_vector(const Vector *v1, const Vector *v2){\
    if (!v1 || !v2) return 0;\
    if (v1->size != v2->size) return 0;\
    if (v1->CompareVoidPtr && v2->CompareVoidPtr && v1->CompareVoidPtr == v2->CompareVoidPtr) {\
        for (size_t i = 0; i < v1->size; i++){\
            if (v1->CompareVoidPtr(v1->data[i], v2->data[i]) != 0){\
                return 0;\
            }\
        }\
    }\
    else{\
        for (size_t i = 0; i < v1->size; i++){\
            if (v1->data[i] != v2->data[i]){\
                return 0;\
            }\
        }\
    }\
    return 1;\
}\
\
void copy_vector(Vector *dest, const Vector *src){\
    if (!dest || !src) return;\
    erase_vector(dest);\
    dest->CopyVoidPtr = src->CopyVoidPtr;\
    dest->DeleteVoidPtr = src->DeleteVoidPtr;\
    dest->CompareVoidPtr = src->CompareVoidPtr;\
    dest->capacity = src->capacity;\
    dest->size = src->size;\
    dest->data = (VECTOR_TYPE*)malloc(dest->capacity * sizeof(VECTOR_TYPE));\
    if (!dest->data){\
        dest->capacity = 0;\
        dest->size = 0;\
        return;\
    }\
    if (src->CopyVoidPtr){\
        for (size_t i = 0; i < src->size; i++){\
            dest->data[i] = src->CopyVoidPtr(src->data[i]);\
        }\
    }\
    else{/*копируются толко указатели для простых типов*/\
        memcpy(dest->data, src->data, src->size * sizeof(VECTOR_TYPE));\
    }\
}\
\
Vector *copy_vector_new(const Vector *src){\
    if (!src) return NULL;\
    Vector *new_vec = (Vector*)malloc(sizeof(Vector));\
    if (!new_vec) return NULL;\
    *new_vec = create_vector(src->capacity, src->CopyVoidPtr, src->DeleteVoidPtr);\
    new_vec->CompareVoidPtr = src->CompareVoidPtr;\
    if (!new_vec->data){\
        free(new_vec);\
        return NULL;\
    }\
    copy_vector(new_vec, src);\
    return new_vec;\
}\
\
void push_back_vector(Vector *v, VECTOR_TYPE value){\
    if (!v) return;\
    if (v->size >= v->capacity){\
        size_t new_capacity = v->capacity * 2;\
        if (new_capacity == 0) new_capacity = 1;\
        VECTOR_TYPE *new_data = (VECTOR_TYPE*)realloc(v->data, new_capacity * sizeof(VECTOR_TYPE));\
        if (!new_data) return;\
        v->data = new_data;\
        v->capacity = new_capacity;\
    }\
    if (v->CopyVoidPtr){\
        v->data[v->size] = v->CopyVoidPtr(value);\
    }\
    else{\
        v->data[v->size] = value;\
    }\
    v->size++;\
}\
\
void delete_at_vector(Vector *v, size_t index){\
    if (!v || index >= v->size) return;\
    if (v->DeleteVoidPtr){\
        v->DeleteVoidPtr(v->data[index]);\
    }\
    for (size_t i = index; i < v->size - 1; i++){\
        v->data[i] = v->data[i + 1];\
    }\
    v->size--;\
}\
\
VECTOR_TYPE get_at_vector(const Vector *v, size_t index){\
    if (!v || index >= v->size){\
        VECTOR_TYPE default_value = {0};\
        return default_value;\
    }\
    return v->data[index];\
}\
\
void delete_vector(Vector *v){\
    if (v){\
        erase_vector(v);\
    }\
}\
\
void free_vector(Vector *v){\
    if (v){\
        erase_vector(v);\
        free(v);\
    }\
}

#endif // VECTOR_H
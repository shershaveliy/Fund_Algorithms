#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define DEFINE_HEAP(TYPE)\
\
typedef struct {\
    TYPE *items; /*динамический массв элементов*/\
    size_t count;/*текущее количество символов*/\
    size_t max_count;/*вместимость массива*/\
    TYPE (*copy_func)(TYPE);/*функц копирования*/\
    void (*free_func)(TYPE);/*функц освобождения элемента*/\
    int (*cmp_func)(TYPE, TYPE);/*функц сравнения элементв*/\
} Heap;\
\
static inline TYPE heap_default_copy(TYPE val){\
    return val;\
}\
/*просеивание вниз*/\
static inline void heap_sift_down(Heap *heap, size_t pos){\
    TYPE saved = heap->items[pos];/*сохраняем текущий элемент*/\
    \
    while (1){\
        size_t left = pos * 2 + 1; /*левый потомок*/\
        size_t right = left + 1;/*правый потомок*/\
        size_t swap_with = pos;/*кандидат для обмена*/\
        \
        if (left >= heap->count) break;\
        /*выбираем меньшего из потомков*/\
        if (right >= heap->count){\
            swap_with = left;\
        }\
        else{\
            if (heap->cmp_func(heap->items[left], heap->items[right]) <= 0) {\
                swap_with = left;\
            }\
            else{\
                swap_with = right;\
            }\
        }\
        /*если потомок не меньше saved останавливаемся*/\
        if (heap->cmp_func(heap->items[swap_with], saved) >= 0) break;\
        \
        heap->items[pos] = heap->items[swap_with];\
        pos = swap_with;\
    }/*Вставляем сохраненный элемент на найденное место*/\
    heap->items[pos] = saved;\
}\
\
static inline Heap heap_create(size_t init_size, TYPE (*copy_fn)(TYPE),\
                 void (*free_fn)(TYPE), int (*cmp_fn)(TYPE, TYPE)){\
    Heap h = {0};\
    if (init_size == 0) init_size = 1;\
    \
    h.copy_func = copy_fn ? copy_fn : heap_default_copy;\
    h.free_func = free_fn;\
    h.cmp_func = cmp_fn;\
    \
    h.items = (TYPE *)malloc(init_size * sizeof(TYPE));\
    if (h.items){\
        h.max_count = init_size;\
    }\
    return h;\
}\
\
static inline void heap_destroy(Heap *heap){\
    if (heap->items){\
        if (heap->free_func){\
            for (size_t i = 0; i < heap->count; i++){\
                heap->free_func(heap->items[i]);\
            }\
        }\
        free(heap->items);\
        heap->items = NULL;\
    }\
    heap->count = 0;\
    heap->max_count = 0;\
    heap->copy_func = NULL;\
    heap->free_func = NULL;\
    heap->cmp_func = NULL;\
}\
\
static inline bool heap_empty(const Heap *heap){\
    return heap->count == 0; \
}\
\
static inline size_t heap_size(const Heap *heap){\
    return heap->count; \
}\
\
static inline TYPE heap_top(const Heap *heap){\
    if (heap->count == 0) abort();\
    return heap->items[0];\
}\
\
static inline void heap_push(Heap *heap, TYPE value){\
    /*увеличение массива при необходимости*/\
    if (heap->count >= heap->max_count){\
        size_t new_max = heap->max_count == 0 ? 1 : heap->max_count * 2;\
        TYPE *new_items = (TYPE *)realloc(heap->items, new_max * sizeof(TYPE));\
        if (!new_items) abort();/*если всё упало*/\
        heap->items = new_items;\
        heap->max_count = new_max;\
    }\
    /*вставка в конец*/\
    size_t i = heap->count++;\
    heap->items[i] = heap->copy_func(value);\
    /*просеивание вверх*/\
    while (i > 0){\
        size_t parent = (i - 1) / 2;\
        if (heap->cmp_func(heap->items[parent], heap->items[i]) <= 0) {\
            break;\
        }\
        \
        TYPE temp = heap->items[parent];\
        heap->items[parent] = heap->items[i];\
        heap->items[i] = temp;\
        i = parent;\
    }\
}\
\
static inline TYPE heap_pop(Heap *heap) {\
    if (heap->count == 0) abort();\
    \
    TYPE top_item = heap->items[0];\
    heap->count--;\
    \
    if (heap->count > 0){\
        /*перемещаем последний элемент в корень*/\
        heap->items[0] = heap->items[heap->count];\
        heap_sift_down(heap, 0);\
    }\
    \
    return top_item;\
}\
/*построение кучи из массива за O(n) - алгоритм Флойда*/\
static inline Heap heap_build(TYPE *array, size_t n,\
                TYPE (*copy_fn)(TYPE), void (*free_fn)(TYPE),\
                int (*cmp_fn)(TYPE, TYPE)){\
    Heap h = heap_create(n, copy_fn, free_fn, cmp_fn);\
    if (!h.items) return h; /*возвращаем NULL по сути*/\
    \
    for (size_t i = 0; i < n; i++){\
        h.items[i] = h.copy_func(array[i]);\
    }\
    h.count = n;\
    /*просеиваем все узлы начиная с последнего "нелиста"*/\
    for (size_t i = n / 2; i-- > 0;){\
        heap_sift_down(&h, i);\
    }\
    \
    return h;\
}\
/*сравнение куч*/\
static inline bool heap_equals(const Heap *h1, const Heap *h2){\
    if (h1 == h2) return true;\
    if (!h1 || !h2) return false;\
    if (h1->count != h2->count) return false;\
    \
    for (size_t i = 0; i < h1->count; i++) {\
        if (h1->cmp_func(h1->items[i], h2->items[i]) != 0){\
            return false;\
        }\
    }\
    return true;\
}

#endif // HEAP_H
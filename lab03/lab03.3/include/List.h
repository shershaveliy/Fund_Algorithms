#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

#define DEFINE_LINKED_LIST(LIST_TYPE, NAME) \
\
typedef struct NAME##_Node { \
    LIST_TYPE* data; \
    struct NAME##_Node *prev; \
    struct NAME##_Node *next; \
} NAME##_Node; \
\
typedef struct { \
    NAME##_Node *head; \
    NAME##_Node *tail; \
    size_t size; \
    void (*DeleteVoidPtr)(LIST_TYPE); \
    LIST_TYPE (*CopyVoidPtr)(LIST_TYPE); \
    int (*Compare)(LIST_TYPE, LIST_TYPE); \
    LIST_TYPE invalidData; \
} NAME##_List; \
\
static inline NAME##_List NAME##_create_list( \
        void (*DeleteVoidPtr)(LIST_TYPE), \
        LIST_TYPE (*CopyVoidPtr)(LIST_TYPE), \
        int (*Compare)(LIST_TYPE, LIST_TYPE), \
        LIST_TYPE invalidData) { \
    NAME##_List l; \
    l.head = NULL; \
    l.tail = NULL; \
    l.size = 0; \
    l.DeleteVoidPtr = DeleteVoidPtr; \
    l.CopyVoidPtr = CopyVoidPtr; \
    l.Compare = Compare; \
    l.invalidData = invalidData; \
    return l; \
} \
\
static inline NAME##_Node *NAME##_create_node(NAME##_List *list, LIST_TYPE value) { \
    NAME##_Node *node = (NAME##_Node *)malloc(sizeof(NAME##_Node)); \
    if (!node) return NULL; \
    node->data = (LIST_TYPE*)malloc(sizeof(LIST_TYPE)); \
    if (!node->data) { free(node); return NULL; } \
    *(node->data) = list->CopyVoidPtr(value); \
    node->prev = node->next = NULL; \
    return node; \
} \
\
static inline void NAME##_destroy_node(NAME##_List *list, NAME##_Node *node) { \
    if (node->data) { \
        list->DeleteVoidPtr(*(node->data)); \
        free(node->data); \
    } \
    node->prev = node->next = NULL; \
    free(node); \
} \
\
static inline NAME##_Node* NAME##_get_node_at(const NAME##_List *list, size_t index) { \
    if (index >= list->size) return NULL; \
    NAME##_Node *found; \
    if (index < list->size / 2) { \
        found = list->head; \
        for (size_t i = 0; i < index; i++) found = found->next; \
    } else { \
        found = list->tail; \
        for (size_t i = list->size - 1; i > index; i--) found = found->prev; \
    } \
    return found; \
} \
\
static inline void NAME##_push_back_list(NAME##_List *list, LIST_TYPE value) { \
    NAME##_Node *n = NAME##_create_node(list, value); \
    if (!n) return; \
    if (!list->tail) list->head = list->tail = n; \
    else { n->prev = list->tail; list->tail->next = n; list->tail = n; } \
    list->size++; \
} \
\
static inline void NAME##_push_front_list(NAME##_List *list, LIST_TYPE value) { \
    NAME##_Node *n = NAME##_create_node(list, value); \
    if (!n) return; \
    if (!list->head) list->head = list->tail = n; \
    else { n->next = list->head; list->head->prev = n; list->head = n; } \
    list->size++; \
} \
\
static inline LIST_TYPE NAME##_pop_back_list(NAME##_List *list) { \
    if (!list->tail) return list->invalidData; \
    NAME##_Node *tail = list->tail; \
    LIST_TYPE data = *(tail->data); \
    if (list->head == list->tail) list->head = list->tail = NULL; \
    else { list->tail = tail->prev; list->tail->next = NULL; } \
    NAME##_destroy_node(list, tail); \
    list->size--; \
    return data; \
} \
\
static inline LIST_TYPE NAME##_pop_front_list(NAME##_List *list) { \
    if (!list->head) return list->invalidData; \
    NAME##_Node *head = list->head; \
    LIST_TYPE data = *(head->data); \
    if (list->head == list->tail) list->head = list->tail = NULL; \
    else { list->head = head->next; list->head->prev = NULL; } \
    NAME##_destroy_node(list, head); \
    list->size--; \
    return data; \
} \
\
static inline void NAME##_erase_list(NAME##_List *list) { \
    while (list->head) { \
        NAME##_Node *next = list->head->next; \
        NAME##_destroy_node(list, list->head); \
        list->head = next; \
    } \
    list->head = list->tail = NULL; \
    list->size = 0; \
} \
\
static inline void NAME##_delete_list(NAME##_List *list) { \
    NAME##_erase_list(list); \
} \
\
static inline void NAME##_insert_at_list(NAME##_List *list, size_t index, LIST_TYPE value) { \
    if (index > list->size) return; \
    if (index == 0) { NAME##_push_front_list(list, value); return; } \
    if (index == list->size) { NAME##_push_back_list(list, value); return; } \
    NAME##_Node *node = NAME##_get_node_at(list, index); \
    NAME##_Node *new_node = NAME##_create_node(list, value); \
    new_node->next = node; \
    new_node->prev = node->prev; \
    new_node->prev->next = new_node; \
    node->prev = new_node; \
    list->size++; \
} \
\
static inline void NAME##_delete_at_list(NAME##_List *list, size_t index) { \
    if (index >= list->size) return; \
    if (index == 0) { LIST_TYPE d = NAME##_pop_front_list(list); list->DeleteVoidPtr(d); return; } \
    if (index == list->size - 1) { LIST_TYPE d = NAME##_pop_back_list(list); list->DeleteVoidPtr(d); return; } \
    NAME##_Node *node = NAME##_get_node_at(list, index); \
    node->prev->next = node->next; \
    node->next->prev = node->prev; \
    NAME##_destroy_node(list, node); \
    list->size--; \
} \
\
static inline LIST_TYPE NAME##_get_at_list(const NAME##_List *list, size_t index) { \
    NAME##_Node *n = NAME##_get_node_at(list, index); \
    return n ? *(n->data) : list->invalidData; \
} \
\
static inline int NAME##_is_equal_list(const NAME##_List *l1, const NAME##_List *l2) { \
    if (l1 == l2) return 1; \
    if (!l1 || !l2) return 0; \
    if (l1->size != l2->size) return 0; \
    NAME##_Node *h1 = l1->head; \
    NAME##_Node *h2 = l2->head; \
    while (h1 && h2) { \
        if (l1->Compare(*(h1->data), *(h2->data)) != 0) return 0; \
        h1 = h1->next; \
        h2 = h2->next; \
    } \
    return 1; \
} \
\
static inline void NAME##_push_stack(NAME##_List *stack, LIST_TYPE value) { \
    NAME##_push_back_list(stack, value); \
} \
\
static inline LIST_TYPE NAME##_pop_stack(NAME##_List *stack) { \
    return NAME##_pop_back_list(stack); \
} \
\
static inline LIST_TYPE NAME##_peek_stack(const NAME##_List *stack) { \
    if (!stack->tail) return stack->invalidData; \
    return *(stack->tail->data); \
} \
\
static inline void NAME##_enqueue(NAME##_List *queue, LIST_TYPE value) { \
    NAME##_push_back_list(queue, value); \
} \
\
static inline LIST_TYPE NAME##_dequeue(NAME##_List *queue) { \
    return NAME##_pop_front_list(queue); \
} \
\
static inline LIST_TYPE NAME##_peek_queue(const NAME##_List *queue) { \
    if (!queue->head) return queue->invalidData; \
    return *(queue->head->data); \
}

#endif

#include "undo.h"
#include <stdlib.h>
#include <stdio.h>

/* Dynamic array for undo operations (moved from original main) */
static Operation *undo_arr = NULL;
static size_t undo_size = 0;
static size_t undo_capacity = 0;
/* modification_count should reflect total number of modifications since last undo */
static int modification_count = 0;

int push_operation(const Operation *op) {
    if (undo_size + 1 > undo_capacity) {
        size_t nc = (undo_capacity == 0) ? 16 : undo_capacity * 2;
        Operation *tmp = (Operation*)realloc(undo_arr, nc * sizeof(Operation));
        if (!tmp) return 0;
        undo_arr = tmp;
        undo_capacity = nc;
    }
    undo_arr[undo_size++] = *op;
    modification_count++;
    return 1;
}

int pop_operation(Operation *out) {
    if (undo_size == 0) return 0;
    *out = undo_arr[--undo_size];
    return 1;
}

void free_undo_storage(void) {
    free(undo_arr);
    undo_arr = NULL;
    undo_size = undo_capacity = 0;
    modification_count = 0;
}

/* Undo logic: undo last N/2 modifications */
void undo_operations(Liver_List *list) {
    if (modification_count <= 0 || undo_size == 0) {
        printf("Нет операций для отмены\n");
        return;
    }

    int N = modification_count;
    int to_undo = N / 2;
    if (to_undo <= 0) {
        printf("N/2 == 0, ничего не отменяется\n");
        return;
    }

    printf("Отмена %d операций (N=%d)...\n", to_undo, N);

    for (int i = 0; i < to_undo; ++i) {
        Operation op;
        if (!pop_operation(&op)) break;
        modification_count--;

        if (op.type == OP_ADD) {
            unsigned int id = op.data.id;
            Liver_Node *cur = list->head;
            size_t idx = 0;
            while (cur && cur->data->id != id) { cur = cur->next; idx++; }
            if (cur) {
                delete_at_list(list, idx);
                printf("Отмена добавления ID=%u\n", id);
            } else {
                printf("Не найден элемент для отмены добавления ID=%u\n", id);
            }
        }
        else if (op.type == OP_DELETE) {
            size_t idx = op.index;
            if (idx > list->size) idx = list->size;
            if (idx == 0) Liver_push_front_list(list, op.data);
            else if (idx == list->size) Liver_push_back_list(list, op.data);
            else Liver_insert_at_list(list, idx, op.data);
            printf("Отмена удаления ID=%u (вставлен обратно)\n", op.data.id);
        }
        else if (op.type == OP_MODIFY) {
            unsigned int id = op.data.id;
            Liver_Node *cur = list->head;
            size_t idx = 0;
            while (cur && cur->data->id != id) { cur = cur->next; idx++; }
            if (cur) {
                delete_at_list(list, idx);
            }
            size_t insert_idx = op.index;
            if (insert_idx > list->size) insert_idx = list->size;
            if (insert_idx == 0) Liver_push_front_list(list, op.old_data);
            else if (insert_idx == list->size) Liver_push_back_list(list, op.old_data);
            else Liver_insert_at_list(list, insert_idx, op.old_data);
            printf("Отмена изменения ID=%u (восстановлены старые данные)\n", op.data.id);
        }
    }

    printf("Отмена завершена. Осталось модификаций: %d\n", modification_count);
}

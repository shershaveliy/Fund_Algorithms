#ifndef UNDO_H
#define UNDO_H

#include <stddef.h>
#include "liver.h"

/* Тип операции для undo */
typedef enum { OP_ADD, OP_DELETE, OP_MODIFY } OpType;

typedef struct {
    OpType type;
    Liver data;      /* для ADD — добавленный; для DELETE — удалённый; для MODIFY — новый */
    Liver old_data;  /* для MODIFY — старое значение */
    size_t index;    /* позиция (иногда нужна для восстановления) */
} Operation;

/* invalid operation constant helper (optional) */
#define INVALID_OPERATION ((Operation){0})

/* DEFINE linked list for Operation */
DEFINE_LINKED_LIST(Operation, Operation)

/* API для хранения и работы со стеком операций (undo array) */
int push_operation(const Operation *op); /* вернуть 1 при успехе, 0 — ошибка */
int pop_operation(Operation *out);       /* вернуть 1 если вышел op, 0 — пусто */
void free_undo_storage(void);
void undo_operations(Liver_List *list);  /* отмена N/2 модификаций (реализовано в undo.c) */

#endif /* UNDO_H */

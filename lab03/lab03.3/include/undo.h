#ifndef UNDO_H
#define UNDO_H

#include <stddef.h>
#include "liver.h"

typedef enum{
    OP_ADD, // Операция добавления нового жителя
    OP_DELETE,// Операция удаления жителя  
    OP_MODIFY // Операция изменения данных жителя
} OpType;

typedef struct {
    OpType type;
    Liver data; 
    Liver old_data;// Старые данные (только для MODIFY)
    size_t index;
} Operation;

//макрос для создания невалидной операции
#define INVALID_OPERATION ((Operation){0})

DEFINE_LINKED_LIST(Operation, Operation)


int push_operation(const Operation *op);
int pop_operation(Operation *out);
void free_undo_storage(void);
void undo_operations(Liver_List *list);

#endif

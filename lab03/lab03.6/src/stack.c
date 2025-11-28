#include "../include/stack.h"

void init_stack(Stack *stack){
    stack->top = -1;
}

int is_empty(Stack *stack){
    return stack->top == -1;
}

int push(Stack *stack, char c) {
    if (stack->top >= STACK_SIZE - 1){
        return 0; // Переполнение стека
    }
    stack->data[++(stack->top)] = c;
    return 1;
}

char pop(Stack *stack){
    if (is_empty(stack)){
        return '\0';
    }
    return stack->data[(stack->top)--];
}

char peek(Stack *stack){
    if (is_empty(stack)){
        return '\0';
    }
    return stack->data[stack->top];
}
#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 1000

typedef struct{
    char data[STACK_SIZE];
    int top;
} Stack;

void init_stack(Stack *stack);
int is_empty(Stack *stack);
int push(Stack *stack, char c);
char pop(Stack *stack);
char peek(Stack *stack);

#endif
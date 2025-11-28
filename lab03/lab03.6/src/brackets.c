#include "../include/brackets.h"
#include "../include/stack.h"

// Проверка, является ли символ открывающей скобкой
int is_open_bracket(char c){
    return c == '(' || c == '[' || c == '{' || c == '<';
}

// Проверка, является ли символ закрывающей скобкой
int is_close_bracket(char c){
    return c == ')' || c == ']' || c == '}' || c == '>';
}

// Получение соответствующей открывающей скобки для закрывающей
char get_matching_open_bracket(char close_bracket){
    switch (close_bracket){
        case ')': return '(';
        case ']': return '[';
        case '}': return '{';
        case '>': return '<';
        default: return '\0';
    }
}

int check_brackets(const char *str){
    Stack stack;
    init_stack(&stack);
    
    for (int i = 0; str[i] != '\0'; i++){
        char current = str[i];
        
        // Если это открывающая скобка - добавляем в стек
        if (is_open_bracket(current)){
            if (!push(&stack, current)){
                return 0;
            }
        }
        // Если это закрывающая скобка - проверяем соответствие
        else if (is_close_bracket(current)){
            char expected_open = get_matching_open_bracket(current);
            
            // Если стек пуст или верхний элемент не соответствует
            if (is_empty(&stack) || pop(&stack) != expected_open){
                return 0; // Несбалансированные скобки
            }
        }
        // Остальные символы игнорируем
    }
    
    // Если стек пуст - все скобки сбалансированы
    return is_empty(&stack);
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/brackets.h"

void demonstrate() {

    const char *tests[] = {
        // Correct cases
        "",
        "()", "[]", "{}", "<>",
        "( )", "[ ]", "{ }", "< >",
        "()[]", "[]{}", "{}<>", "<>()",
        "()[]{}<>",
        "(())", "[[]]", "{{}}", "<<>>",
        "({})", "[()]", "{[]}", "<[]>",
        "([{}])", "<({[]})>",
        "({[<>]})",
        "((([[{{<>}}]])))",
        "a(b)c",
        "hello [world] {test} <string>",
        "int main() { return 0; }",
        "array[10] = {1, 2, 3};",
        "if (x = 0) { y = x * 2; }",
        "function<a,b>(param1, param2)",
        "((a + b) * [c - d] / {e % f})",
        "no brackets here",
        "123 456 789",
        "!@#$%^&*()_+",
        "multiple    spaces",
        "(a + b) * (c - d)",
        "array[index] = value;",
        "if (condition) { action(); }",
        "{(a[b] + c(d))}",
        "(((())))",
        "([{<>}])",
        "<html><body></body></html>",
        "{key: [value1, value2]}",
        "text (a + b) [c - {d * (e + f)}]",
        "a(b[c]{d<e>})f",
        "function(x[y{z<w>}])",
        "if ((x[0] <> y[1]))",
        "(((((((((((((((((((((())))))))))))))))))))))",
        "<><><><><>",
        "<<<>>>",
        "<<><>>",
        "[({(<()>)}[])]",
        "(((((((((())))))))))",

        // Incorrect cases
        "(",
        "[",
        "{",
        "<",
        "(()",
        "[[[]",
        "{{}",
        "([]{}",
        "({[<>",
        ")",
        "]",
        "}",
        ">",
        "())",
        "[]]",
        "{}}",
        "<>>",
        ")([]",
        "][{}",
        "}{<>",
        "><()",
        "(]",
        "[)",
        "{>",
        "<}",
        "([)]",
        "{[}]",
        "<(>)",
        "({[}])",
        "([{<)>]}",
        "(<[{)}>])",
        "{<[(])>}",
        "{<([)]>}",
        "[({(<)>})]",
        "([{<abc123>})]",
        "no closing bracket {",
        "extra closing ) here",
        "mismatch <]>",
        "<div><span></div></span>",
        "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[",
        "({[<]})",

        NULL
    };

    int total_tests = 0;
    int passed = 0;

    // Count tests
    for (int i = 0; tests[i] != NULL; i++)
        total_tests++;

    printf("Running %d tests...\n\n", total_tests);
    fflush(stdout);

    for (int i = 0; tests[i] != NULL; i++) {

        int ok = check_brackets(tests[i]);

        char status[16];
        if (ok) {
            strcpy(status, "[OK]");
            passed++;
        } else {
            strcpy(status, "[ERR]");
        }

        char display[60];
        if (strlen(tests[i]) > 50) {
            strncpy(display, tests[i], 47);
            display[47] = 0;
            strcat(display, "...");
        } else {
            strcpy(display, tests[i]);
        }

        printf("%3d. %-50s  %s\n", i + 1, display, status);

        if ((i + 1) % 10 == 0)
            fflush(stdout);
    }


    fflush(stdout);
}
void interactive_mode() {
    printf("\n================================================================================\n");
    printf("                    ИНТЕРАКТИВНЫЙ РЕЖИМ\n");
    printf("================================================================================\n");
    printf("Вводите строки для проверки (или 'quit' для выхода):\n\n");
    
    char input[1000];
    
    while (1) {
        printf("> ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        input[strcspn(input, "\n")] = '\0';
        
        if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0 || 
            strcmp(input, "q") == 0) {
            break;
        }
        
        if (strlen(input) == 0) {
            printf("  Пустая строка - корректна\n");
            continue;
        }
        
        int result = check_brackets(input);
        
        if (result) {
            printf("[OK]\n");
        } else {
            printf("[ERR]\n");
        }
    }
}

int main() {
    printf("ПРОВЕРКА КОРРЕКТНОСТИ РАССТАНОВКИ СКОБОК\n");
    printf("Поддерживаемые скобки: ( ) [ ] { } < >\n\n");
    
    int choice;
    
    while (1) {
        printf("Выберите режим:\n");
        printf("1 - Демонстрация (все тесты)\n");
        printf("2 - Интерактивный режим\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");
        
        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Ошибка ввода!\n\n");
            continue;
        }
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        switch (choice) {
            case 0:
                printf("Выход.\n");
                return 0;
                
            case 1:
                demonstrate();
                break;
                
            case 2:
                interactive_mode();
                break;
                
            case 3: {
                char input[1000];
                printf("Введите строку: ");
                if (fgets(input, sizeof(input), stdin) != NULL) {
                    input[strcspn(input, "\n")] = '\0';
                    int result = check_brackets(input);
                    printf("Результат: %s\n", result ? "КОРРЕКТНО" : "НЕКОРРЕКТНО");
                }
                break;
            }
                
            default:
                printf("Неверный выбор!\n");
                break;
        }
        
        printf("\n");
    }
    
    return 0;
}
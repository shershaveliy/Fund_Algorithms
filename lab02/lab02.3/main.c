#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "include/overprintf.h"

void test_roman() {
    printf("тест римских чисел (%%Ro)\n");
    
    struct {
        int input;
        const char *expected;
    } tests[] = {
        {3, "III"}, {8, "VIII"}, {19, "XIX"}, {47, "XLVII"},
        {94, "XCIV"}, {247, "CCXLVII"}, {589, "DLXXXIX"},
        {1294, "MCCXCIV"}, {1999, "MCMXCIX"}, {2499, "MMCDXCIX"},
        {0, "0"}, {-12, "-12"}, {4001, "4001"}
    };
    
    char buffer[64];
    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        oversprintf(buffer, "%Ro", tests[i].input);
        printf("   %4d -> %-20s (ожидалось: %s)\n", 
               tests[i].input, buffer, tests[i].expected);
    }
    printf("\n");
}

void test_zeckendorf() {
    printf("тесты для Цекендорфа (%%Zr)\n");
    
    unsigned int tests[] = {3, 8, 21, 55, 89, 144, 233, 377, 610, 986};
    
    char buffer[64];
    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        oversprintf(buffer, "%Zr", tests[i]);
        printf("   %10u -> %s\n", tests[i], buffer);
    }
    printf("\n");
}

void test_base() {
    printf("тест систем счисления (%%Cv/%%CV)\n");
    
    struct {
        int number;
        int base;
        const char *lower_expected;
        const char *upper_expected;
    } tests[] = {
        {127, 2, "1111111", "1111111"},
        {100, 8, "144", "144"},
        {1000, 16, "3e8", "3E8"},
        {2023, 36, "1kj", "1KJ"},
        {123456, 16, "1e240", "1E240"},
        {-100, 8, "-144", "-144"},
        {7, 3, "21", "21"},
        {255, 12, "193", "193"}
    };
    
    char buffer[64];
    printf("   Нижний регистр (%%Cv):\n");
    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        oversprintf(buffer, "%Cv", tests[i].number, tests[i].base);
        printf("      %6d в %2d-ричной -> %-12s (ожидалось: %s)\n", 
               tests[i].number, tests[i].base, buffer, tests[i].lower_expected);
    }
    
    printf("   Верхний регистр (%%CV):\n");
    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        oversprintf(buffer, "%CV", tests[i].number, tests[i].base);
        printf("      %6d в %2d-ричной -> %-12s (ожидалось: %s)\n", 
               tests[i].number, tests[i].base, buffer, tests[i].upper_expected);
    }
    printf("\n");
}

void test_base10() {
    printf("тест перевода в десятичную систему (%%to/%%TO)\n");
    
    struct {
        const char *input;
        int base;
        const char *expected;
    } tests[] = {
        {"1111111", 2, "127"},
        {"144", 8, "100"},
        {"3e8", 16, "1000"},
        {"1kj", 36, "2023"},
        {"1e240", 16, "123456"},
        {"-144", 8, "-100"},
        {"21", 3, "7"},
        {"193", 12, "255"},
        {"abc", 16, "2748"},
        {"XYZ", 36, "44027"},
        {"+3e8", 16, "1000"}
    };
    
    char buffer[64];
    printf("   Нижний регистр (%%to):\n");
    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        oversprintf(buffer, "%to", tests[i].input, tests[i].base);
        printf("      '%s' в %2d-ричной -> %-12s (ожидалось: %s)\n", 
               tests[i].input, tests[i].base, buffer, tests[i].expected);
    }
    
    printf("   Верхний регистр (%%TO):\n");
    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        oversprintf(buffer, "%TO", tests[i].input, tests[i].base);
        printf("      '%s' в %2d-ричной -> %-12s (ожидалось: %s)\n", 
               tests[i].input, tests[i].base, buffer, tests[i].expected);
    }
    printf("\n");
}

void test_dumps() {
    printf("тест дампов памяти\n");
    
    char buffer[256];
    
    printf("   Целые числа (mi):\n");
    int int_values[] = {127, -127, 1024, -1024, 65535};
    for (int i = 0; i < sizeof(int_values)/sizeof(int_values[0]); i++) {
        oversprintf(buffer, "%mi", int_values[i]);
        printf("      int %11d -> %s\n", int_values[i], buffer);
    }
    
    printf("   Беззнаковые целые (mu):\n");
    unsigned int uint_values[] = {127, 1024, 65535, 1000000, 4294967295U};
    for (int i = 0; i < sizeof(uint_values)/sizeof(uint_values[0]); i++) {
        oversprintf(buffer, "%mu", uint_values[i]);
        printf("      uint %10u -> %s\n", uint_values[i], buffer);
    }
    
    printf("   Вещественные double (md):\n");
    double double_values[] = {0.5, -0.5, 2.71828, -3.14159, 100.12345};
    for (int i = 0; i < sizeof(double_values)/sizeof(double_values[0]); i++) {
        oversprintf(buffer, "%md", double_values[i]);
        printf("      double %8.5f -> %s\n", double_values[i], buffer);
    }
    
    printf("   Вещественные float (mf):\n");
    float float_values[] = {0.5f, -0.5f, 2.71828f, -3.14159f, 100.123f};
    for (int i = 0; i < sizeof(float_values)/sizeof(float_values[0]); i++) {
        oversprintf(buffer, "%mf", float_values[i]);
        printf("      float %8.5f -> %s\n", float_values[i], buffer);
    }
    printf("\n");
}

void test_combined_operations() {
    printf("Комбинированные операции\n");
    
    char buffer[256];
    
    printf("   Комбинированная строка:\n");
    oversprintf(buffer, "Римское: %Ro, Цекендорф: %Zr, HEX: %Cv", 2023, 2023u, 2023, 16);
    printf("      %s\n", buffer);
    
    oversprintf(buffer, "Двоичное: %Cv, Восьмеричное: %Cv", 255, 2, 255, 8);
    printf("      %s\n", buffer);
    
    oversprintf(buffer, "Дамп int: %mi, Дамп double: %md", -12345, -12345.6789);
    printf("      %s\n", buffer);
    
    printf("\n");
}

void test_standard_specifiers() {
    printf("тесты стандартных спецификаторов\n");
    
    char buffer[128];
    
    oversprintf(buffer, "%d", -42);
    printf("   %%d  -42     -> %s\n", buffer);
    
    oversprintf(buffer, "%i", 42);
    printf("   %%i  42      -> %s\n", buffer);
    
    oversprintf(buffer, "%u", 100u);
    printf("   %%u  100u    -> %s\n", buffer);
    
    oversprintf(buffer, "%o", 255);
    printf("   %%o  255     -> %s\n", buffer);
    
    oversprintf(buffer, "%x", 255);
    printf("   %%x  255     -> %s\n", buffer);
    
    oversprintf(buffer, "%X", 255);
    printf("   %%X  255     -> %s\n", buffer);
    
    oversprintf(buffer, "%.2f", 3.14159);
    printf("   %%.2f 3.14159 -> %s\n", buffer);
    
    oversprintf(buffer, "%.3e", 12345.6789);
    printf("   %%.3e 12345.6789 -> %s\n", buffer);
    
    oversprintf(buffer, "%c", 'A');
    printf("   %%c  'A'     -> %s\n", buffer);
    
    oversprintf(buffer, "%s", "test");
    printf("   %%s  \"test\"  -> %s\n", buffer);
    
    oversprintf(buffer, "|%5d|", 42);
    printf("   |%%5d| 42     -> %s\n", buffer);
    
    oversprintf(buffer, "|%-5d|", 42);
    printf("   |%%-5d| 42    -> %s\n", buffer);
    
    printf("\n");
}


void run_tests_sprintf() {
    printf("ТЕСТЫ:\n\n");
    
    test_roman();
    test_zeckendorf();
    test_base();
    test_base10();
    test_dumps();
    test_combined_operations();
    test_standard_specifiers();
    
    printf("КОНЕЦ ТЕСТОВ:\n\n");
}


void test_roman_fprintf() {
    FILE *fout = fopen("output.txt", "w");
    if(!fout){
        printf("Ошибка открытия файла");
        return;
    }
    
    fprintf(fout, "тест римских чисел (%%Ro)\n");
    
    int tests[] = {3, 8, 19, 47, 94, 247, 589, 1294, 1999, 2499, 0, -12, 4001};
    
    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        fprintf(fout, "   %4d -> ", tests[i]);
        overfprintf(fout, "%Ro", tests[i]);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
    fclose(fout);
}

void test_zeckendorf_fprintf() {
    FILE *fout = fopen("output.txt", "a");
    if(!fout){
        printf("Ошибка открытия файла");
        return;
    }
    
    fprintf(fout, "тесты для Цекендорфа (%%Zr)\n");
    
    unsigned int tests[] = {3, 8, 21, 55, 89, 144, 233, 377, 610, 987};
    
    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        fprintf(fout, "   %10u -> ", tests[i]);
        overfprintf(fout, "%Zr", tests[i]);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
    fclose(fout);
}

void test_base_fprintf() {
    FILE *fout = fopen("output.txt", "a");
    if(!fout){
        printf("Ошибка открытия файла");
        return;
    }
    
    fprintf(fout, "тест систем счисления (%%Cv/%%CV)\n");
    
    struct {
        int number;
        int base;
    } tests[] = {
        {127, 2}, {100, 8}, {1000, 16}, {2023, 36},
        {123456, 16}, {-100, 8}, {7, 3}, {255, 12}
    };
    
    fprintf(fout, "   Нижний регистр (%%Cv):\n");
    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        fprintf(fout, "      %6d в %2d-ричной -> ", tests[i].number, tests[i].base);
        overfprintf(fout, "%Cv", tests[i].number, tests[i].base);
        fprintf(fout, "\n");
    }
    
    fprintf(fout, "   Верхний регистр (%%CV):\n");
    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        fprintf(fout, "      %6d в %2d-ричной -> ", tests[i].number, tests[i].base);
        overfprintf(fout, "%CV", tests[i].number, tests[i].base);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
    fclose(fout);
}

void test_memory_dumps_fprintf() {
    FILE *fout = fopen("output.txt", "w");
    if(!fout){
        printf("Ошибка открытия файла");
        return;
    }
    
    fprintf(fout, "тест дампов памяти\n\n");
    
    fprintf(fout, "Целые числа (mi):\n");
    int int_values[] = {0, 1, 255, -1, 256, -256, 65535, INT_MAX, INT_MIN};
    for (int i = 0; i < sizeof(int_values)/sizeof(int_values[0]); i++) {
        fprintf(fout, "   int %11d -> ", int_values[i]);
        overfprintf(fout, "%mi", int_values[i]);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
    
    fprintf(fout, "Беззнаковые целые (mu):\n");
    unsigned int uint_values[] = {0, 1, 255, 256, 65535, 1000000, UINT_MAX};
    for (int i = 0; i < sizeof(uint_values)/sizeof(uint_values[0]); i++) {
        fprintf(fout, "   uint %10u -> ", uint_values[i]);
        overfprintf(fout, "%mu", uint_values[i]);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
    
    fprintf(fout, "Вещественные double (md):\n");
    double double_values[] = {0.0, 1.0, -1.0, 3.14159, -2.71828, 123.456, 0.5, -0.5};
    for (int i = 0; i < sizeof(double_values)/sizeof(double_values[0]); i++) {
        fprintf(fout, "   double %8.5f -> ", double_values[i]);
        overfprintf(fout, "%md", double_values[i]);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
    
    fprintf(fout, "Вещественные float (mf):\n");
    float float_values[] = {0.0f, 1.0f, -1.0f, 3.14159f, -2.71828f, 123.456f, 0.5f, -0.5f};
    for (int i = 0; i < sizeof(float_values)/sizeof(float_values[0]); i++) {
        fprintf(fout, "   float %8.5f -> ", float_values[i]);
        overfprintf(fout, "%mf", float_values[i]);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
    
    fprintf(fout, "Сравнение int и unsigned int:\n");
    int compare_values[] = {1, 255, -1};
    for (int i = 0; i < sizeof(compare_values)/sizeof(compare_values[0]); i++) {
        fprintf(fout, "   Значение %d:\n", compare_values[i]);
        fprintf(fout, "      int     -> ");
        overfprintf(fout, "%mi", compare_values[i]);
        fprintf(fout, "\n");
        fprintf(fout, "      unsigned-> ");
        overfprintf(fout, "%mu", (unsigned int)compare_values[i]);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
    
    fclose(fout);
    printf("Результаты записаны в memory_dumps.txt\n");
}

void test_standard_specifiers_file() {
    FILE *fout = fopen("output.txt", "w");
    if(!fout){
        printf("ошибка файла\n");
        return;
    }
    
    // Такая же структура как в консольном выводе
    overfprintf(fout, "тесты стандартных спецификаторов\n\n");
    
    overfprintf(fout, "%%d  -42     -> %d\n", -42);
    overfprintf(fout, "%%i  42      -> %i\n", 42);
    overfprintf(fout, "%%u  100u    -> %u\n", 100u);
    overfprintf(fout, "%%o  255     -> %o\n", 255);
    overfprintf(fout, "%%x  255     -> %x\n", 255);
    overfprintf(fout, "%%X  255     -> %X\n", 255);
    overfprintf(fout, "%%.2f 3.14159 -> %.2f\n", 3.14159);
    overfprintf(fout, "%%.3e 12345.6789 -> %.3e\n", 12345.6789);
    overfprintf(fout, "%%c  'A'     -> %c\n", 'A');
    overfprintf(fout, "%%s  \"test\"  -> %s\n", "test");
    overfprintf(fout, "|%%5d| 42     -> |%5d|\n", 42);
    overfprintf(fout, "|%%-5d| 42    -> |%-5d|\n", 42);
    
    fclose(fout);
}

void run_tests_fprintf() {
    printf("Запуск тестов fprintf...\n");
    
    test_roman_fprintf();
    test_zeckendorf_fprintf();
    test_base_fprintf();
    test_standard_specifiers_file();
    
    printf("Тесты fprintf завершены. Результаты в output.txt\n");
}


int main() {
    
    run_tests_sprintf();
    run_tests_fprintf();
    
    return 0;
}
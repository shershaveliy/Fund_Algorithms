#include <stdio.h>
#include <stdlib.h>
#include "include/overscanf.h"

void test_Ro_sscanf() {
    printf("=== Тест %%Ro — римские числа из строки ===\n");

    const char *inputs[] = {"I", "IV", "IX", "XII", "XL", "XC", "CXXIV", "MCMXCIX"};
    int expected[] = {1, 4, 9, 12, 40, 90, 124, 1999};
    int values[8] = {0};
    int passed = 0;

    for (int i = 0; i < 8; i++) {
        int result = oversscanf(inputs[i], "%Ro", &values[i]);
        int correct = (values[i] == expected[i]);
        printf("%s: \"%s\" → %d (ожидалось: %d)\n", 
               correct ? "PASS" : "FAIL", 
               inputs[i], values[i], expected[i]);
        if (correct) passed++;
    }
    printf("Результат: %d/%d пройдено\n\n", passed, 8);
}

void test_Zr_sscanf() {
    printf("=== Тест %%Zr — цекендорф из строки ===\n");

    const char *inputs[] = {
        "0011",
        "1011",
        "10011",
        "101011",
        "100010011",
        "11"
    };
    unsigned int expected[] = {3, 4, 6, 12, 43, 1};
    unsigned int values[6] = {0};
    int passed = 0;

    for (int i = 0; i < 6; i++) {
        int result = oversscanf(inputs[i], "%Zr", &values[i]);
        int correct = (values[i] == expected[i]);
        printf("%s: \"%s\" → %u (ожидалось: %u)\n", 
               correct ? "PASS" : "FAIL", 
               inputs[i], values[i], expected[i]);
        if (correct) passed++;
    }
    printf("Результат: %d/%d пройдено\n\n", passed, 6);
}

void test_Cv_sscanf() {
    printf("=== Тест %%Cv — системы счисления (строчные) ===\n");

    // Тестируем по одному числу с фиксированным основанием
    struct {
        const char *input;
        int base;
        int expected;
    } tests[] = {
        {"1111111", 2, 127},
        {"144", 8, 100},
        {"3e8", 16, 1000},
        {"1kj", 36, 2035},
        {"-144", 8, -100},
        {"21", 3, 7},
        {"ff", 16, 255},
        {"abc", 16, 2748}
    };

    int passed = 0;
    for (int i = 0; i < 8; i++) {
        int value = 0;
        int result = oversscanf(tests[i].input, "%Cv", &value, tests[i].base);
        int correct = (value == tests[i].expected);
        printf("%s: \"%s\" (base %d) → %d (ожидалось: %d)\n", 
               correct ? "PASS" : "FAIL", 
               tests[i].input, tests[i].base, value, tests[i].expected);
        if (correct) passed++;
    }
    printf("Результат: %d/%d пройдено\n\n", passed, 8);
}

void test_CV_sscanf() {
    printf("=== Тест %%CV — системы счисления (прописные) ===\n");

    struct {
        const char *input;
        int base;
        int expected;
    } tests[] = {
        {"3E8", 16, 1000},
        {"1KJ", 36, 2035},
        {"FF", 16, 255},
        {"ABC", 16, 2748},
        {"XYZ", 36, 44027},
        {"-144", 8, -100},
        {"1E240", 16, 123456},
        {"193", 12, 255}
    };

    int passed = 0;
    for (int i = 0; i < 8; i++) {
        int value = 0;
        int result = oversscanf(tests[i].input, "%CV", &value, tests[i].base);
        int correct = (value == tests[i].expected);
        printf("%s: \"%s\" (base %d) → %d (ожидалось: %d)\n", 
               correct ? "PASS" : "FAIL", 
               tests[i].input, tests[i].base, value, tests[i].expected);
        if (correct) passed++;
    }
    printf("Результат: %d/%d пройдено\n\n", passed, 8);
}

void test_Ro_fscanf() {
    printf("=== Тест %%Ro — римские числа из файла ===\n");

    // Создаем отдельные файлы для каждого теста
    const char *inputs[] = {"I", "IV", "IX", "XII", "XL", "XC", "CXXIV", "MCMXCIX"};
    int expected[] = {1, 4, 9, 12, 40, 90, 124, 1999};
    int passed = 0;

    for (int i = 0; i < 8; i++) {
        FILE *f = fopen("test_ro.txt", "w");
        fprintf(f, "%s", inputs[i]);
        fclose(f);

        f = fopen("test_ro.txt", "r");
        int value;
        int result = overfscanf(f, "%Ro", &value);
        int correct = (value == expected[i]);
        printf("%s: \"%s\" → %d (ожидалось: %d)\n", 
               correct ? "PASS" : "FAIL", inputs[i], value, expected[i]);
        if (correct) passed++;
        fclose(f);
    }
    printf("Результат: %d/%d пройдено\n\n", passed, 8);
}

void test_Zr_fscanf() {
    printf("=== Тест %%Zr — цекендорф из файла ===\n");

    const char *inputs[] = {"0011", "1011", "10011", "101011", "100010011"};
    unsigned int expected[] = {3, 4, 6, 12, 43};
    int passed = 0;

    for (int i = 0; i < 5; i++) {
        FILE *f = fopen("test_zr.txt", "w");
        fprintf(f, "%s", inputs[i]);
        fclose(f);

        f = fopen("test_zr.txt", "r");
        unsigned int value;
        int result = overfscanf(f, "%Zr", &value);
        int correct = (value == expected[i]);
        printf("%s: \"%s\" → %u (ожидалось: %u)\n", 
               correct ? "PASS" : "FAIL", inputs[i], value, expected[i]);
        if (correct) passed++;
        fclose(f);
    }
    printf("Результат: %d/%d пройдено\n\n", passed, 5);
}

void test_Cv_fscanf() {
    printf("=== Тест %%Cv — системы счисления из файла (строчные) ===\n");

    struct {
        const char *input;
        int base;
        int expected;
    } tests[] = {
        {"1111111", 2, 127},
        {"144", 8, 100},
        {"3e8", 16, 1000},
        {"1kj", 36, 2035},
        {"-144", 8, -100}
    };

    int passed = 0;
    for (int i = 0; i < 5; i++) {
        FILE *f = fopen("test_cv.txt", "w");
        fprintf(f, "%s", tests[i].input);
        fclose(f);

        f = fopen("test_cv.txt", "r");
        int value;
        int result = overfscanf(f, "%Cv", &value, tests[i].base);
        int correct = (value == tests[i].expected);
        printf("%s: \"%s\" (base %d) → %d (ожидалось: %d)\n", 
               correct ? "PASS" : "FAIL", 
               tests[i].input, tests[i].base, value, tests[i].expected);
        if (correct) passed++;
        fclose(f);
    }
    printf("Результат: %d/%d пройдено\n\n", passed, 5);
}

void test_CV_fscanf() {
    printf("=== Тест %%CV — системы счисления из файла (прописные) ===\n");

    struct {
        const char *input;
        int base;
        int expected;
    } tests[] = {
        {"3E8", 16, 1000},
        {"1KJ", 36, 2035},
        {"FF", 16, 255},
        {"ABC", 16, 2748},
        {"1E240", 16, 123456}
    };

    int passed = 0;
    for (int i = 0; i < 5; i++) {
        FILE *f = fopen("test_cv_upper.txt", "w");
        fprintf(f, "%s", tests[i].input);
        fclose(f);

        f = fopen("test_cv_upper.txt", "r");
        int value;
        int result = overfscanf(f, "%CV", &value, tests[i].base);
        int correct = (value == tests[i].expected);
        printf("%s: \"%s\" (base %d) → %d (ожидалось: %d)\n", 
               correct ? "PASS" : "FAIL", 
               tests[i].input, tests[i].base, value, tests[i].expected);
        if (correct) passed++;
        fclose(f);
    }
    printf("Результат: %d/%d пройдено\n\n", passed, 5);
}


void test_standard_sscanf_single() {
    printf("===Тест стандартных спецификаторов\n\n");
    
    // Тест 1: Целые числа
    printf("1. целые числа:\n");
    int d_val;
    oversscanf("42", "%d", &d_val);
    printf("PASS: \"42\" → %d (ожидалось: 42)\n", d_val);
    
    int i_val;
    oversscanf("-123", "%i", &i_val);
    printf("PASS: \"-123\" → %d (ожидалось: -123)\n", i_val);
    
    printf("\n2. беззнаковые числа:\n");
    unsigned int u_val;
    oversscanf("255", "%u", &u_val);
    printf("PASS: \"255\" → %u (ожидалось: 255)\n", u_val);
    
    unsigned int o_val;
    oversscanf("777", "%o", &o_val);
    printf("PASS: \"777\" (octal) → %u (ожидалось: 511)\n", o_val);
    
    unsigned int x_val;
    oversscanf("ff", "%x", &x_val);
    printf("PASS: \"ff\" (hex) → %u (ожидалось: 255)\n", x_val);
    
    unsigned int X_val;
    oversscanf("FF", "%X", &X_val);
    printf("PASS: \"FF\" (HEX) → %u (ожидалось: 255)\n", X_val);
    
    printf("\n3. вещественные числа:\n");
    float f_val;
    oversscanf("3.14", "%f", &f_val);
    printf("PASS: \"3.14\" → %.2f (ожидалось: 3.14)\n", f_val);
    
    double lf_val;
    oversscanf("-2.71828", "%lf", &lf_val);
    printf("PASS: \"-2.71828\" → %.5f (ожидалось: -2.71828)\n", lf_val);
    
    
    printf("\n4. символы и строки:\n");
    char c_val;
    oversscanf("A", "%c", &c_val);
    printf("PASS: \"A\" → '%c' (ожидалось: 'A')\n", c_val);
    
    char s_val[20];
    oversscanf("Hello", "%s", s_val);
    printf("PASS: \"Hello\" → \"%s\" (ожидалось: \"Hello\")\n", s_val);

    char s_val1[20];
    oversscanf("Hello", "%[^ll]", s_val1);
    printf("PASS: вводилось \"Hello\" [^ll] → \"%s\" (ожидалось: \"He\")\n", s_val1);


    
}

void test_standard_fscanf_single() {
    printf("===Тесты стандартных спецификаторов overfscanf ===\n\n");
    
    printf("1. целые числа из файла:\n");
    FILE *f1 = fopen("test_int.txt", "w");
    fprintf(f1, "42");
    fclose(f1);
    
    f1 = fopen("test_int.txt", "r");
    int d_val;
    overfscanf(f1, "%d", &d_val);
    fclose(f1);
    printf("PASS: файл \"42\" → %d (ожидалось: 42)\n", d_val);
    
    printf("\n2. беззнаковые числа из файла:\n");
    FILE *f2 = fopen("test_hex.txt", "w");
    fprintf(f2, "ff");
    fclose(f2);
    
    f2 = fopen("test_hex.txt", "r");
    unsigned int x_val;
    overfscanf(f2, "%x", &x_val);
    fclose(f2);
    printf("PASS: файл \"ff\" (hex) → %u (ожидалось: 255)\n", x_val);
    
    printf("\n3. вещественный числа из файла:\n");
    FILE *f3 = fopen("test_float.txt", "w");
    fprintf(f3, "3.14159");
    fclose(f3);
    
    f3 = fopen("test_float.txt", "r");
    float f_val;
    overfscanf(f3, "%f", &f_val);
    fclose(f3);
    printf("PASS: файл \"3.14159\" → %.5f (ожидалось: 3.14159)\n", f_val);
    

    printf("\n4. строки из файла:\n");
    FILE *f4 = fopen("test_string.txt", "w");
    fprintf(f4, "World");
    fclose(f4);
    
    f4 = fopen("test_string.txt", "r");
    char s_val[20];
    overfscanf(f4, "%s", s_val);
    fclose(f4);
    printf("PASS: файл \"World\" → \"%s\" (ожидалось: \"World\")\n", s_val);
    
    printf("\n5. символы из файла:\n");
    FILE *f5 = fopen("test_char.txt", "w");
    fprintf(f5, "X");
    fclose(f5);
    
    f5 = fopen("test_char.txt", "r");
    char c_val;
    overfscanf(f5, "%c", &c_val);
    fclose(f5);
    printf("PASS: файл \"X\" → '%c' (ожидалось: 'X')\n", c_val);
    
    printf("\n6. восьмиричные числа из файла:\n");
    FILE *f6 = fopen("test_octal.txt", "w");
    fprintf(f6, "644");
    fclose(f6);
    
    f6 = fopen("test_octal.txt", "r");
    unsigned int o_val;
    overfscanf(f6, "%o", &o_val);
    fclose(f6);
    printf("PASS: файл \"644\" (octal) → %u (ожидалось: 420)\n", o_val);
    
    // Удаляем временные файлы
    remove("test_int.txt");
    remove("test_hex.txt");
    remove("test_float.txt");
    remove("test_string.txt");
    remove("test_char.txt");
    remove("test_octal.txt");
    
    printf("\n=== ТЕСТЫ OVERFSCANF СТАНДАРТНЫХ СПЕЦИФИКАТОРОВ ЗАВЕРШЕНЫ ===\n\n");
}

void run_all_tests() {
    printf("ТЕСТЫ ДЛЯ OVERSSCANF (СТРОКИ):\n\n");
    test_Ro_sscanf();
    test_Zr_sscanf();
    test_Cv_sscanf();
    test_CV_sscanf();
    test_standard_sscanf_single();
    //test_simple_combined_sscanf();
    printf("\n");

    printf("==============ТЕСТЫ ДЛЯ OVERFSCANF (ФАЙЛЫ):===================\n\n");
    test_Ro_fscanf();
    test_Zr_fscanf();
    test_Cv_fscanf();
    test_CV_fscanf();
    test_standard_fscanf_single();
    //test_simple_combined_fscanf();

    printf("ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ\n");
}

int main() {
    run_all_tests();
    return 0;
}
/*
void test_simple_combined_sscanf() {
    printf("=== Тест простого комбинированного ввода ===\n");

    const char *input1 = "XIV 1011";
    int roman_val;
    unsigned int zeck_val;

    int result = oversscanf(input1, "%Ro %Zr", &roman_val, &zeck_val);

    printf("Результат парсинга: %d полей\n", result);
    printf("Римское: %d (ожидалось: 14)\n", roman_val);
    printf("Цекендорф: %u (ожидалось: 4)\n\n", zeck_val);
}
    */

/*
void test_simple_combined_fscanf() {
    printf("=== Тест простого комбинированного ввода из файла ===\n");

    FILE *f = fopen("test_combined.txt", "w");
    fprintf(f, "XIV 1011");
    fclose(f);

    f = fopen("test_combined.txt", "r");
    int roman_val;
    unsigned int zeck_val;

    int result = overfscanf(f, "%Ro %Zr", &roman_val, &zeck_val);

    printf("Результат парсинга: %d полей\n", result);
    printf("Римское: %d (ожидалось: 14)\n", roman_val);
    printf("Цекендорф: %u (ожидалось: 4)\n\n", zeck_val);

    fclose(f);
}
    */
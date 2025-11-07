#include "../include/studentManager.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Компараторы для qsort
int compare_id(const void *a, const void *b){
    // Приводим указатели void* к типу Student* и вычитаем ID
    // Результат: отрицательный - a < b, 0 - равны, положительный - a > b
    return ((Student*)a)->id - ((Student*)b)->id;
}

int compare_last_name(const void *a, const void *b){
    return strcmp(((Student*)a)->lastName, ((Student*)b)->lastName);
}

int compare_first_name(const void *a, const void *b){
    return strcmp(((Student*)a)->firstName, ((Student*)b)->firstName);
}

int compare_group(const void *a, const void *b){
    return strcmp(((Student*)a)->group, ((Student*)b)->group);
}

static int atoi2(const char *str, int *value){
    if (str == NULL || value == NULL) return 0;
    
    char *endptr;
    errno = 0;
    long result = strtol(str, &endptr, 10);
    
    // Проверка ошибок преобразования
    if (errno == ERANGE || result < 0 || result > 255) return 0;
    if (endptr == str || *endptr != '\0') return 0;
    
    *value = (int)result;
    return 1;
}

static int validName(const char *name){


    if (name == NULL || strlen(name) == 0) return 0;
    
    for (int i = 0; name[i]; i++){
        if (!isalpha(name[i])){
            return 0;
        }
    }
    return 1;
}

static int validGroup(const char *group){
    if (group == NULL || strlen(group) == 0) return 0;
    
    // Группа должна содержать хотя бы одну букву и одну цифру
    int has_alpha = 0, has_digit = 0;
    for (int i = 0; group[i]; i++){
        if (isalpha(group[i])) has_alpha = 1;
        if (isdigit(group[i])) has_digit = 1;
        if (!isalnum(group[i])) return 0; // Разрешаем только буквы и цифры
    }
    return has_alpha && has_digit;
}

static int validGrade(int grade){
    return grade >= 1 && grade <= 5;
}

Status student_load(StudentManager *manager, const char *filename){
    if (manager == NULL || filename == NULL){
        return ERROR_INVALID_DATA;
    }

    FILE *file = fopen(filename, "r");
    if (!file) return ERROR_FILE_NOT_FOUND;

    int capacity = 10;
    manager->students = malloc(capacity * sizeof(Student));
    if (manager->students == NULL){
        fclose(file);
        return ERROR_MEMORY;
    }
    manager->count = 0;

    char buffer[256];
    int line_number = 0;
    int valid_lines = 0;
    
    while (fgets(buffer, sizeof(buffer), file)){
        line_number++;
        
        // Пропуск пустых строк и строк только с пробелами
        if (strspn(buffer, " \t\n") == strlen(buffer)) continue;

        if (manager->count >= capacity){
            capacity *= 2;
            Student *temp = realloc(manager->students, capacity * sizeof(Student));
            if (!temp) {
                fclose(file);
                return ERROR_MEMORY;
            }
            manager->students = temp;
        }

        Student *s = &manager->students[manager->count];
        s->grades = malloc(NUM_EXAMS * sizeof(unsigned char));
        if (!s->grades) {
            fclose(file);
            return ERROR_MEMORY;
        }

        // Временные переменные для валидации
        int temp_id;
        char temp_firstName[MAX_NAME_LENGTH] = "";
        char temp_lastName[MAX_NAME_LENGTH] = "";
        char temp_group[MAX_GROUP_LENGTH] = "";
        int temp_grades[NUM_EXAMS];
        int all_grades_valid = 1;

        char *token = strtok(buffer, " \t\n");
        if (!token || !atoi2(token, &temp_id) || temp_id <= 0){
            printf("Предупреждение: Неверный ID в строке %d\n", line_number);
            free(s->grades);
            continue;
        }
        
        token = strtok(NULL, " \t\n");

        if (!token || !validName(token)){
            printf("Предупреждение: Неверное имя в строке %d\n", line_number);
            free(s->grades);
            continue;
        }
        strncpy(temp_firstName, token, MAX_NAME_LENGTH - 1);
        
        token = strtok(NULL, " \t\n");



        if (!token || !validName(token)){
            printf("Предупреждение: Неверная фамилия в строке %d\n", line_number);
            free(s->grades);
            continue;
        }
        strncpy(temp_lastName, token, MAX_NAME_LENGTH - 1);
        
        token = strtok(NULL, " \t\n");

        if (!token || !validGroup(token)){
            printf("Предупреждение: Неверная группа в строке %d\n", line_number);
            free(s->grades);
            continue;
        }
        strncpy(temp_group, token, MAX_GROUP_LENGTH - 1);
        
        for (int i = 0; i < NUM_EXAMS; i++){
            token = strtok(NULL, " \t\n");
            if (!token || !atoi2(token, &temp_grades[i]) || 
                !validGrade(temp_grades[i])){
                printf("Предупреждение: Неверная оценка в строке %d\n", line_number);
                all_grades_valid = 0;
                break;
            }
        }

        if (!all_grades_valid) {
            free(s->grades);
            continue;
        }

        // Проверка уникальности ID
        int id_exists = 0;
        for (int i = 0; i < manager->count; i++){
            if (manager->students[i].id == temp_id) {
                printf("Предупреждение: Дублирующий ID %d в строке %d\n", temp_id, line_number);
                id_exists = 1;
                break;
            }
        }

        if (id_exists){
            free(s->grades);
            continue;
        }

        s->id = temp_id;
        strncpy(s->firstName, temp_firstName, MAX_NAME_LENGTH - 1);
        s->firstName[MAX_NAME_LENGTH - 1] = '\0';
        strncpy(s->lastName, temp_lastName, MAX_NAME_LENGTH - 1);
        s->lastName[MAX_NAME_LENGTH - 1] = '\0';
        strncpy(s->group, temp_group, MAX_GROUP_LENGTH - 1);
        s->group[MAX_GROUP_LENGTH - 1] = '\0';
        
        for (int i = 0; i < NUM_EXAMS; i++) {
            s->grades[i] = (unsigned char)temp_grades[i];
        }

        manager->count++;
        valid_lines++;
    }

    fclose(file);
    
    if (valid_lines == 0){
        printf("Не найдено ни одной корректной записи в файле\n");
        return ERROR_INVALID_DATA;
    }
    
    printf("Успешно загружено %d студентов из %d строк\n", valid_lines, line_number);
    return OK;
}

void student_free2(StudentManager *manager){
    for (int i = 0; i < manager->count; i++){
        student_free(&manager->students[i]);
    }
    free(manager->students);
    manager->count = 0;
}


void student_search_by_id(const StudentManager *manager, unsigned int id){
    int found = 0;

    for (int i = 0; i < manager->count; i++){
        if (manager->students[i].id == id){
            printf("Найден: ");
            student_print(&manager->students[i]);
            found = 1;
        }
    }
    if (!found) printf("Студент с ID %u не найден\n", id);
}

void student_search_by_name(const StudentManager *manager, const char *name, int search_by_last_name){

    int found = 0;
    char search_lower[MAX_NAME_LENGTH];

    strcpy(search_lower, name);

    for (int i = 0; search_lower[i]; i++){
        search_lower[i] = tolower(search_lower[i]);
    }

    for (int i = 0; i < manager->count; i++){

        char student_name[MAX_NAME_LENGTH];
        strcpy(student_name, search_by_last_name ? manager->students[i].lastName : manager->students[i].firstName);

        for (int j = 0; student_name[j]; j++){
            student_name[j] = tolower(student_name[j]);
        }

        if (strstr(student_name, search_lower)){
            printf("Найден: ");
            student_print(&manager->students[i]);
            found = 1;
        }
    }
    if (!found) printf("Студент с %s '%s' не найден\n", search_by_last_name ? "фамилией" : "именем", name);
}

void student_search_by_group(const StudentManager *manager, const char *group){

    int found = 0;
    for (int i = 0; i < manager->count; i++){

        if (strcmp(manager->students[i].group, group) == 0){
            printf("Найден: ");
            student_print(&manager->students[i]);
            found = 1;
        }
    }
    if (!found) printf("Студенты в группе '%s' не найдены\n", group);
}

void student_sort_by_id(StudentManager *manager){
    qsort(manager->students, manager->count, sizeof(Student), compare_id);
    printf("Сортировка по ID завершена\n");
}

void student_sort_by_last_name(StudentManager *manager){
    qsort(manager->students, manager->count, sizeof(Student), compare_last_name);
    printf("Сортировка по фамилии завершена\n");
}

void student_sort_by_first_name(StudentManager *manager){
    qsort(manager->students, manager->count, sizeof(Student), compare_first_name);
    printf("Сортировка по имени завершена\n");
}

void student_sort_by_group(StudentManager *manager){
    qsort(manager->students, manager->count, sizeof(Student), compare_group);
    printf("Сортировка по группе завершена\n");
}

Status student_write_student_trace(const StudentManager *manager, const char *filename, unsigned int id){

    FILE *file = fopen(filename, "a");
    if (!file) return ERROR_FILE_NOT_FOUND;

    int found = 0;
    for (int i = 0; i < manager->count; i++) {
        if (manager->students[i].id == id) {
            const Student *s = &manager->students[i];
            fprintf(file, "Данные студента (ID: %u):\n", id);
            fprintf(file, "ФИО: %s %s\n", s->firstName, s->lastName);
            fprintf(file, "Группа: %s\n", s->group);
            fprintf(file, "Средняя оценка: %.2f\n\n", student_calculate_average(s));
            found = 1;
            break;
        }
    }

    if (!found) fprintf(file, "Студент с ID %u не найден\n\n", id);
    fclose(file);
    return OK;
}

Status student_write_high_achievers(const StudentManager *manager, const char *filename){

    FILE *file = fopen(filename, "a");
    if (!file) return ERROR_FILE_NOT_FOUND;

    // Расчет общего среднего балла
    double total_avg = 0;
    for (int i = 0; i < manager->count; i++) {
        total_avg += student_calculate_average(&manager->students[i]);
    }
    total_avg /= manager->count;

    fprintf(file, "Студенты с баллом выше среднего (%.2f):\n", total_avg);
    int found = 0;
    for (int i = 0; i < manager->count; i++) {
        double avg = student_calculate_average(&manager->students[i]);
        if (avg > total_avg){
            fprintf(file, "%s %s (%.2f)\n", manager->students[i].lastName, manager->students[i].firstName, avg);
            found = 1;
        }
    }
    if (!found) fprintf(file, "Не найдено\n");

    fprintf(file, "\n");

    fclose(file);
    return OK;
}

void student_print_all(const StudentManager *manager){
    printf("\nВсе студенты (%d):\n", manager->count);

    for (int i = 0; i < manager->count; i++){
        printf("%d. ", i + 1);
        student_print(&manager->students[i]);
    }
}
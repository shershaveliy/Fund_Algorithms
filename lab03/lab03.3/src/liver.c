#include "../include/liver.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

//Используем при невалидных значениях или для инициализации
Liver create_invalid_liver(void){
    Liver inv;
    inv.id = 0;
    strcpy(inv.surname, "INVALID");
    strcpy(inv.name, "INVALID");
    inv.patronymic[0] = '\0';
    inv.day = inv.month = inv.year = 0;
    inv.gender = 'X';
    inv.income = -1.0;
    return inv;
}

void delete_liver(Liver l){
    (void)l;
}

Liver copy_liver(Liver l){ //Простое присваивание т.к. структура без указателей
    return l;
}

int compare_livers(Liver a, Liver b){
    if (a.id < b.id) return -1;
    if (a.id > b.id) return 1;
    return 0;
}

//Получение даты
static void get_today(int *d, int *m, int *y){
    SYSTEMTIME st;
    GetLocalTime(&st);  // Прямой вызов Windows API
    
    *d = st.wDay;
    *m = st.wMonth; 
    *y = st.wYear;
}

int calculate_age(const Liver *l){
    int dd, mm, yy;
    get_today(&dd, &mm, &yy);
    
    int age = yy - l->year;
    if (mm < l->month || (mm == l->month && dd < l->day)) 
        age--;
    
    return age;
}

//Сравнение по возрасту
int compare_by_age_for_insert(const Liver *a, const Liver *b){
    int age_a = calculate_age(a);
    int age_b = calculate_age(b);
    if (age_a < age_b) return -1;
    if (age_a > age_b) return 1;
    if (a->id < b->id) return -1;
    if (a->id > b->id) return 1;
    return 0;
}

//Валидация
int is_alpha_string(const char *s){
    if (!s || s[0] == '\0') return 0;
    for (size_t i = 0; s[i]; ++i) {
        if (!isalpha((unsigned char)s[i])) return 0;
    }
    return 1;
}

int is_future_date(int day, int month, int year){
    int current_day, current_month, current_year;
    get_today(&current_day, &current_month, &current_year);
    
    if (year > current_year) return 1;
    
    if (year == current_year && month > current_month) return 1;
    
    if (year == current_year && month == current_month && day > current_day) return 1;
    
    return 0;
}

int is_valid_date(int day, int month, int year){
    if (year < 1900 || year > 9999) return 0;
    if (month < 1 || month > 12) return 0;
    int mdays[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    int maxd = mdays[month-1];
    if (month == 2 && ((year%4==0 && year%100!=0) || (year%400==0))) maxd = 29;
    if (day < 1 || day > maxd) return 0;

    if (is_future_date(day, month, year)){
        return 0;
    }

    return 1;
}

//Парсинг строки из файла
int parse_line_to_liver(const char *line, Liver *out){
    unsigned int id_u;
    char s1[128], s2[128], s3[128];
    int day, month, year;
    char gender;
    double income;

    int scanned9 = sscanf(line, "%u %127s %127s %127s %d %d %d %c %lf", &id_u, s1, s2, s3, &day, &month, &year, &gender, &income);
    if (scanned9 == 9){
        out->id = id_u;
        strncpy(out->surname, s1, sizeof(out->surname)-1);
        out->surname[sizeof(out->surname)-1] = '\0';

        strncpy(out->name, s2, sizeof(out->name)-1);
        out->name[sizeof(out->name)-1] = '\0';

        strncpy(out->patronymic, s3, sizeof(out->patronymic)-1);
        out->patronymic[sizeof(out->patronymic)-1] = '\0';

        out->day = day; out->month = month; out->year = year;
        out->gender = gender;
        out->income = income;
        return 1;
    }
    //Если нет отчества
    int scanned8 = sscanf(line, "%u %127s %127s %d %d %d %c %lf", &id_u, s1, s2, &day, &month, &year, &gender, &income);
    if (scanned8 == 8){
        out->id = id_u;
        strncpy(out->surname, s1, sizeof(out->surname)-1);
        out->surname[sizeof(out->surname)-1] = '\0';

        strncpy(out->name, s2, sizeof(out->name)-1);
        out->name[sizeof(out->name)-1] = '\0';

        out->patronymic[0] = '\0';
        out->day = day; out->month = month; out->year = year;
        out->gender = gender;
        out->income = income;
        return 1;
    }

    return 0;
}


void insert_sorted_by_age(Liver_List *list, Liver val){
    if (list->size == 0){
        Liver_push_front_list(list, val);
        return;
    }
    /* Поиск позиции для вставки.
    Проходим по списку, находим первый элемент, который должен быть после нового
    и вставляем новый элемент перед ним*/
    Liver_Node *cur = list->head;
    size_t pos = 0;
    while (cur){
        Liver cur_val = *(cur->data);
        int cmp = compare_by_age_for_insert(&cur_val, &val);
        if (cmp > 0) {
            Liver_insert_at_list(list, pos, val);
            return;
        }
        cur = cur->next;
        pos++;
    }
    Liver_push_back_list(list, val);
}

//Читаем весь файл
Liver_List read_from_file(const char *filename){
    Liver_List list = Liver_create_list(delete_liver, copy_liver, compare_livers, create_invalid_liver());
    FILE *f = fopen(filename, "r");
    if (!f){
        fprintf(stderr, "Ошибка: не удалось открыть файл '%s'\n", filename);
        return list;
    }

    char buf[512];
    size_t total_lines = 0;

    while (fgets(buf, sizeof(buf), f)){
        total_lines++;
        size_t L = strlen(buf);

        if (L > 0 && (buf[L-1] == '\n' || buf[L-1] == '\r')){
            while (L > 0 && (buf[L-1] == '\n' || buf[L-1] == '\r')){
                buf[--L] = '\0';
            }
        }
        if (buf[0] == '\0') continue;

        Liver lv;
        if (!parse_line_to_liver(buf, &lv)){
            fprintf(stderr, "Пропуск: неверный формат строки (№%zu): %s\n", total_lines, buf);
            continue;
        }

        if (!is_alpha_string(lv.surname) || !is_alpha_string(lv.name)){
            fprintf(stderr, "Ошибка: некорректные символы в ФИО для ID %u\n", lv.id);
            continue;
        }
        if (strlen(lv.patronymic) > 0 && !is_alpha_string(lv.patronymic)){
            fprintf(stderr, "Ошибка: некорректные символы в отчестве для ID %u\n", lv.id);
            continue;
        }
        if (!is_valid_date(lv.day, lv.month, lv.year)){
            fprintf(stderr, "Ошибка: некорректная дата для ID %u\n", lv.id);
            continue;
        }
        if (!(lv.gender == 'M' || lv.gender == 'W')){
            fprintf(stderr, "Ошибка: некорректный пол для ID %u\n", lv.id);
            continue;
        }
        if (lv.income < 0.0) {
            fprintf(stderr, "Ошибка: отрицательный доход для ID %u\n", lv.id);
            continue;
        }

        insert_sorted_by_age(&list, lv);
    }

    fclose(f);
    printf("Загружено %zu жителей (прочитано строк: %zu) из %s\n", list.size, total_lines, filename);
    return list;
}

void save_to_file(const Liver_List *list, const char *filename){
    FILE *f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Ошибка: не удалось создать файл '%s'\n", filename);
        return;
    }
    Liver_Node *cur = list->head;
    while (cur) {
        Liver lv = *(cur->data);
        fprintf(f, "%u %s %s %s %d %d %d %c %.2lf\n",
                lv.id, lv.surname, lv.name, lv.patronymic,
                lv.day, lv.month, lv.year, lv.gender, lv.income);
        cur = cur->next;
    }
    fclose(f);
    printf("Данные сохранены в %s\n", filename);
}

void display_residents(const Liver_List *list){
    printf("\n--- Список (%zu) ---\n", list->size);
    if (list->size == 0) {
        printf("Пусто\n"); 
        return;
    }
    Liver_Node *cur = list->head;
    while (cur) {
        Liver lv = *(cur->data);
        int age = calculate_age(&lv);
        printf("ID=%u %s %s %s %02d.%02d.%04d age=%d gender=%c income=%.2lf\n",
               lv.id, lv.surname, lv.name, lv.patronymic,
               lv.day, lv.month, lv.year, age, lv.gender, lv.income);
        cur = cur->next;
    }
}
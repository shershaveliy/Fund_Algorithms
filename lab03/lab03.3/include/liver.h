#ifndef LIVER_H
#define LIVER_H

#include <stddef.h>
#include "list.h" /* ваш макрос DEFINE_LINKED_LIST(LIST_TYPE, NAME) */

/* Описание структуры Liver (как в вашем рабочем коде) */
typedef struct {
    unsigned int id;
    char surname[50];
    char name[50];
    char patronymic[50]; /* допускается пустая строка */
    int day;
    int month;
    int year;
    char gender; /* 'M' или 'W' */
    double income; /* >=0 */
} Liver;

/* "invalid" значение */
Liver create_invalid_liver(void);

/* Функции-адаптеры для списка */
void delete_liver(Liver l);
Liver copy_liver(Liver l);
int compare_livers(Liver a, Liver b);

/* Вспомогательные функции */
int calculate_age(const Liver *l);
int compare_by_age_for_insert(const Liver *a, const Liver *b);
int is_alpha_string(const char *s);
int is_valid_date(int day, int month, int year);

/* Парсинг одной строки в Liver */
int parse_line_to_liver(const char *line, Liver *out);

/* Операции со списком (публичные для main/undo)
   - вставка по возрасту
   - чтение/сохранение/отображение/поиск и CRUD
*/
void insert_sorted_by_age(Liver_List *list, Liver val);
LinkedList /* not used: kept for compatibility */;

/* NOTE: макрос разворачивается и даёт:
   types: Liver_Node, Liver_List
   функции: Liver_create_list, Liver_push_back_list, Liver_push_front_list, Liver_pop_back_list, ...
*/
DEFINE_LINKED_LIST(Liver, Liver)

#endif /* LIVER_H */

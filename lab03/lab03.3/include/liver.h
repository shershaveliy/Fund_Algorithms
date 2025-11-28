#ifndef LIVER_H
#define LIVER_H

#include "list.h"

typedef struct {
    unsigned int id;
    char surname[50];
    char name[50];
    char patronymic[50]; //Отчество может быть пустым
    int day, month, year;
    char gender;
    double income; //Доход
} Liver;

DEFINE_LINKED_LIST(Liver, Liver)

Liver create_invalid_liver(void);
void delete_liver(Liver l);
Liver copy_liver(Liver l);
int compare_livers(Liver a, Liver b);

int calculate_age(const Liver *l);
int is_alpha_string(const char *s);
int is_valid_date(int d, int m, int y);

int parse_line_to_liver(const char *line, Liver *out);

void insert_sorted_by_age(Liver_List *list, Liver v);
Liver_List read_from_file(const char *filename);
void save_to_file(const Liver_List *list, const char *filename);
void display_residents(const Liver_List *list);

#endif

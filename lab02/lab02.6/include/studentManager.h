#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "student.h"

typedef struct{
    Student *students;
    int count;
} StudentManager;


Status student_load(StudentManager *manager, const char *filename);

void student_free2(StudentManager *manager);

void student_search_by_id(const StudentManager *manager, unsigned int id);
void student_search_by_name(const StudentManager *manager, const char *name, int search_by_last_name);
void student_search_by_group(const StudentManager *manager, const char *group);

void student_sort_by_id(StudentManager *manager);
void student_sort_by_last_name(StudentManager *manager);
void student_sort_by_first_name(StudentManager *manager);
void student_sort_by_group(StudentManager *manager);

// Работа с файлами
Status student_write_student_trace(const StudentManager *manager, const char *filename, unsigned int id);
Status student_write_high_achievers(const StudentManager *manager, const char *filename);

void student_print_all(const StudentManager *manager);

#endif
#ifndef STUDENT_H
#define STUDENT_H

#include "status.h"

#define MAX_NAME_LENGTH 50
#define MAX_GROUP_LENGTH 20
#define NUM_EXAMS 5

typedef struct{
    unsigned int id;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char group[MAX_GROUP_LENGTH];
    unsigned char *grades;
} Student;

double student_calculate_average(const Student *student);
void student_print(const Student *student);
void student_free(Student *student);

#endif
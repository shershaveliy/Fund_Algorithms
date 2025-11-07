#include "../include/student.h"
#include <stdlib.h>
#include <stdio.h>

double student_calculate_average(const Student *student){
    if (student == NULL || student->grades == NULL) return 0.0;
    
    double sum = 0;
    for (int i = 0; i < NUM_EXAMS; i++){
        sum += student->grades[i];
    }
    return sum / NUM_EXAMS;
}

void student_print(const Student *student){
    if (student == NULL) return;
    
    printf("ID: %u, Имя: %s %s, Группа: %s, Средний балл: %.2f\n", 
           student->id, student->firstName, student->lastName, 
           student->group, student_calculate_average(student));
}

void student_free(Student *student){
    if (student != NULL && student->grades != NULL){
        free(student->grades);
    }
}
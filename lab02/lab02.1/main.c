#include "include/number.h"
#include "include/status.h"
#include <stdio.h>
#include <stdlib.h>

void print_results(bool* results, int count){
    for(int i = 0; i < count; i++){
        printf("Дробь %d: %s\n", i + 1, results[i] ? "конечная" : "бесконечная");
    }
}

int main(){
    bool* results = NULL;
    
    Status status = check_all(&results, 2, 4, 0.5, 0.25, 0.2, 0.125874824828482482384723848237482347828748324);
    if(status == OK){
        print_results(results, 4);
        free(results);
    } 
    else{
        print_status(status);
    }


    status = check_all(&results, 2656572, 3, 0.5, 0.2, 0.333);
    if(status == OK){
        print_results(results, 3);
        free(results);
    }
    else{
        print_status(status);
    }

    return 0;
}
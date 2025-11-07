#include "include/studentManager.h"
#include "include/status.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){


    if (argc < 2){
        printf("Использование: %s <файл_студентов> [файл_трассировки]\n", argv[0]);
        return 1;
    }

    StudentManager manager = {0};
    Status status = student_load(&manager, argv[1]);

    if (status != OK){
        print_status(status);
        return 1;
    }

    printf("Загружено %d студентов\n", manager.count);

    char trace_file[100] = "";

    if (argc >= 3){
        strcpy(trace_file, argv[2]);
        printf("Файл трассировки: %s\n", trace_file);
    }

    int choice;
    do{
        printf("\n=== Система управления студентами ===\n");
        printf("1. Поиск по ID\n");
        printf("2. Поиск по фамилии\n");
        printf("3. Поиск по имени\n");
        printf("4. Поиск по группе\n");
        printf("5. Сортировка по ID\n");
        printf("6. Сортировка по фамилии\n");
        printf("7. Сортировка по имени\n");
        printf("8. Сортировка по группе\n");
        printf("9. Запись в файл трассировки (по ID)\n");
        printf("10. Запись отличников в файл\n");
        printf("11. Показать всех студентов\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        
        scanf("%d", &choice);
        
        switch (choice){
            case 1:{
                unsigned int id;
                printf("Введите ID: ");
                scanf("%u", &id);
                student_search_by_id(&manager, id);
                break;
            }
            case 2:{
                char name[MAX_NAME_LENGTH];
                printf("Введите фамилию: ");
                scanf("%s", name);
                student_search_by_name(&manager, name, 1);
                break;
            }
            case 3:{
                char name[MAX_NAME_LENGTH];
                printf("Введите имя: ");
                scanf("%s", name);
                student_search_by_name(&manager, name, 0);
                break;
            }
            case 4:{
                char group[MAX_GROUP_LENGTH];
                printf("Введите группу: ");
                scanf("%s", group);
                student_search_by_group(&manager, group);
                break;
            }
            case 5: student_sort_by_id(&manager); break;
            case 6: student_sort_by_last_name(&manager); break;
            case 7: student_sort_by_first_name(&manager); break;
            case 8: student_sort_by_group(&manager); break;
            case 9: {
                if (!trace_file[0]){
                    print_status(ERROR_NO_TRACE_FILE);
                    break;
                }
                unsigned int id;
                printf("Введите ID студента: ");
                scanf("%u", &id);
                status = student_write_student_trace(&manager, trace_file, id);
                print_status(status);
                break;
            }
            case 10:{
                if (!trace_file[0]){
                    print_status(ERROR_NO_TRACE_FILE);
                    break;
                }
                status = student_write_high_achievers(&manager, trace_file);
                print_status(status);
                break;
            }
            case 11: student_print_all(&manager); break;
            case 0: printf("Выход...\n"); break;
            default: printf("Неверный выбор\n");
        }
    } while (choice != 0);

    student_free2(&manager);
    return 0;
}
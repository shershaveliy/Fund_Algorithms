#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/liver.h"
#include "include/undo.h"


static void print_menu(void){
    puts("\n=== МЕНЮ ===");
    puts("1 - Показать всех жителей");
    puts("2 - Поиск");
    puts("3 - Изменить жителя");
    puts("4 - Добавить жителя");
    puts("5 - Удалить жителя");
    puts("6 - Сохранить в файл");
    puts("7 - Отменить последние N/2 модификаций (Undo)");
    puts("0 - Выход");
    printf("Выберите: ");
}

static void search_residents(const Liver_List *list){
    printf("\n--- Поиск ---\n1) По ID\n2) По фамилии\n3) По имени\n4) По полу\n5) По диапазону дохода\nВыберите: ");

    int choice;
    if (scanf("%d", &choice) != 1){
        while (getchar()!='\n');
        puts("Ошибка ввода");
        return;
    }

    int found = 0;
    Liver_Node *cur = list->head;

    if (choice == 1){

        unsigned id;
        printf("Введите ID: ");
        scanf("%u", &id);

        while (cur){
            if (cur->data->id == id){
                int age = calculate_age(cur->data);
                printf("Найден: ID=%u, %s %s %s, %02d.%02d.%04d (возраст %d), %c, доход %.2lf\n",
                       cur->data->id, cur->data->surname, cur->data->name, cur->data->patronymic,
                       cur->data->day, cur->data->month, cur->data->year, age, cur->data->gender, cur->data->income);
                found = 1; break;
            }
            cur = cur->next;
        }
    }
    else if (choice == 2){
        char s[50];
        printf("Введите фамилию: ");
        scanf("%49s", s);

        while (cur){
            if (strcmp(cur->data->surname, s) == 0){
                int age = calculate_age(cur->data);
                printf("Найден: ID=%u, %s %s %s, age=%d, %c, income=%.2lf\n",
                       cur->data->id, cur->data->surname, cur->data->name, cur->data->patronymic,
                       age, cur->data->gender, cur->data->income);
                found = 1;
            }
            cur = cur->next;
        }
    }
    else if (choice == 3){
        char s[50];
        printf("Введите имя: ");
        scanf("%49s", s);

        while (cur){
            if (strcmp(cur->data->name, s) == 0){
                int age = calculate_age(cur->data);
                printf("Найден: ID=%u, %s %s %s, age=%d, %c, income=%.2lf\n",
                       cur->data->id, cur->data->surname, cur->data->name, cur->data->patronymic,
                       age, cur->data->gender, cur->data->income);
                found = 1;
            }
            cur = cur->next;
        }
    }
    else if (choice == 4){
        char g;
        printf("Введите пол (M/W): ");
        scanf(" %c", &g);

        while (cur){
            if (cur->data->gender == g){
                int age = calculate_age(cur->data);
                printf("Найден: ID=%u, %s %s %s, age=%d, income=%.2lf\n",
                       cur->data->id, cur->data->surname, cur->data->name, cur->data->patronymic,
                       age, cur->data->income);
                found = 1;
            }
            cur = cur->next;
        }
    }
    else if (choice == 5){

        double minv, maxv;
        printf("Введите минимальный доход: "); scanf("%lf", &minv);
        printf("Введите максимальный доход: "); scanf("%lf", &maxv);
        while (cur){
            if (cur->data->income >= minv && cur->data->income <= maxv){
                int age = calculate_age(cur->data);
                printf("Найден: ID=%u, %s %s %s, age=%d, income=%.2lf\n",
                       cur->data->id, cur->data->surname, cur->data->name, cur->data->patronymic,
                       age, cur->data->income);
                found = 1;
            }
            cur = cur->next;
        }
    }
    else{
        puts("Неверный выбор");
        return;
    }

    if (!found) puts("Жители по заданным критериям не найдены");
}


static void add_resident(Liver_List *list){
    Liver lv;
    printf("\n--- Добавление нового жителя ---\n");
    printf("Введите ID: ");
    if (scanf("%u", &lv.id) != 1){
        while (getchar()!='\n');
        puts("Ошибка ввода");
        return;
    }

    for (Liver_Node *n = list->head; n; n = n->next){
        if (n->data->id == lv.id){
            puts("Ошибка: житель с таким ID уже существует");
            return;
        }
    }

    printf("Введите фамилию: ");
    scanf("%49s", lv.surname);
    if (!is_alpha_string(lv.surname)){
        puts("Ошибка: фамилия только буквы");
        return;
    }

    printf("Введите имя: ");
    scanf("%49s", lv.name);
    if (!is_alpha_string(lv.name)){
        puts("Ошибка: имя только буквы");
        return;
    }

    printf("Введите отчество (введите '-' если нет): ");
    char tmp[50];
    scanf("%49s", tmp);
    if (strcmp(tmp, "-") == 0) lv.patronymic[0] = '\0';
    else{
        strncpy(lv.patronymic, tmp, sizeof(lv.patronymic)-1);
        lv.patronymic[sizeof(lv.patronymic)-1] = '\0';
    }

    if (strlen(lv.patronymic) > 0 && !is_alpha_string(lv.patronymic)){
        puts("Ошибка: отчество только буквы");
        return;
    }

    printf("Введите дату рождения (день месяц год): ");
    if (scanf("%d %d %d", &lv.day, &lv.month, &lv.year) != 3){
        while (getchar()!='\n');
        puts("Ошибка ввода");
        return;
    }
    if (!is_valid_date(lv.day, lv.month, lv.year)){
        puts("Ошибка: некорректная дата");
        return;
    }

    printf("Введите пол (M/W): ");
    scanf(" %c", &lv.gender);
    if (!(lv.gender == 'M' || lv.gender == 'W')){
        puts("Ошибка: пол должен быть M или W");
        return;
    }

    printf("Введите средний доход: ");
    if (scanf("%lf", &lv.income) != 1){
        while (getchar()!='\n');
        puts("Ошибка ввода");
        return;
    }
    if (lv.income < 0){
        puts("Ошибка: доход не может быть отрицательным");
        return;
    }

    //Вставка в отсортированный по возрасту список
    insert_sorted_by_age(list, lv);

    //Сохраняем операцию для undo
    Operation op = {
        OP_ADD,
        lv,
        create_invalid_liver(),
        0
    };
    if (!push_operation(&op)) fprintf(stderr, "Предупреждение: не удалось сохранить операцию (undo)\n");

    puts("Житель успешно добавлен");
}

static void remove_resident(Liver_List *list){

    unsigned int remove_id;
    printf("Введите ID жителя для удаления: ");
    if (scanf("%u", &remove_id) != 1){
        while (getchar()!='\n');
        puts("Ошибка ввода");
        return;
    }

    Liver_Node *cur = list->head;
    size_t index = 0;
    while (cur != NULL && cur->data->id != remove_id){
        cur = cur->next;
        index++;
    }

    if (cur == NULL){
        printf("Житель с ID %u не найден\n", remove_id);
        return;
    }

    Operation op;
    op.type = OP_DELETE;
    op.data = *(cur->data);
    op.old_data = create_invalid_liver();
    op.index = index;
    if (!push_operation(&op)) fprintf(stderr, "Предупреждение: не удалось сохранить операцию (undo)\n");

    Liver_delete_at_list(list, index);
    printf("Житель ID=%u успешно удалён\n", remove_id);
}

static void modify_resident(Liver_List *list){
    unsigned int modify_id;
    printf("Введите ID жителя для изменения: ");
    if (scanf("%u", &modify_id) != 1){
        while (getchar()!='\n');
        puts("Ошибка ввода");
        return;
    }

    Liver_Node *cur = list->head;
    size_t index = 0;
    while (cur != NULL && cur->data->id != modify_id){
        cur = cur->next;
        index++;
    }

    if (cur == NULL){
        printf("Житель с ID %u не найден\n", modify_id);
        return;
    }

    Liver old_data = *(cur->data);
    Liver modified = old_data;

    puts("\nЧто изменить?");
    puts("1. Фамилию\n2. Имя\n3. Отчество\n4. Дату рождения\n5. Пол\n6. Доход");
    printf("Выберите: ");
    int choice;
    if (scanf("%d", &choice) != 1){
        while (getchar()!='\n');
        puts("Ошибка ввода");
        return;
    }

    switch (choice){
        case 1:
            printf("Введите новую фамилию: ");
            scanf("%49s", modified.surname);
            if (!is_alpha_string(modified.surname)){
                puts("Ошибка: фамилия должна содержать только буквы");
                return;
            }
            break;
        case 2:
            printf("Введите новое имя: ");
            scanf("%49s", modified.name);
            if (!is_alpha_string(modified.name)){
                puts("Ошибка: имя должно содержать только буквы");
                return;
            }
            break;
        case 3:{
            char tmp[50];
            printf("Введите новое отчество (введите '-' если пустое): ");
            scanf("%49s", tmp);
            if (strcmp(tmp, "-") == 0) modified.patronymic[0] = '\0';
            else{
                strncpy(modified.patronymic, tmp, sizeof(modified.patronymic)-1);
                modified.patronymic[sizeof(modified.patronymic)-1] = '\0';
            }
            if (strlen(modified.patronymic) > 0 && !is_alpha_string(modified.patronymic)){
                puts("Ошибка: отчество должно содержать только буквы"); 
                return; 
            }
            break;
        }
        case 4:
            printf("Введите новую дату (день месяц год): ");
            if (scanf("%d %d %d", &modified.day, &modified.month, &modified.year) != 3){ 
                while (getchar()!='\n'); 
                puts("Ошибка ввода"); 
                return; 
            }
            if (!is_valid_date(modified.day, modified.month, modified.year)){
                puts("Ошибка: некорректная дата"); 
                return; 
            }
            break;
        case 5:
            printf("Введите новый пол (M/W): "); 
            scanf(" %c", &modified.gender);
            if (!(modified.gender == 'M' || modified.gender == 'W')){ 
                puts("Ошибка: пол должен быть M или W"); 
                return; 
            }
            break;
        case 6:
            printf("Введите новый доход: "); 
            if (scanf("%lf", &modified.income) != 1){ 
                while (getchar()!='\n'); 
                puts("Ошибка ввода"); 
                return; 
            }
            if (modified.income < 0){ 
                puts("Ошибка: доход не может быть отрицательным"); 
                return; 
            }
            break;
        default:
            puts("Неверный выбор"); return;
    }

    //Удаляем старую запись и вставляем новую (в упорядоченное место)
    Liver_delete_at_list(list, index);
    insert_sorted_by_age(list, modified);

    Operation op;
    op.type = OP_MODIFY;
    op.data = modified;
    op.old_data = old_data;
    op.index = index;
    if (!push_operation(&op)) fprintf(stderr, "Предупреждение: не удалось сохранить операцию (undo)\n");

    puts("Данные успешно изменены");
}


int main(void){

    Liver_List list = Liver_create_list(delete_liver, copy_liver, compare_livers, create_invalid_liver());
    free_undo_storage();

    char filename[260];
    printf("Введите имя файла для загрузки данных: ");
    if (scanf("%259s", filename) != 1){ 
        fprintf(stderr, "Ошибка ввода\n"); 
        return 1; 
    }

    Liver_List loaded = read_from_file(filename);

    list = loaded;

    int choice;
    do{
        print_menu();
        if (scanf("%d", &choice) != 1){ 
            while (getchar()!='\n'); 
            puts("Ошибка ввода"); 
            continue; 
        }
        switch (choice){
            case 1: display_residents(&list); break;
            case 2: search_residents(&list); break;
            case 3: modify_resident(&list); break;
            case 4: add_resident(&list); break;
            case 5: remove_resident(&list); break;
            case 6:{
                char outname[260];
                printf("Введите имя файла для сохранения: ");
                if (scanf("%259s", outname) != 1){
                    puts("Ошибка ввода"); 
                    break; 
                }
                save_to_file(&list, outname);
                break;
            }
            case 7: undo_operations(&list); break;
            case 0: puts("Выход..."); break;
            default: puts("Неверный выбор"); break;
        }
    } while (choice != 0);

    Liver_delete_list(&list);
    free_undo_storage();
    return 0;
}

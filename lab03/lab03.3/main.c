#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/liver.h"
#include "include/undo.h"

/* We already have macro expansions in include headers:
   - Liver_List / Liver_Node and Liver_* functions
   - Operation_List / Operation_Node and Operation_* functions
   so we can use them below.
*/

/* forward declarations for functions implemented in liver.c */
int parse_line_to_liver(const char *line, Liver *out);
void insert_sorted_by_age(Liver_List *list, Liver val);
Liver create_invalid_liver(void);
void display_residents(const Liver_List *list);
void save_to_file(const Liver_List *list, const char *filename);

/* -- Local (menu) functions using the Liver_List API -- */

/* search_residents - interactive search (moved from original main) */
static void search_residents(const Liver_List *list) {
    printf("\n--- Поиск ---\n1) По ID\n2) По фамилии\n3) По имени\n4) По полу\n5) По диапазону дохода\nВыберите: ");
    int choice;
    if (scanf("%d", &choice) != 1) { while (getchar()!='\n'); printf("Ошибка ввода\n"); return; }
    int found = 0;
    Liver_Node *cur = NULL;

    if (choice == 1) {
        unsigned int id; printf("Введите ID: "); scanf("%u", &id);
        cur = Liver_List_get_node_at(& (Liver_List){ .head = NULL }, 0); /* dummy to avoid warning - not used */
        (void)cur;
        cur = ((Liver_List*)list)->head;
        while (cur) {
            if (cur->data->id == id) {
                int age = calculate_age(cur->data);
                printf("Найден: ID=%u, %s %s %s, %02d.%02d.%04d (возраст %d), %c, доход %.2lf\n",
                       cur->data->id, cur->data->surname, cur->data->name, cur->data->patronymic,
                       cur->data->day, cur->data->month, cur->data->year, age, cur->data->gender, cur->data->income);
                found = 1; break;
            }
            cur = cur->next;
        }
    } else if (choice == 2) {
        char s[50]; printf("Введите фамилию: "); scanf("%49s", s);
        cur = list->head;
        while (cur) {
            if (strcmp(cur->data->surname, s) == 0) {
                int age = calculate_age(cur->data);
                printf("Найден: ID=%u, %s %s %s, %02d.%02d.%04d (возраст %d), %c, доход %.2lf\n",
                       cur->data->id, cur->data->surname, cur->data->name, cur->data->patronymic,
                       cur->data->day, cur->data->month, cur->data->year, age, cur->data->gender, cur->data->income);
                found = 1;
            }
            cur = cur->next;
        }
    } else if (choice == 3) {
        char s[50]; printf("Введите имя: "); scanf("%49s", s);
        cur = list->head;
        while (cur) {
            if (strcmp(cur->data->name, s) == 0) {
                int age = calculate_age(cur->data);
                printf("Найден: ID=%u, %s %s %s, %02d.%02d.%04d (возраст %d), %c, доход %.2lf\n",
                       cur->data->id, cur->data->surname, cur->data->name, cur->data->patronymic,
                       cur->data->day, cur->data->month, cur->data->year, age, cur->data->gender, cur->data->income);
                found = 1;
            }
            cur = cur->next;
        }
    } else if (choice == 4) {
        char g; printf("Введите пол (M/W): "); scanf(" %c", &g);
        cur = list->head;
        while (cur) {
            if (cur->data->gender == g) {
                int age = calculate_age(cur->data);
                printf("Найден: ID=%u, %s %s %s, %02d.%02d.%04d (возраст %d), %c, доход %.2lf\n",
                       cur->data->id, cur->data->surname, cur->data->name, cur->data->patronymic,
                       cur->data->day, cur->data->month, cur->data->year, age, cur->data->gender, cur->data->income);
                found = 1;
            }
            cur = cur->next;
        }
    } else if (choice == 5) {
        double minv, maxv;
        printf("Введите min доход: "); scanf("%lf", &minv);
        printf("Введите max доход: "); scanf("%lf", &maxv);
        cur = list->head;
        while (cur) {
            if (cur->data->income >= minv && cur->data->income <= maxv) {
                int age = calculate_age(cur->data);
                printf("Найден: ID=%u, %s %s %s, %02d.%02d.%04d (возраст %d), %c, доход %.2lf\n",
                       cur->data->id, cur->data->surname, cur->data->name, cur->data->patronymic,
                       cur->data->day, cur->data->month, cur->data->year, age, cur->data->gender, cur->data->income);
                found = 1;
            }
            cur = cur->next;
        }
    } else {
        printf("Неверный выбор\n");
        return;
    }

    if (!found) printf("Жители по заданным критериям не найдены\n");
}

/* add_resident / remove_resident / modify_resident functions basically mirror original code
   but use Liver_* API and push_operation/pop_operation from undo module. */

static void add_resident(Liver_List *list) {
    Liver lv;
    printf("\n--- Добавление ---\n");
    printf("Введите ID: "); if (scanf("%u", &lv.id) != 1) { while (getchar()!='\n'); printf("Ошибка ввода\n"); return; }

    Liver_Node *cur = list->head;
    while (cur) { if (cur->data->id == lv.id) { printf("Ошибка: ID уже существует\n"); return; } cur = cur->next; }

    printf("Фамилия: "); scanf("%49s", lv.surname);
    if (!is_alpha_string(lv.surname)) { printf("Ошибка: фамилия только буквы\n"); return; }
    printf("Имя: "); scanf("%49s", lv.name);
    if (!is_alpha_string(lv.name)) { printf("Ошибка: имя только буквы\n"); return; }

    printf("Отчество (введите '-' если нет): ");
    char tmp[50]; scanf("%49s", tmp);
    if (strcmp(tmp, "-") == 0) lv.patronymic[0] = '\0'; else { strncpy(lv.patronymic, tmp, sizeof(lv.patronymic)-1); lv.patronymic[sizeof(lv.patronymic)-1]='\0'; }
    if (strlen(lv.patronymic) > 0 && !is_alpha_string(lv.patronymic)) { printf("Ошибка: отчество только буквы\n"); return; }

    printf("Дата рождения (день месяц год): "); if (scanf("%d %d %d", &lv.day, &lv.month, &lv.year) != 3) { printf("Ошибка ввода\n"); while (getchar()!='\n'); return; }
    if (!is_valid_date(lv.day, lv.month, lv.year)) { printf("Ошибка: некорректная дата\n"); return; }

    printf("Пол (M/W): "); scanf(" %c", &lv.gender);
    if (!(lv.gender == 'M' || lv.gender == 'W')) { printf("Ошибка: пол M или W\n"); return; }

    printf("Средний доход: "); if (scanf("%lf", &lv.income) != 1) { printf("Ошибка ввода\n"); while (getchar()!='\n'); return; }
    if (lv.income < 0) { printf("Ошибка: доход >=0\n"); return; }

    insert_sorted_by_age(list, lv);

    Operation op;
    op.type = OP_ADD;
    op.data = lv;
    op.old_data = create_invalid_liver();
    op.index = 0;
    if (!push_operation(&op)) fprintf(stderr, "Предупреждение: не удалось сохранить операцию (undo)\n");

    printf("Добавлено\n");
}

static void remove_resident(Liver_List *list) {
    unsigned int id;
    printf("Введите ID для удаления: ");
    if (scanf("%u", &id) != 1) { while (getchar()!='\n'); printf("Ошибка ввода\n"); return; }

    Liver_Node *cur = list->head;
    size_t idx = 0;
    while (cur && cur->data->id != id) { cur = cur->next; idx++; }
    if (!cur) { printf("Не найден ID=%u\n", id); return; }

    Operation op;
    op.type = OP_DELETE;
    op.data = *(cur->data);
    op.old_data = create_invalid_liver();
    op.index = idx;
    if (!push_operation(&op)) fprintf(stderr, "Предупреждение: не удалось сохранить операцию (undo)\n");

    delete_at_list(list, idx);
    printf("Удален ID=%u\n", id);
}

static void modify_resident(Liver_List *list) {
    unsigned int id;
    printf("Введите ID для изменения: ");
    if (scanf("%u", &id) != 1) { while (getchar()!='\n'); printf("Ошибка ввода\n"); return; }

    Liver_Node *cur = list->head;
    size_t idx = 0;
    while (cur && cur->data->id != id) { cur = cur->next; idx++; }
    if (!cur) { printf("Не найден ID=%u\n", id); return; }

    Liver old = *(cur->data);
    Liver modified = old;

    printf("Что менять?\n1-Фамилия 2-Имя 3-Отчество 4-ДР 5-Пол 6-Доход\nВыбор: ");
    int ch; if (scanf("%d", &ch) != 1) { while (getchar()!='\n'); printf("Ошибка ввода\n"); return; }
    switch (ch) {
        case 1: printf("Новая фамилия: "); scanf("%49s", modified.surname); if (!is_alpha_string(modified.surname)) { printf("Ошибка\n"); return; } break;
        case 2: printf("Новое имя: "); scanf("%49s", modified.name); if (!is_alpha_string(modified.name)) { printf("Ошибка\n"); return; } break;
        case 3: { printf("Новое отчество ( '-' если пустое ): "); char tmp[50]; scanf("%49s", tmp); if (strcmp(tmp,"-")==0) modified.patronymic[0]=0; else strncpy(modified.patronymic,tmp,sizeof(modified.patronymic)-1), modified.patronymic[sizeof(modified.patronymic)-1]=0; if (strlen(modified.patronymic)>0 && !is_alpha_string(modified.patronymic)) { printf("Ошибка\n"); return; } break; }
        case 4: printf("Новая ДР (д м г): "); if (scanf("%d %d %d", &modified.day, &modified.month, &modified.year) != 3) { printf("Ошибка ввода\n"); while (getchar()!='\n'); return; } if (!is_valid_date(modified.day, modified.month, modified.year)) { printf("Ошибка: дата\n"); return; } break;
        case 5: printf("Новый пол (M/W): "); scanf(" %c", &modified.gender); if (!(modified.gender=='M'||modified.gender=='W')) { printf("Ошибка\n"); return; } break;
        case 6: printf("Новый доход: "); if (scanf("%lf", &modified.income) != 1) { printf("Ошибка ввода\n"); while (getchar()!='\n'); return; } if (modified.income < 0) { printf("Ошибка: доход\n"); return; } break;
        default: printf("Неверный выбор\n"); return;
    }

    delete_at_list(list, idx);
    insert_sorted_by_age(list, modified);

    Operation op;
    op.type = OP_MODIFY;
    op.data = modified;
    op.old_data = old;
    op.index = idx;
    if (!push_operation(&op)) fprintf(stderr, "Предупреждение: не удалось сохранить операцию (undo)\n");

    printf("Изменено\n");
}

/* menu print */
static void print_menu(void) {
    printf("\n=== МЕНЮ ===\n");
    printf("1 - Показать всех жителей\n");
    printf("2 - Поиск\n");
    printf("3 - Изменить жителя\n");
    printf("4 - Добавить жителя\n");
    printf("5 - Удалить жителя\n");
    printf("6 - Сохранить в файл\n");
    printf("7 - Отменить последние N/2 модификаций (Undo)\n");
    printf("0 - Выход\n");
    printf("Выберите: ");
}

int main(void) {
    Liver_List list = Liver_create_list(delete_liver, copy_liver, compare_livers, create_invalid_liver());
    free_undo_storage();

    char filename[260];
    printf("Введите имя файла для загрузки данных: ");
    if (scanf("%259s", filename) != 1) { fprintf(stderr, "Ошибка ввода\n"); return 1; }

    /* читаем данные */
    Liver_List tmp = read_from_file(filename);
    /* copy tmp into working list (we can simply assign since it's a struct containing head/tail/size) */
    list = tmp;

    int choice;
    do {
        print_menu();
        if (scanf("%d", &choice) != 1) { printf("Ошибка ввода\n"); while (getchar()!='\n'); continue; }
        switch (choice) {
            case 1:
                display_residents(&list);
                break;
            case 2:
                search_residents(&list);
                break;
            case 3:
                modify_resident(&list);
                break;
            case 4:
                add_resident(&list);
                break;
            case 5:
                remove_resident(&list);
                break;
            case 6: {
                char outname[260];
                printf("Введите имя файла для сохранения: ");
                if (scanf("%259s", outname) != 1) { printf("Ошибка ввода\n"); break; }
                save_to_file(&list, outname);
                break;
            }
            case 7:
                undo_operations(&list);
                break;
            case 0:
                printf("Выход...\n");
                break;
            default:
                printf("Неверный выбор\n");
        }
    } while (choice != 0);

    /* cleanup */
    Liver_delete_list(&list);
    free_undo_storage();

    return 0;
}

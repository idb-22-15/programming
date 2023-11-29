#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../term3-structalgo-lab3/double_list.c"
#include "../term3-structalgo-lab3/linked_list.c"

typedef enum list_type_t { LIST_LINKED = '1', LIST_DOUBLE = '2' } list_type_t;

void menu_ll_print_help() {
  printf(
      "Выберете команду:\n"
      "\t1)создать список\n"
      "\t2)сделать список пустым\n"
      "\t3)проверить на пустоту\n"
      "\t4)установить указатель в начало\n"
      "\t5)проверить, находится ли указатель в конце\n"
      "\t6)сдвинуть указатель на следующий элемент\n"
      "\t7)вывести значение элемента за указателем\n"
      "\t8)удалить элемент за указателем\n"
      "\t9)взять элемент за указателем\n"
      "\t10)изменить значение элемента за указателем\n"
      "\t11)добавить элемент за указателем\n"
      "\t12)распечатать список\n"
      "\t13)удалить список\n"
      "\t14/q)выйти в меню\n"
      "\th)Помощь\n");
}

void menu_ll() {
  char* choice;
  bool is_ended = false;

  linked_list* list;
  linked_list* pointer;

  menu_ll_print_help();
  while (!is_ended) {
    printf("> ");
    scanf("%s", choice);
    if (!strcmp(choice, "1")) {
      list = ll_new_node(0);
    }
    if (!strcmp(choice, "2")) {
      ll_make_empty(&list);
    }
    if (!strcmp(choice, "3"))
      ll_is_empty(list) ? printf("Список пустой\n")
                        : printf("Список не пустой\n");
    if (!strcmp(choice, "4"))
      pointer = list;
    if (!strcmp(choice, "5"))
      ll_is_end(list) ? printf("Указатель в конце списка\n")
                      : printf("Указатель не в конце списка\n");
    if (!strcmp(choice, "6"))
      pointer = pointer->next;
    if (!strcmp(choice, "7"))
      printf("Значение узла за указателем: %d\n",
             ll_get_node_value(pointer->next));
    if (!strcmp(choice, "8"))
      ll_pop_index(&list, ll_get_index(list, pointer));
    if (!strcmp(choice, "9"))
      printf("Значение узла за указателем: %d",
             ll_get_node_value(pointer->next));
    if (!strcmp(choice, "10")) {
      int new_value;
      printf("Введите новое знвчение для замены: ");
      scanf("%d", &new_value);
      ll_set_node_value(pointer->next, new_value);
    }
    if (!strcmp(choice, "11")) {
      int new_value;
      printf("Введите новое знвчение для создания: ");
      scanf("%d", &new_value);
      ll_insert_after(list, ll_get_index(list, pointer), new_value);
    }
    if (!strcmp(choice, "12")) {
      printf("Список: ");
      ll_println(list);
    }
    if (!strcmp(choice, "13"))
      ll_free(&list);
    if (!strcmp(choice, "14") || !strcmp(choice, "q")) {
      is_ended = true;
    }
    if (!strcmp(choice, "h"))
      menu_ll_print_help();
  }
}

void menu_dl_print_help() {
  printf(
      "Выберете команду:\n"
      "\t1)создать список\n"
      "\t2)сделать список пустым\n"
      "\t3)проверить на пустоту\n"
      "\t4)установить указатель в начало\n"
      "\t5)установить указатель в конец\n"
      "\t6)проверить, находится ли указатель в начале\n"
      "\t7)проверить, находится ли указатель в конце\n"
      "\t8)сдвинуть указатель на следующий элемент\n"
      "\t9)сдвинуть указатель на предыдущий элемент\n"
      "\t10)вывести значение элемента до указателя\n"
      "\t11)вывести значение элемента за указателем\n"
      "\t12)удалить элемент до указателя\n"
      "\t13)удалить элемент за указателем\n"
      "\t14)взять элемент до указателя\n"
      "\t15)взять элемент за указателем\n"
      "\t16)изменить значение элемента до указателя\n"
      "\t17)изменить значение элемента за указателем\n"
      "\t18)добавить элемент до указателя\n"
      "\t19)добавить элемент за указателем\n"
      "\t20)распечатать список\n"
      "\t21)удалить список\n"
      "\t22/q)выйти в меню\n"
      "\th)Помощь\n");
}

void menu_dl() {
  char* choice;
  bool is_ended = false;

  double_list* list;
  double_list* pointer;

  menu_dl_print_help();

  while (!is_ended) {
    printf("> ");
    scanf("%s", choice);
    if (!strcmp(choice, "1")) {
      list = dl_new_node(0, NULL);
    }
    if (!strcmp(choice, "2")) {
      dl_make_empty(&list);
    }
    if (!strcmp(choice, "3"))
      dl_is_empty(list) ? printf("Список пустой\n")
                        : printf("Список не пустой\n");
    if (!strcmp(choice, "4"))
      pointer = list;
    if (!strcmp(choice, "5"))
      dl_is_end(list) ? printf("Указатель в конце списка\n")
                      : printf("Указатель не в конце списка\n");
    if (!strcmp(choice, "6"))
      pointer = pointer->next;
    if (!strcmp(choice, "7"))
      printf("Значение узла за указателем: %d\n",
             dl_get_node_value(pointer->next));
    if (!strcmp(choice, "8"))
      dl_pop_index(&list, dl_get_index(list, pointer));
    if (!strcmp(choice, "9"))
      printf("Значение узла за указателем: %d",
             dl_get_node_value(pointer->next));
    if (!strcmp(choice, "10")) {
      int new_value;
      printf("Введите новое знвчение для замены: ");
      scanf("%d", &new_value);
      dl_set_node_value(pointer->next, new_value);
    }
    if (!strcmp(choice, "11")) {
      int new_value;
      printf("Введите новое знвчение для создания: ");
      scanf("%d", &new_value);
      dl_insert_after(list, dl_get_index(list, pointer), new_value);
    }
    if (!strcmp(choice, "12")) {
      printf("Список: ");
      dl_println(list);
    }
    if (!strcmp(choice, "13"))
      dl_free(&list);
    if (!strcmp(choice, "14") || !strcmp(choice, "q")) {
      is_ended = true;
    }
    if (!strcmp(choice, "h"))
      menu_dl_print_help();
  }
};

void menu_choose_list_type() {
  char choice;
  bool is_ended = false;

  while (!is_ended) {
    printf("Выберете вид списка:\n\t1)связный\n\t2)двухсвязный\n\tq)выйти\n");
    printf("> ");
    scanf("%c", &choice);

    switch (choice) {
      case LIST_LINKED:
        menu_ll();
        break;
      case LIST_DOUBLE:
        menu_dl();
        break;
      case 'q':
        is_ended = true;
        break;
      default:
        break;
    }
  };
}

int main() {
  setlocale(LC_ALL, "");
  menu_choose_list_type();
}

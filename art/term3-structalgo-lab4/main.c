#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../term3-structalgo-lab3/double_list.c"
#include "../term3-structalgo-lab3/linked_list.c"

void ll_println_with_pointer(linked_list* head, linked_list* pointer) {
  ll_handle_error(head);
  linked_list* current_node = head;
  while (current_node != NULL) {
    if (current_node == pointer)
      printf("[ %d ] ", current_node->value);
    else
      printf("%d ", current_node->value);
    current_node = current_node->next;
  }
  printf("\n");
}

void dl_println_with_pointer(double_list* head, double_list* pointer) {
  dl_handle_error(head);
  double_list* current_node = head;
  while (current_node != NULL) {
    if (current_node == pointer)
      printf("[ %d ] ", current_node->value);
    else
      printf("%d ", current_node->value);
    current_node = current_node->next;
  }
  printf("\n");
}

void dl_println_reversed_with_pointer(double_list* head, double_list* pointer) {
  dl_handle_error(head);
  double_list* current_node = dl_get_last_node(head);
  while (current_node != NULL) {
    if (current_node == pointer)
      printf("[ %d ] ", current_node->value);
    else
      printf("%d ", current_node->value);
    current_node = current_node->prev;
  }
  printf("\n");
}

void print_start_menu() {
  printf(
      "Выберете команду\n"
      "\t1/new      создать список\n"
      "\t2/q        выйти в меню\n");
}

void menu_ll_print_help() {
  printf(
      "Выберете команду:\n"
      "\t1/new      создать список\n"
      "\t2/empty    сделать список пустым\n"
      "\t3/isempty  проверить на пустоту\n"
      "\t4/tostart  установить указатель в начало\n"
      "\t5/isend    проверить, находится ли указатель в конце\n"
      "\t6/next     сдвинуть указатель на следующий элемент\n"
      "\t7/pnext    вывести значение элемента за указателем\n"
      "\t8/dnext    удалить элемент за указателем\n"
      "\t9/popnext  взять элемент за указателем\n"
      "\t10/cnext   изменить значение элемента за указателем\n"
      "\t11/anext   добавить элемент за указателем\n"
      "\t12/p       распечатать список\n"
      "\t13/dall/q  удалить список и выйти в меню\n"
      "\th          помощь\n");
}

void menu_ll_choose_task(linked_list* list) {
  char choice[256];
  bool is_ended = false;
  linked_list* pointer;

  bool is_value_taken = false;
  int taken_value;

  menu_ll_print_help();
  while (!is_ended) {
    printf("> ");
    scanf("%s", choice);
    if (!strcmp(choice, "1") || !strcmp(choice, "new"))
      list = ll_new_node(0);

    else if (!strcmp(choice, "2") || !strcmp(choice, "empty"))
      ll_make_empty(&list);

    else if (!strcmp(choice, "3") || !strcmp(choice, "isempty"))
      ll_is_empty(list) ? printf("Список пустой\n")
                        : printf("Список не пустой\n");

    else if (!strcmp(choice, "4") || !strcmp(choice, "tostart"))
      pointer = list;

    else if (!strcmp(choice, "5") || !strcmp(choice, "isend"))
      ll_is_end(list) ? printf("Указатель в конце списка\n")
                      : printf("Указатель не в конце списка\n");

    else if (!strcmp(choice, "6") || !strcmp(choice, "next"))
      pointer = pointer->next;

    else if (!strcmp(choice, "7"))
      printf("Значение узла за указателем: %d\n",
             ll_get_node_value(pointer->next));

    else if (!strcmp(choice, "8") || !strcmp(choice, "dnext"))
      ll_pop_index(&list, ll_get_index(list, pointer->next));

    else if (!strcmp(choice, "9") || !strcmp(choice, "popnext")) {
      is_value_taken = true;
      taken_value = ll_pop_index(&list, ll_get_index(list, pointer->next));
    }

    else if (!strcmp(choice, "10") || !strcmp(choice, "cnext")) {
      int new_value;
      printf("Введите новое значение для замены: ");
      scanf("%d", &new_value);
      ll_set_node_value(pointer->next, new_value);
    }

    else if (!strcmp(choice, "11") || !strcmp(choice, "anext")) {
      int new_value;
      printf("Введите новое значение для создания: ");
      scanf("%d", &new_value);
      ll_insert_after(list, ll_get_index(list, pointer), new_value);
    }

    else if (!strcmp(choice, "12") || !strcmp(choice, "p")) {
      printf("Список: ");
      ll_println_with_pointer(list, pointer);
    }

    else if (!strcmp(choice, "13") || !strcmp(choice, "dall") ||
             !strcmp(choice, "q")) {
      if (!ll_is_empty(list))
        ll_free(&list);

      is_ended = true;
      if (is_value_taken)
        printf("Взятое значение: %d\n", taken_value);
    }

    else if (strcmp(choice, "h") == 0)
      menu_ll_print_help();

    else
      printf("Команда не существует\n");
  }
}

void menu_ll() {
  char choice[256];
  bool is_ended = false;

  linked_list* list;
  while (!is_ended) {
    print_start_menu();

    printf("> ");
    scanf("%s", choice);

    if (!strcmp(choice, "1") || !strcmp(choice, "new")) {
      list = ll_new_node(0);
      menu_ll_choose_task(list);
    }

    else if (!strcmp(choice, "2") || !strcmp(choice, "q"))
      is_ended = true;

    else
      printf("Команда не существует\n");
  }
}

void menu_dl_print_help() {
  printf(
      "Выберете команду:\n"
      "\t1/new      создать список\n"
      "\t2/empty    сделать список пустым\n"
      "\t3/isempty  проверить на пустоту\n"
      "\t4/tostart  установить указатель в начало\n"
      "\t5/toend    установить указатель в конец\n"
      "\t6/isstart  проверить, находится ли указатель в начале\n"
      "\t7/isend    проверить, находится ли указатель в конце\n"
      "\t8/prev     сдвинуть указатель на следующий элемент\n"
      "\t9/next     сдвинуть указатель на предыдущий элемент\n"
      "\t10/pprev   вывести значение элемента до указателя\n"
      "\t11/pnext   вывести значение элемента за указателем\n"
      "\t12/dprev   удалить элемент до указателя\n"
      "\t13/dnext   удалить элемент за указателем\n"
      "\t14/popprev взять элемент до указателя\n"
      "\t15/popnext взять элемент за указателем\n"
      "\t16/cprev   изменить значение элемента до указателя\n"
      "\t17/cnext   изменить значение элемента за указателем\n"
      "\t18/aprev   добавить элемент до указателя\n"
      "\t19/anext   добавить элемент за указателем\n"
      "\t20/p       распечатать список\n"
      "\t21/dall/q  удалить список и выйти в меню\n"
      "\th          помощь\n");
}

void menu_dl_choose_task(double_list* list) {
  char choice[256];
  bool is_ended = false;

  double_list* pointer;

  bool is_value_taken = false;
  int taken_value;

  menu_dl_print_help();

  while (!is_ended) {
    printf("> ");
    scanf("%s", choice);
    if (!strcmp(choice, "1") || !strcmp(choice, "new"))
      list = dl_new_node(0, NULL);

    else if (!strcmp(choice, "2") || !strcmp(choice, "empty"))
      dl_make_empty(&list);

    else if (!strcmp(choice, "3") || !strcmp(choice, "isempty"))
      dl_is_empty(list) ? printf("Список пустой\n")
                        : printf("Список не пустой\n");

    else if (!strcmp(choice, "4") || !strcmp(choice, "tostart"))
      pointer = list;

    else if (!strcmp(choice, "5") || !strcmp(choice, "toend"))
      pointer = dl_get_last_node(list);

    else if (!strcmp(choice, "6") || !strcmp(choice, "isstart"))
      dl_is_start(pointer) ? printf("Указатель в начале списка\n")
                           : printf("Указатель не в начале списка\n");

    else if (!strcmp(choice, "7") || !strcmp(choice, "isend"))
      dl_is_end(pointer) ? printf("Указатель в конце списка\n")
                         : printf("Указатель не в конце списка\n");

    else if (!strcmp(choice, "8") || !strcmp(choice, "prev"))
      pointer = pointer->prev;

    else if (!strcmp(choice, "9") || !strcmp(choice, "next"))
      pointer = pointer->next;

    else if (!strcmp(choice, "10") || !strcmp(choice, "pprev"))
      printf("Значение элемента до указателя: %d\n",
             dl_get_node_value(pointer->prev));

    else if (!strcmp(choice, "11") || !strcmp(choice, "pnext"))
      printf("Значение элемента за указателем: %d\n",
             dl_get_node_value(pointer->next));

    else if (!strcmp(choice, "12") || !strcmp(choice, "dprev"))
      dl_pop_index(&list, dl_get_index(list, pointer->prev));

    else if (!strcmp(choice, "13") || !strcmp(choice, "dnext"))
      dl_pop_index(&list, dl_get_index(list, pointer->next));

    else if (!strcmp(choice, "14") || !strcmp(choice, "popprev"))
      taken_value = dl_pop_index(&list, dl_get_index(list, pointer->prev));

    else if (!strcmp(choice, "15") || !strcmp(choice, "popnext"))
      taken_value = dl_pop_index(&list, dl_get_index(list, pointer->next));

    else if (!strcmp(choice, "16") || !strcmp(choice, "cprev")) {
      int new_value;
      printf("Введите новое значение для замены: ");
      scanf("%d", &new_value);
      dl_set_node_value(pointer->prev, new_value);
    }

    else if (!strcmp(choice, "17") || !strcmp(choice, "cnext")) {
      int new_value;
      printf("Введите новое значение для замены: ");
      scanf("%d", &new_value);
      dl_set_node_value(pointer->next, new_value);
    }

    else if (!strcmp(choice, "18") || !strcmp(choice, "aprev")) {
      int new_value;
      printf("Введите новое значение для создания: ");
      scanf("%d", &new_value);
      dl_insert_before(&list, dl_get_index(list, pointer), new_value);
    }

    else if (!strcmp(choice, "19") || !strcmp(choice, "anext")) {
      int new_value;
      printf("Введите новое значение для создания: ");
      scanf("%d", &new_value);
      dl_insert_after(list, dl_get_index(list, pointer), new_value);
    }

    else if (!strcmp(choice, "20") || !strcmp(choice, "p")) {
      printf("Список:   ");
      dl_println_with_pointer(list, pointer);
      printf("Обратный: ");
      dl_println_reversed_with_pointer(list, pointer);
    }

    else if (!strcmp(choice, "21") || !strcmp(choice, "dall") ||
             !strcmp(choice, "q")) {
      if (!dl_is_empty(list))
        dl_free(&list);

      is_ended = true;
      if (is_value_taken)
        printf("Взятое значение: %d\n", taken_value);
    }

    else if (!strcmp(choice, "h"))
      menu_dl_print_help();

    else
      printf("Команда не сущетвует\n");
  }
}

void menu_dl() {
  char choice[256];
  bool is_ended = false;

  double_list* list;
  while (!is_ended) {
    print_start_menu();

    printf("> ");
    scanf("%s", choice);

    if (!strcmp(choice, "1") || !strcmp(choice, "new")) {
      list = dl_new_node(0, NULL);
      menu_dl_choose_task(list);
    }

    else if (!strcmp(choice, "2") || !strcmp(choice, "q"))
      is_ended = true;

    else
      printf("Команда не существует\n");
  }
}

void menu_choose_list_type() {
  char choice[256];
  bool is_ended = false;

  while (!is_ended) {
    printf(
        "Выберете вид списка:\n"
        "\t1          связный\n"
        "\t2          двухсвязный\n"
        "\tq          выйти\n");
    printf("> ");
    scanf("%s", choice);

    if (!strcmp(choice, "1"))
      menu_ll();

    else if (!strcmp(choice, "2"))
      menu_dl();

    else if (!strcmp(choice, "q"))
      is_ended = true;

    else
      printf("Команда не сущетвует\n");
  };
}

int main() {
  setlocale(LC_ALL, "");
  menu_choose_list_type();
}

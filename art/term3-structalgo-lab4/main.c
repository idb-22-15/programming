#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../term3-structalgo-lab3/double_list.c"
#include "../term3-structalgo-lab3/linked_list.c"

#define BUFFER_SIZE 256

void ll_println_with_pointer(linked_list* head, linked_list* pointer) {
  ll_handle_error(head);
  linked_list* current_node = head;
  while (current_node != NULL) {
    if (current_node == pointer)
      printf("[ %c ] ", current_node->value);
    else
      printf("%c ", current_node->value);
    current_node = current_node->next;
  }
  printf("\n");
}

void dl_println_with_pointer(double_list* head, double_list* pointer) {
  dl_handle_error(head);
  double_list* current_node = head;
  while (current_node != NULL) {
    if (current_node == pointer)
      printf("[ %c ] ", current_node->value);
    else
      printf("%c ", current_node->value);
    current_node = current_node->next;
  }
  printf("\n");
}

void dl_println_reversed_with_pointer(double_list* head, double_list* pointer) {
  dl_handle_error(head);
  double_list* current_node = dl_get_last_node(head);
  while (current_node != NULL) {
    if (current_node == pointer)
      printf("[ %c ] ", current_node->value);
    else
      printf("%c ", current_node->value);
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
      "\t1/empty    сделать список пустым\n"
      "\t2/isempty  проверить на пустоту\n"
      "\t3/tostart  установить указатель в начало\n"
      "\t4/isend    проверить, находится ли указатель в конце\n"
      "\t5/next     сдвинуть указатель на следующий элемент\n"
      "\t6/pnext    вывести значение элемента за указателем\n"
      "\t7/dnext    удалить элемент за указателем\n"
      "\t8/popnext  взять элемент за указателем\n"
      "\t9/cnext    изменить значение элемента за указателем\n"
      "\t10/anext   добавить элемент за указателем\n"
      "\t11/p       распечатать список\n"
      "\t12/dall/q  удалить список и выйти в меню\n"
      "\th          помощь\n");
}

void println_command_does_not_exist() {
  printf("Команда не существует\n");
}

void println_list_is_empty() {
  printf("Список пустой\n");
}

void println_prev_node_does_not_exist() {
  printf("Предыдущий элемент не существует\n");
}

void println_next_node_does_not_exist() {
  printf("Следующий элемент не существует\n");
}

void menu_ll_choose_task(linked_list* list) {
  char choice[BUFFER_SIZE];
  bool is_ended = false;
  linked_list* pointer = list;

  bool is_value_taken = false;
  int taken_value;

  menu_ll_print_help();
  while (!is_ended) {
    printf("> ");
    scanf("%s", choice);

    if (!strcmp(choice, "1") || !strcmp(choice, "empty")) {
      ll_make_empty(&list);
      printf("Список опустошён\n");
    }

    else if (!strcmp(choice, "2") || !strcmp(choice, "isempty"))
      ll_is_empty(list) ? println_list_is_empty()
                        : printf("Список не пустой\n");

    else if (!strcmp(choice, "3") || !strcmp(choice, "tostart")) {
      if (ll_is_empty(list))
        println_list_is_empty();
      else {
        pointer = list;
        ll_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "4") || !strcmp(choice, "isend"))
      if (ll_is_empty(list))
        println_list_is_empty();
      else
        ll_is_end(list) ? printf("Указатель в конце списка\n")
                        : printf("Указатель не в конце списка\n");

    else if (!strcmp(choice, "5") || !strcmp(choice, "next")) {
      if (ll_is_empty(list))
        println_list_is_empty();
      else if (ll_is_end(pointer))
        println_next_node_does_not_exist();
      else {
        pointer = pointer->next;
        ll_println_with_pointer(list, pointer);
      }

    }

    else if (!strcmp(choice, "6") || !strcmp(choice, "pnext")) {
      if (ll_is_empty(list))
        println_list_is_empty();
      else if (ll_is_end(pointer))
        println_next_node_does_not_exist();
      else
        printf("Значение узла за указателем: %d\n",
               ll_get_node_value(pointer->next));
    }

    else if (!strcmp(choice, "7") || !strcmp(choice, "dnext")) {
      if (ll_is_empty(list))
        println_list_is_empty();
      else if (ll_is_end(pointer))
        println_next_node_does_not_exist();
      else {
        ll_pop_index(&list, ll_get_index(list, pointer->next));
        ll_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "8") || !strcmp(choice, "popnext")) {
      if (ll_is_empty(list))
        println_list_is_empty();
      else if (ll_is_end(pointer))
        println_next_node_does_not_exist();
      else {
        is_value_taken = true;
        taken_value = ll_pop_index(&list, ll_get_index(list, pointer->next));
        ll_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "9") || !strcmp(choice, "cnext")) {
      if (ll_is_empty(list))
        println_list_is_empty();
      else if (ll_is_end(pointer))
        println_next_node_does_not_exist();
      else {
        char new_value[BUFFER_SIZE];
        printf("Введите новое значение для замены: ");
        scanf("%s", &new_value);
        ll_set_node_value(pointer->next, new_value[0]);
        ll_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "10") || !strcmp(choice, "anext")) {
      if (ll_is_empty(list))
        println_list_is_empty();
      else {
        char new_value[BUFFER_SIZE];
        printf("Введите новое значение для создания: ");
        scanf("%s", new_value);
        ll_insert_after(list, ll_get_index(list, pointer), new_value[0]);
        ll_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "11") || !strcmp(choice, "p")) {
      if (ll_is_empty(list))
        println_list_is_empty();
      else {
        printf("Список: ");
        ll_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "12") || !strcmp(choice, "dall") ||
             !strcmp(choice, "q")) {
      if (!ll_is_empty(list))
        ll_free(&list);

      printf("Список удалён\n");

      is_ended = true;
      if (is_value_taken)
        printf("Взятое значение: %d\n", taken_value);
    }

    else if (strcmp(choice, "h") == 0)
      menu_ll_print_help();

    else
      println_command_does_not_exist();
  }
}

void menu_ll() {
  char choice[BUFFER_SIZE];
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
      println_command_does_not_exist();
  }
}

void menu_dl_print_help() {
  printf(
      "Выберете команду:\n"
      "\t1/empty    сделать список пустым\n"
      "\t2/isempty  проверить на пустоту\n"
      "\t3/tostart  установить указатель в начало\n"
      "\t4/toend    установить указатель в конец\n"
      "\t5/isstart  проверить, находится ли указатель в начале\n"
      "\t6/isend    проверить, находится ли указатель в конце\n"
      "\t7/prev     сдвинуть указатель на следующий элемент\n"
      "\t8/next     сдвинуть указатель на предыдущий элемент\n"
      "\t9/pprev   вывести значение элемента до указателя\n"
      "\t10/pnext   вывести значение элемента за указателем\n"
      "\t11/dprev   удалить элемент до указателя\n"
      "\t12/dnext   удалить элемент за указателем\n"
      "\t13/popprev взять элемент до указателя\n"
      "\t14/popnext взять элемент за указателем\n"
      "\t15/cprev   изменить значение элемента до указателя\n"
      "\t16/cnext   изменить значение элемента за указателем\n"
      "\t17/aprev   добавить элемент до указателя\n"
      "\t18/anext   добавить элемент за указателем\n"
      "\t10/p       распечатать список\n"
      "\t20/dall/q  удалить список и выйти в меню\n"
      "\th          помощь\n");
}

void menu_dl_choose_task(double_list* list) {
  char choice[BUFFER_SIZE];
  bool is_ended = false;

  double_list* pointer = list;

  bool is_value_taken = false;
  int taken_value;

  menu_dl_print_help();

  while (!is_ended) {
    printf("> ");
    scanf("%s", choice);

    if (!strcmp(choice, "1") || !strcmp(choice, "empty")) {
      dl_make_empty(&list);
      printf("Список удалён\n");
    }

    else if (!strcmp(choice, "2") || !strcmp(choice, "isempty"))
      dl_is_empty(list) ? println_list_is_empty()
                        : printf("Список не пустой\n");

    else if (!strcmp(choice, "3") || !strcmp(choice, "tostart")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else {
        pointer = list;
        dl_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "4") || !strcmp(choice, "toend")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else {
        pointer = dl_get_last_node(list);
        dl_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "5") || !strcmp(choice, "isstart"))
      if (dl_is_empty(list))
        println_list_is_empty();
      else
        dl_is_start(pointer) ? printf("Указатель в начале списка\n")
                             : printf("Указатель не в начале списка\n");

    else if (!strcmp(choice, "6") || !strcmp(choice, "isend"))
      if (dl_is_empty(list))
        println_list_is_empty();
      else
        dl_is_end(pointer) ? printf("Указатель в конце списка\n")
                           : printf("Указатель не в конце списка\n");

    else if (!strcmp(choice, "7") || !strcmp(choice, "prev")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else if (dl_is_start(pointer))
        println_prev_node_does_not_exist();
      else {
        pointer = pointer->prev;
        dl_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "8") || !strcmp(choice, "next")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else if (dl_is_end(pointer))
        println_next_node_does_not_exist();
      else {
        pointer = pointer->next;
        dl_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "9") || !strcmp(choice, "pprev"))
      if (dl_is_empty(list))
        println_list_is_empty();
      else if (dl_is_start(pointer))
        println_prev_node_does_not_exist();
      else
        printf("Значение элемента до указателя: %d\n",
               dl_get_node_value(pointer->prev));

    else if (!strcmp(choice, "10") || !strcmp(choice, "pnext"))
      if (dl_is_empty(list))
        println_list_is_empty();
      else if (dl_is_end(pointer))
        println_next_node_does_not_exist();
      else
        printf("Значение элемента за указателем: %d\n",
               dl_get_node_value(pointer->next));

    else if (!strcmp(choice, "11") || !strcmp(choice, "dprev")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else if (dl_is_start(pointer))
        println_prev_node_does_not_exist();
      else {
        dl_pop_index(&list, dl_get_index(list, pointer->prev));
        dl_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "12") || !strcmp(choice, "dnext")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else if (dl_is_end(pointer))
        println_next_node_does_not_exist();
      else {
        dl_pop_index(&list, dl_get_index(list, pointer->next));
        dl_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "13") || !strcmp(choice, "popprev")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else if (dl_is_start(pointer))
        println_prev_node_does_not_exist();
      else {
        taken_value = dl_pop_index(&list, dl_get_index(list, pointer->prev));
        dl_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "14") || !strcmp(choice, "popnext")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else if (dl_is_end(pointer))
        println_next_node_does_not_exist();
      else {
        taken_value = dl_pop_index(&list, dl_get_index(list, pointer->next));
        dl_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "15") || !strcmp(choice, "cprev")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else if (dl_is_start(pointer))
        println_prev_node_does_not_exist();
      else {
        char new_value[BUFFER_SIZE];
        printf("Введите новое значение для замены: ");
        scanf("%s", new_value);
        dl_set_node_value(pointer->prev, new_value[0]);
        dl_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "16") || !strcmp(choice, "cnext")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else if (dl_is_end(pointer))
        println_next_node_does_not_exist();
      else {
        char new_value[BUFFER_SIZE];
        printf("Введите новое значение для замены: ");
        scanf("%s", new_value);
        dl_set_node_value(pointer->next, new_value[0]);
        dl_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "17") || !strcmp(choice, "aprev")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else {
        char new_value[BUFFER_SIZE];
        printf("Введите новое значение для создания: ");
        scanf("%s", new_value);
        dl_insert_before(&list, dl_get_index(list, pointer), new_value[0]);
        dl_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "18") || !strcmp(choice, "anext")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else {
        char new_value[BUFFER_SIZE];
        printf("Введите новое значение для создания: ");
        scanf("%s", new_value);
        dl_insert_after(list, dl_get_index(list, pointer), new_value[0]);
        dl_println_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "19") || !strcmp(choice, "p")) {
      if (dl_is_empty(list))
        println_list_is_empty();
      else {
        printf("Список:   ");
        dl_println_with_pointer(list, pointer);
        printf("Обратный: ");
        dl_println_reversed_with_pointer(list, pointer);
      }
    }

    else if (!strcmp(choice, "20") || !strcmp(choice, "dall") ||
             !strcmp(choice, "q")) {
      if (!dl_is_empty(list))
        dl_free(&list);

      printf("Список удалён\n");

      is_ended = true;
      if (is_value_taken)
        printf("Взятое значение: %d\n", taken_value);
    }

    else if (!strcmp(choice, "h"))
      menu_dl_print_help();

    else
      println_command_does_not_exist();
  }
}

void menu_dl() {
  char choice[BUFFER_SIZE];
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
      println_command_does_not_exist();
  }
}

void menu_choose_list_type() {
  char choice[BUFFER_SIZE];
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
      println_command_does_not_exist();
  };
}

int main() {
  setlocale(LC_ALL, "");
  menu_choose_list_type();
}

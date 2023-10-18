#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

void menu();

void menu_input();
void input_from_db();
void input_from_console();

void menu_output();
void output_in_db();
void output_in_console();

void menu_add();
void add_one();

void menu_find();
void find_many_by_string(char*, int);
void find_many_by_int(int);

void menu_delete();

void menu_sort();
void sort_selection_by_name();
void sort_selection_by_surname();
void sort_selection_by_email();
void sort_selection_by_balance();

void print_table_x();
void print_table_top();
void print_table_head();
void print_table_head_full();
void print_table_body(struct Consumer, int);
void print_table_underline();
void print_table_item_underline();
void print_table_bottom();

struct Consumer {
  char name[100];
  char surname[100];
  char email[100];
  int balance;
};

struct Consumer consumers[100];
int count = 0;

const char* UNEXPECTED_COMMAND = "Unexpected command\n";

HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);

void set_color(unsigned int color) {
  fflush(stdout);
  SetConsoleTextAttribute(h_console, color);
}

void reset_color() {
  fflush(stdout);
  SetConsoleTextAttribute(h_console, 15);
}

void set_color_menu() {
  fflush(stdout);
  SetConsoleTextAttribute(h_console, 14);
}

void set_color_error() {
  fflush(stdout);
  SetConsoleTextAttribute(h_console, 4);
}

void set_color_success() {
  fflush(stdout);
  SetConsoleTextAttribute(h_console, 10);
}

void print_success(const char* message) {
  set_color_success();
  printf(message);
  reset_color();
}

void print_error(const char* message) {
  set_color_error();
  printf(message);
  reset_color();
}

int main() {
  reset_color();
  __try {
    menu();
  } __except (EXCEPTION_EXECUTE_HANDLER) {
    print_error("\nSomething went wrong :(\n");
  }
}

void menu() {
  while (true) {
    fflush(stdout);
    set_color_menu();
    printf("Please, enter command:\n");
    printf(
        "\t1: input db\t\t4: find counsumer(s)\t\t7: exit\n\t2: output "
        "db\t\t5: delete consumer(s)\n\t3: add counsumer\t6: sort db\n> ");
    // printf("\t1: input db\n\t2: output db\n\t3: add counsumer\n\t4: find
    // counsumer(s)\n\t5: delete consumer(s)\n\t6: sort db\n\t7: exit\n> ");
    reset_color();

    char command_string[100] = "";
    int command = 0;

    scanf("%s", command_string);
    command = atoi(command_string);
    switch (command) {
      case 1:
        menu_input();
        break;
      case 2:
        menu_output();
        break;
      case 3:
        menu_add();
        break;
      case 4:
        menu_find();
        break;
      case 5:
        menu_delete();
        break;
      case 6:
        menu_sort();
        break;
      case 7:
        exit(0);
        break;
      default:
        break;
    }
  }
}

void menu_input() {
  set_color_menu();
  printf("Enter data from:\n");
  printf("\t1: db\t\t\t2: console\n> ");
  reset_color();

  char command_string[100] = "";
  int command;

  scanf("%s", command_string);
  command = atoi(command_string);

  switch (command) {
    case 1:
      input_from_db();
      output_in_console();
      break;
    case 2:
      input_from_console();
      output_in_console();
      break;
    default:
      menu_input();
  }
}

void input_from_db() {
  printf("Trying to read from db\n");

  FILE* file = fopen("db.txt", "r");

  if (file == 0) {
    printf("No db file");
    return;
  }

  __try {
    count = 0;
    int i = 0;
    while (fscanf(file, "%s%s%s%d", consumers[i].name, consumers[i].surname,
                  consumers[i].email, &consumers[i].balance) != EOF) {
      i++;
      count++;
    }
  } __except (EXCEPTION_EXECUTE_HANDLER) {
    print_error("Failed to load data from db\n");
  }

  fclose(file);
}

void input_from_console() {
  set_color_menu();
  printf("Please, enter items count: ");
  reset_color();

  char itemsCountString[100] = "";
  int itemsCount;

  scanf("%s", &itemsCountString);

  if (!isdigit(itemsCountString[0])) {
    print_error(UNEXPECTED_COMMAND);
    return;
  }

  itemsCount = atoi(itemsCountString);

  try {
    set_color_menu();
    printf("Please, enter data to DB:\n");
    reset_color();

    count = 0;
    for (int i = 0; i < itemsCount; i++) {
      add_one();
    }
    printf("\n");
  } catch (const char* errorMessage) {
    print_error("Failed to add new consumer\n");
  }
}

void menu_output() {
  set_color_menu();
  printf("Write data to:\n");
  printf("\t1: db\t\t\t2: console\n> ");
  reset_color();

  char command_string[100] = "";
  int command;

  scanf("%s", command_string);
  command = atoi(command_string);

  switch (command) {
    case 1:
      output_in_db();
      break;
    case 2:
      output_in_console();
      break;
    default:
      menu_output();
      break;
  }
}

void output_in_db() {
  FILE* file = fopen("db.txt", "w");

  if (file == 0) {
    printf("No db file\n");
    return;
  }

  __try {
    for (int i = 0; i < count; i++) {
      const struct Consumer consumer = consumers[i];
      fprintf(file, "%s %s %s %d\n", consumer.name, consumer.surname,
              consumer.email, consumer.balance);
    }
  } __except (EXCEPTION_EXECUTE_HANDLER) {
    print_error("Failed to write in db\n");
  }

  fclose(file);
}

void output_in_console() {
  print_table_head_full();

  for (int i = 0; i < count; i++) {
    print_table_body(consumers[i], i);
    if (i + 1 != count)
      print_table_underline();
  }
  print_table_bottom();
}

void menu_add() {
  try {
    add_one();
  } catch (const char* errorMessage) {
    print_error(errorMessage);
  }
}

void add_one() {
  set_color_menu();
  printf("Please, enter new consumer:\n");
  printf("Name    Surname Email   Balance\n");
  reset_color();
  char balanceString[100] = "";

  scanf("%s%s%s%s", consumers[count].name, consumers[count].surname,
        consumers[count].email, &balanceString);
  consumers[count].balance = atoi(balanceString);

  if (isdigit(balanceString[0])) {
    consumers[count].balance = atoi(balanceString);
  } else if (atoi(balanceString) == 0)
    throw "Invalid data\n";

  print_success("Consumer was added\n");
  count++;
}

void menu_find() {
  set_color_menu();
  printf("Find by\n");
  printf("\t1: name\t\t\t3: email\n\t2: surname\t\t4: balance\n> ");
  reset_color();

  char find_by_string[100] = "";
  int findBy;

  scanf("%s", find_by_string);
  findBy = atoi(find_by_string);

  char string[100];
  char number_string[100];
  int number;

  switch (findBy) {
    case 1:
      set_color_menu();
      printf("Please, enter name: ");
      reset_color();
      scanf("%s", string);

      find_many_by_string(string, 1);
      break;
    case 2:
      set_color_menu();
      printf("Please, enter surname: ");
      reset_color();
      scanf("%s", string);

      find_many_by_string(string, 2);
      break;
    case 3:
      set_color_menu();
      printf("Please, enter email: ");
      reset_color();
      scanf("%s", string);

      find_many_by_string(string, 3);
      break;
    case 4:
      set_color_menu();
      printf("Please, enter balance: ");
      reset_color();
      scanf("%s", number_string);

      if (!isdigit(number_string[0])) {
        print_error(UNEXPECTED_COMMAND);
        break;
      }
      number = atoi(number_string);
      find_many_by_int(number);
      break;
    default:
      menu_find();
      break;
  }
}

void find_many_by_string(char* string, int findBy) {
  print_table_head_full();
  int countFounded = 0;
  for (int i = 0; i < count; i++) {
    char* param = NULL;
    switch (findBy) {
      case 1:
        param = consumers[i].name;
        break;
      case 2:
        param = consumers[i].surname;
        break;
      case 3:
        param = consumers[i].email;
        break;
    }
    if (strcmp(param, string) == 0) {
      if (countFounded != 0)
        print_table_underline();
      print_table_body(consumers[i], i);
      countFounded++;
    }
  }
  print_table_bottom();
  set_color_success();
  printf("%d consumer(s) was(were) found\n", countFounded);
  reset_color();
}

void find_many_by_int(int number) {
  print_table_head_full();
  int countFounded = 0;
  for (int i = 0; i < count; i++) {
    if (consumers[i].balance == number) {
      if (countFounded != 0)
        print_table_underline();
      print_table_body(consumers[i], i);
      countFounded++;
    }
  }
  print_table_bottom();
  set_color_success();
  printf("%d consumer(s) was(were) found\n", countFounded);
  reset_color();
}

void menu_delete() {
  void delete_one_by_order(int);
  void delete_many_by_string(const char*, int);
  void deleteManyByInt(int);

  set_color_menu();
  printf("Delete by:\n");
  printf(
      "\t1: order\t\t3: surname\t\t\t5: balance\n\t2: name\t\t\t4: email\n> ");
  reset_color();

  char deleteByString[100] = "";
  int deleteBy;

  scanf("%s", &deleteByString);
  deleteBy = atoi(deleteByString);

  char string[100];
  char number_string[100];
  int number;
  switch (deleteBy) {
    case 1:
      set_color_menu();
      printf("Please, enter consumer's order to delete: ");
      reset_color();
      int order;
      scanf("%d", &order);

      delete_one_by_order(order);
      break;
    case 2:
      set_color_menu();
      printf("Please, enter consumers' name to delete: ");
      reset_color();
      scanf("%s", &string);

      delete_many_by_string(string, 2);
      break;
    case 3:
      set_color_menu();
      printf("Please, enter consumers' surname to delete: ");
      reset_color();
      scanf("%s", &string);

      delete_many_by_string(string, 3);
      break;
    case 4:
      set_color_menu();
      printf("Please, enter consumers' email to delete: ");
      reset_color();
      scanf("%s", &string);

      delete_many_by_string(string, 4);
      break;
    case 5:
      set_color_menu();
      printf("Please, enter consumers' balance to delete: ");
      reset_color();
      scanf("%s", number_string);
      if (!isdigit(number_string[0])) {
        print_error(UNEXPECTED_COMMAND);
        break;
      }
      number = atoi(number_string);
      deleteManyByInt(number);
      break;
    default:
      menu_delete();
      break;
  }
}

void delete_one_by_order(int order) {
  if (order > count) {
    printf("No consumer with such order\n");
    return;
  }

  const int index = order - 1;
  for (int i = index; i < count; i++) {
    consumers[i] = consumers[i + 1];
  }
  count--;
  print_success("1 consumer was deleted\n");
}

void delete_many_by_string(const char* string, int deleteBy) {
  int count_deleted = 0;
  for (int i = 0; i < count; i++) {
    char* param = NULL;
    switch (deleteBy) {
      case 2:
        param = consumers[i].name;
        break;
      case 3:
        param = consumers[i].surname;
        break;
      case 4:
        param = consumers[i].email;
        break;
    }

    if (strcmp(param, string) == 0) {
      for (int j = i; j < count; j++) {
        consumers[j] = consumers[j + 1];
        char* extraParam = NULL;
        switch (deleteBy) {
          case 2:
            extraParam = consumers[j].name;
            break;
          case 3:
            extraParam = consumers[j].surname;
            break;
          case 4:
            extraParam = consumers[j].email;
            break;
        }
        if (strcmp(extraParam, string) == 0)
          i--;
      }
      count_deleted++;
    }
  }
  count -= count_deleted;
  set_color_success();
  printf("%d consumer(s) was(were) deleted\n", count_deleted);
  reset_color();
}

void deleteManyByInt(int number) {
  int count_deleted = 0;
  for (int i = 0; i < count; i++) {
    if (consumers[i].balance == number) {
      for (int j = i; j < count; j++) {
        consumers[j] = consumers[j + 1];
        if (consumers[j].balance == number)
          i--;
      }
      count_deleted++;
    }
  }
  count -= count_deleted;
  set_color_success();
  printf("%d consumer(s) was deleted\n", count_deleted);
  reset_color();
}

void menu_sort() {
  set_color_menu();
  printf("Sort by:\n");
  printf("\t1: name\t\t\t3: email\n\t2: surname\t\t4: balance\n> ");
  reset_color();

  char sort_by_string[100] = "";
  int sortBy;

  scanf("%s", &sort_by_string);
  sortBy = atoi(sort_by_string);

  switch (sortBy) {
    case 1:
      sort_selection_by_name();
      output_in_console();
      break;
    case 2:
      sort_selection_by_surname();
      output_in_console();
      break;
    case 3:
      sort_selection_by_email();
      output_in_console();
      break;
    case 4:
      sort_selection_by_balance();
      output_in_console();
      break;
    default:
      menu_sort();
      break;
  }
}

void sort_selection_by_name() {
  if (count == 0)
    return;

  for (int i = 0; i < count; i++) {
    for (int j = i + 1; j < count; j++) {
      if (strcmp(consumers[i].name, consumers[j].name) == 1) {
        struct Consumer temp = consumers[i];
        consumers[i] = consumers[j];
        consumers[j] = temp;
      }
    }
  }
}

void sort_selection_by_surname() {
  if (count == 0)
    return;

  for (int i = 0; i < count; i++) {
    for (int j = i + 1; j < count; j++) {
      if (strcmp(consumers[i].surname, consumers[j].surname) == 1) {
        struct Consumer temp = consumers[i];
        consumers[i] = consumers[j];
        consumers[j] = temp;
      }
    }
  }
}

void sort_selection_by_email() {
  if (count == 0)
    return;

  for (int i = 0; i < count; i++) {
    for (int j = i + 1; j < count; j++) {
      if (strcmp(consumers[i].email, consumers[j].email) == 1) {
        struct Consumer temp = consumers[i];
        consumers[i] = consumers[j];
        consumers[j] = temp;
      }
    }
  }
}

void sort_selection_by_balance() {
  if (count == 0)
    return;

  for (int i = 0; i < count; i++) {
    for (int j = i + 1; j < count; j++) {
      if (consumers[i].balance > consumers[j].balance) {
        struct Consumer temp = consumers[i];
        consumers[i] = consumers[j];
        consumers[j] = temp;
      }
    }
  }
}

void print_table_item_underline() {
  const int tw = 196;
  for (int c = 0; c < 13; c++)
    printf("%c", tw);
}

void print_table_x(int tx) {
  const int columns = 5;

  for (int i = 0; i < columns - 1; i++) {
    print_table_item_underline();
    printf("%c", tx);
  }
  print_table_item_underline();
}

void print_table_top() {
  const int ttx = 194;
  const int tatl = 218;
  const int tatr = 191;

  printf("%c", tatl);
  print_table_x(ttx);
  printf("%c", tatr);
  printf("\n");
}

void print_table_head() {
  const int th = 179;
  printf("%c%13s%c%13s%c%13s%c%13s%c%13s%c\n", th, "No", th, "Name", th,
         "Surname", th, "Email", th, "Balance", th);
}

void print_table_head_full() {
  print_table_top();
  print_table_head();
  print_table_underline();
}

void print_table_body(struct Consumer consumer, int index) {
  const int order = index + 1;
  const int th = 179;
  printf("%c%13d%c%13s%c%13s%c%13s%c%13d%c\n", th, order, th, consumer.name, th,
         consumer.surname, th, consumer.email, th, consumer.balance, th);
}

void print_table_underline() {
  const int txl = 195;
  const int txr = 180;
  const int tx = 197;

  printf("%c", txl);
  print_table_x(tx);
  printf("%c", txr);
  printf("\n");
}

void print_table_bottom() {
  const int tbx = 193;
  const int tabl = 192;
  const int tabr = 217;

  printf("%c", tabl);
  print_table_x(tbx);
  printf("%c", tabr);
  printf("\n");
}

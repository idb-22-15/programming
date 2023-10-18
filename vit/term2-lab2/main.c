// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается
// и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

void menu();
void input();
void output();
void add();
void search();
void sort();
void remove();
void load();
void removeByNum();
void save();
void printX(int);
struct Cat {
  char breed[13];  // Порода
  int age;         // Возраст
  char color[10];  // Цвет
  char phone[12];  // Телефон продавца
};
struct Cat db[51];  // База данных
int count = 0;  // Сохраняет последний добавленный элемент

int main() {
  SetConsoleCP(1251);
  menu();
  return 0;
}
void help() {
  printX(4);
  printf("| 1) %s\t", "Ввод в ДБ");
  printf("2) %s  |\n", "Вывод");  //
  printf("| 3) %s\t", "Добавить");
  printf("4) %s  |\n", "Поиск");  //
  printf("| 5) %s\t", "Удалить");
  printf("6) %s   |\n", "Сорт");  //
  printf("| 7) %s\t", "Экспорт");
  printf("8) %6s |\n", "Импорт");
  printf("| 9) %s\t", "Помощь");  //
  printf("0) %5s  |\n", "Выход");
  printX(5);
}
void menu() {
  setlocale(LC_ALL, ".1251");
  char num[2] = {0};  // Выбор опции
  printf("Добро пожаловать в СУБД ветеринарной клиники \"Ушастое Счастье\"\n");
  while (num[0] != '0') {
    help();
    scanf("%1s", &num);
    while (getchar() != '\n')
      ;
    switch (num[0]) {
      case '1':
        input();
        break;
      case '2':
        output();
        break;
      case '3':
        add();
        break;
      case '4':
        search();
        break;
      case '5':
        remove();
        break;
      case '6':
        sort();
        break;
      case '7':
        save();
        break;
      case '8':
        load();
        break;
      case '9':
        help();
        break;
      case '0':
        printf("Выход из программы...");
        break;
      default:
        printf("Повторите ввод в меню\n");
    }
  }
}
void inputScript(int start, int amount) {
  for (int i = start; i < amount + start; i++) {
    printf("Порода: ");
    scanf("%13s", &db[i].breed);
    printf("Возраст: ");
    scanf("%3d", &db[i].age);
    if (db[i].age == 0) {
      printf("Неверный ввод записи. Попробуйте снова\n");
      amount--;
      continue;
    }
    printf("Цвет: ");
    scanf("%9s", &db[i].color);
    printf("Телефон: ");
    scanf("%12s", &db[i].phone);
  }
  count = start + amount;
}
void input() {  // Ввод
  char a[3] = {0};
  int b;
  printf("Сколько вы хотите ввести элементов: ");
  scanf("%2s", &a);
  b = atoi(a);
  if (b == 0 || b > 50) {
    printf("Выходим в меню\n");
    while (getchar() != '\n')
      ;
  }
  inputScript(0, b);
}
void output() {
  if (count != 0) {
    printX(1);
    printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
    for (int i = 0; i < count; i++) {
      printX(2);
      printf("|%5d| %13s | %3d | %9s |%12s|\n", i + 1, db[i].breed, db[i].age,
             db[i].color, db[i].phone);
    }
    printX(3);
  } else {
    printf("Таблица пуста\n");
  }
}

void add() {
  int a;
  printf("Сколько вы хотите ввести элементов: ");
  scanf("%d", &a);
  while (getchar() != '\n')
    ;
  inputScript(count, a);
}
void search() {
  int choice;
  char s[16];
  int found = 0;
  printf("Выберите категорию для поиска: \n");
  printf("1) Порода\n");
  printf("2) Возраст\n");
  printf("3) Цвет\n");
  printf("4) Телефон\n");
  printf("5) Выход в меню\n");
  scanf("%d", &choice);
  while (getchar() != '\n')
    ;
  if (choice <= 4 && choice >= 1) {
    printf("Введите ваш запрос: ");
    scanf("%s", &s);
  }
  switch (choice) {
    case 1:
      for (int i = 0; i < count; i++) {
        if (strcmp(db[i].breed, s) == 0) {
          if (found == 0) {
            printX(1);
            printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
          }
          printX(2);
          printf("|%5d| %13s | %3d | %9s |%12s|\n", i + 1, db[i].breed,
                 db[i].age, db[i].color, db[i].phone);
          found++;
        }
      }
      break;
    case 2:
      choice = atoi(s);
      for (int i = 0; i < count; i++) {
        if (choice == db[i].age) {
          if (found == 0) {
            printX(1);
            printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
          }
          printX(2);
          printf("|%5d| %13s | %3d | %9s |%12s|\n", i + 1, db[i].breed,
                 db[i].age, db[i].color, db[i].phone);
          found++;
        }
      }
      break;
    case 3:
      for (int i = 0; i < count; i++) {
        if (strcmp(db[i].color, s) == 0) {
          if (found == 0) {
            printX(1);
            printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
          }
          printX(2);
          printf("|%5d| %13s | %3d | %9s |%12s|\n", i + 1, db[i].breed,
                 db[i].age, db[i].color, db[i].phone);
          found++;
        }
      }
      break;
    case 4:
      for (int i = 0; i < count; i++) {
        if (strcmp(db[i].phone, s) == 0) {
          if (found == 0) {
            printX(1);
            printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
          }
          printX(2);
          printf("|%5d| %13s | %3d | %9s |%12s|\n", i + 1, db[i].breed,
                 db[i].age, db[i].color, db[i].phone);
          found++;
        }
      }
      break;
  }
  if (found != 0)
    printX(3);
}

void sort() {
  char choice = 0;
  printf("Выберите предмет сортировки:\n");
  printf("1) Порода\n");
  printf("2) Возраст\n");
  printf("3) Цвет\n");
  printf("4) Телефон\n");
  scanf("%c", &choice);
  while (getchar() != '\n')
    ;
  switch (choice) {
    case '1':
      for (int j = 0; j < count - 1; j++) {
        for (int i = 0; i < count - 1; i++) {
          if (strcmp(db[i].breed, db[i + 1].breed) > 0) {
            db[50] = db[i];
            db[i] = db[i + 1];
            db[i + 1] = db[50];
          }
        }
      }
      output();
      break;
    case '2':
      for (int j = 0; j < count - 1; j++) {
        for (int i = 0; i < count - 1; i++) {
          if (db[i].age > db[i + 1].age) {
            db[50] = db[i];
            db[i] = db[i + 1];
            db[i + 1] = db[50];
          }
        }
      }
      output();
      break;
    case '3':
      for (int j = 0; j < count - 1; j++) {
        for (int i = 0; i < count - 1; i++) {
          if (strcmp(db[i].color, db[i + 1].color) > 0) {
            db[50] = db[i];
            db[i] = db[i + 1];
            db[i + 1] = db[50];
          }
        }
      }
      output();
      break;
    case '4':
      for (int j = 0; j < count - 1; j++) {
        for (int i = 0; i < count - 1; i++) {
          if (strcmp(db[i].phone, db[i + 1].phone) > 0) {
            db[50] = db[i];
            db[i] = db[i + 1];
            db[i + 1] = db[50];
          }
        }
      }
      output();
      break;
    default:
      printf("Опция не найдена. Выход в меню\n");
  }
}

void removeByNum() {
  int order = 0;
  printf("Какой элемент удалить: ");
  scanf("%d", &order);
  for (int i = order; i < count; i++) {
    db[i - 1] = db[i];
  }
  count--;
}

void remove() {
  int choice;
  char s[16];
  printf("Выберите тип удаления: \n");
  printf("1) Порода\n");
  printf("2) Возраст\n");
  printf("3) Цвет\n");
  printf("4) Телефон\n");
  printf("5) Номер элемента\n");
  printf("6) Выход в меню\n");
  scanf("%d", &choice);
  if (choice != 6 && choice != 5) {
    printf("Введите ваш запрос: ");
    scanf("%s", &s);
  }
  int counter = count;
  int found = 0;
  switch (choice) {
    case 1:
      for (int i = 0; i < counter; i++) {
        if (strcmp(db[i].breed, s) == 0) {
          if (found == 0) {
            printX(1);
            printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
          }
          printX(2);
          printf("|%5d| %13s | %3d | %9s |%12s|\n", i + 1, db[i].breed,
                 db[i].age, db[i].color, db[i].phone);
          db[i].breed[0] = 0;
          found++;
          for (int j = i; j < count; j++) {
            db[j] = db[j + 1];
          }
          count--;
          i--;
        }
      }
      break;
    case 2:
      choice = atoi(s);
      for (int i = 0; i < counter; i++) {
        if (choice == db[i].age && count != 0) {
          if (found == 0) {
            printX(1);
            printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
          }
          printX(2);
          printf("|%5d| %13s | %3d | %9s |%12s|\n", i + 1, db[i].breed,
                 db[i].age, db[i].color, db[i].phone);
          db[i].breed[0] = 0;
          found++;
          for (int j = i; j < count; j++) {
            db[j] = db[j + 1];
          }
          count--;
          i--;
        }
      }
      break;
    case 3:
      for (int i = 0; i < counter; i++) {
        if (strcmp(db[i].color, s) == 0) {
          if (found == 0) {
            printX(1);
            printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
          }
          printX(2);
          printf("|%5d| %13s | %3d | %9s |%12s|\n", i + 1, db[i].breed,
                 db[i].age, db[i].color, db[i].phone);
          db[i].breed[0] = 0;
          found++;
          for (int j = i; j < count; j++) {
            db[j] = db[j + 1];
          }
          count--;
          i--;
        }
      }
      break;
    case 4:
      for (int i = 0; i < counter; i++) {
        if (strcmp(db[i].phone, s) == 0) {
          if (found == 0) {
            printX(1);
            printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
          }
          printX(2);
          printf("|%5d| %13s | %3d | %9s |%12s|\n", i + 1, db[i].breed,
                 db[i].age, db[i].color, db[i].phone);
          db[i].breed[0] = 0;
          found++;
          for (int j = i; j < count; j++) {
            db[j] = db[j + 1];
          }
          count--;
          i--;
        }
      }
      break;
    case 5:
      removeByNum();
      break;
  }
  if (found != 0)
    printX(3);
}
void save() {
  char name[255];
  FILE* fp;
  printf("Введите название файла: ");
  scanf("%s", &name);
  strcat(name, ".txt");
  fp = fopen(name, "w");
  char buffer[256] = {0};
  int i = 0;
  for (int i = 0; i < count; i++) {
    fprintf(fp, "%s %d %s %s\n", db[i].breed, db[i].age, db[i].color,
            db[i].phone);
  }
  fclose(fp);
}
void load() {
  count = 0;
  char name[255];
  FILE* fp;
  printf("Введите название файла: ");
  scanf("%s", &name);
  strcat(name, ".txt");
  fp = fopen(name, "r");
  if (fp == NULL) {
    printf("Не существует файл. Выходим в меню.\n");
  } else {
    char buffer[256] = {0};
    int i = 0;
    while (fscanf(fp, "%s%d%s%s", db[i].breed, &db[i].age, db[i].color,
                  db[i].phone) != EOF) {
      i++;
    }
    count = i;
    output();
    fclose(fp);
  }
}
void printX(int tx) {
  setlocale(LC_ALL, ".866");  // псевдографика
  if (tx == 1) {              // верх
    printf("\n");
    printf("%c", 218);
    for (int i = 0; i < 5; i++)
      printf("%c", 196);
    printf("%c", 194);
    for (int i = 0; i < 15; i++)
      printf("%c", 196);
    printf("%c", 194);
    for (int i = 0; i < 5; i++)
      printf("%c", 196);
    printf("%c", 194);
    for (int i = 0; i < 11; i++)
      printf("%c", 196);
    printf("%c", 194);
    for (int i = 0; i < 12; i++)
      printf("%c", 196);
    printf("%c\n", 191);
  }
  if (tx == 2) {  // середина
    printf("%c", 195);
    for (int i = 0; i < 5; i++)
      printf("%c", 196);
    printf("%c", 197);
    for (int i = 0; i < 15; i++)
      printf("%c", 196);
    printf("%c", 197);
    for (int i = 0; i < 5; i++)
      printf("%c", 196);
    printf("%c", 197);
    for (int i = 0; i < 11; i++)
      printf("%c", 196);
    printf("%c", 197);
    for (int i = 0; i < 12; i++)
      printf("%c", 196);
    printf("%c\n", 180);
  }
  if (tx == 3) {  // низ
    printf("%c", 192);
    for (int i = 0; i < 5; i++)
      printf("%c", 196);
    printf("%c", 193);
    for (int i = 0; i < 15; i++)
      printf("%c", 196);
    printf("%c", 193);
    for (int i = 0; i < 5; i++)
      printf("%c", 196);
    printf("%c", 193);
    for (int i = 0; i < 11; i++)
      printf("%c", 196);
    printf("%c", 193);
    for (int i = 0; i < 12; i++)
      printf("%c", 196);
    printf("%c\n", 217);
  }
  if (tx == 4) {
    printf("%c", 218);
    for (int i = 0; i < 25; i++)
      printf("%c", 196);
    printf("%c\n", 191);
  }
  if (tx == 5) {
    printf("%c", 192);
    for (int i = 0; i < 25; i++)
      printf("%c", 196);
    printf("%c\n", 217);
  }
  setlocale(LC_ALL, ".1251");  // русификация
}

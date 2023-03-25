// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
void menu(); void input(); void output(); void add(); void search(); void sort(); void del();
struct cat  { 
    char br[15]; // Порода
    int age; // Возраст
    char color[10]; // Цвет
    char ph[12]; // Телефон продавца
}; struct cat K[50]; // База данных
int last = 0; // Сохраняет последний добавленный элемент
void printX(int tx) {
    setlocale(LC_ALL, ".866");
    if (tx == 1) { //верх
        printf("%c", 218);
        for (int i = 0; i < 5; i++) printf("%c", 196);
        printf("%c", 194);
        for (int i = 0; i < 15; i++) printf("%c", 196);
        printf("%c", 194);
        for (int i = 0; i < 5; i++) printf("%c", 196);
        printf("%c", 194);
        for (int i = 0; i < 11; i++) printf("%c", 196);
        printf("%c", 194);
        for (int i = 0; i < 12; i++) printf("%c", 196);
        printf("%c\n", 191);

    }
    if (tx == 2) { // середина
        printf("%c", 195);
        for (int i = 0; i < 5; i++) printf("%c", 196);
        printf("%c", 197);
        for (int i = 0; i < 15; i++) printf("%c", 196);
        printf("%c", 197);
        for (int i = 0; i < 5; i++) printf("%c", 196);
        printf("%c", 197);
        for (int i = 0; i < 11; i++) printf("%c", 196);
        printf("%c", 197);
        for (int i = 0; i < 12; i++) printf("%c", 196);
        printf("%c\n", 180);
    }
    if (tx == 3) { // низ
        printf("%c", 192);
        for (int i = 0; i < 5; i++) printf("%c", 196);
        printf("%c", 193);
        for (int i = 0; i < 15; i++) printf("%c", 196);
        printf("%c", 193);
        for (int i = 0; i < 5; i++) printf("%c", 196);
        printf("%c", 193);
        for (int i = 0; i < 11; i++) printf("%c", 196);
        printf("%c", 193);
        for (int i = 0; i < 12; i++) printf("%c", 196);
        printf("%c\n", 217);
    }
    setlocale(LC_ALL, ".1251");
}

int main()
{ 
    SetConsoleCP(1251);
    menu();
    return 0;
}
void menu() {
    setlocale(LC_ALL, ".1251");
    int num=0; // Выбор опции
    printf("Добро пожаловать в СУБД\n");
    while (num != 7) {
        printf("1) Ввод в базу данных\n"); //готово
        printf("2) Вывод на экран\n"); //готово
        printf("3) Добавление\n"); //готово
        printf("4) Поиск\n"); //готово
        printf("5) Удаление\n");
        printf("6) Сортировка\n");
        printf("7) Выход\n");
        printf("> ");
        scanf("%d", &num);
        switch (num) {
        case 1:
            input();
            break;
        case 2:
            output();
            break;
        case 3:
            add();
            break;
        case 4:
            search();
            break;
        case 5:
            del();
            break;
        case 6:
            sort();
        }
    }
}

void input() { // Ввод
    int a;
    printf("Сколько вы хотите ввести элементов: ");
    scanf("%d", &a); 
    for (int i = 0; i < a; i++) {
        printf("Порода: ");
        scanf("%s", &K[i].br);
        printf("Возраст: ");
        scanf("%d", &K[i].age);
        printf("Цвет: ");
        scanf("%s", &K[i].color);
        printf("Телефон: ");
        scanf("%s", &K[i].ph);
        last = a;
    } 
}
void output() {
    printX(1);
    printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
    for (int i = 0; i < last; i++) {
        printX(2);
        printf("|  %d  | %13s | %3d | %9s |%12s|\n", i+1, K[i].br, K[i].age, K[i].color, K[i].ph);
    }
    printX(3);
}

void add() {
    int a;
    printf("Сколько вы хотите ввести элементов: ");
    scanf("%d", &a);
    for (int i = last; i < a+last; i++) {
        printf("Порода: ");
        scanf("%s", &K[i].br);
        printf("Возраст: ");
        scanf("%d", &K[i].age);
        printf("Цвет: ");
        scanf("%s", &K[i].color);
        printf("Телефон: ");
        scanf("%s", &K[i].ph);
    }
    last = a + last; // Обновляем счетчик последнего объекта
}

void search() {
    int num;
    printf("Выберите предмет поиска: \n");
    printf("1) Порода, цвет, телефон\n");
    printf("2) Возраст\n");
    printf("3) Выход в меню\n> ");
    scanf("%d", &num);
    printf("Введите предмет поиска\n> ");
    switch (num) {
    case 1: 
        char s[16];
        scanf("%s", &s);
        printX(1);
        printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
        for (int i = 0; i < 50; i++) {
            if (strcmp(K[i].br, s) == 0 || strcmp(K[i].color, s) == 0 || strcmp(K[i].ph, s) == 0) {
                printX(2);
                printf("|  %d  | %13s | %3d | %9s |%12s|\n", i + 1, K[i].br, K[i].age, K[i].color, K[i].ph);
                
            }
            
        } 
        printX(3); 
        break;
    case 2:
        int d;
        scanf("%d", &d);
        printX(1);
        printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
        for (int i = 0; i < 50; i++) {
            if (d == K[i].age) {
                printX(2);
                printf("|  %d  | %13s | %3d | %9s |%12s|\n", i + 1, K[i].br, K[i].age, K[i].color, K[i].ph);
            }
        }
        printX(3);
        break;
    }
}

void sort() {
    int num;
    printf("Выберите предмет поиска: \n");
    printf("1) Порода\n");
    printf("2) Возраст\n");
    printf("3) Цвет\n");
    printf("4) Телефон\n> ");
    scanf("%d", &num);
    switch (num) {
    case 1:
        for (int j = 0; j < last-1; j++) {
            for (int i = 0; i < last-1; i++) {
                if (strcmp(K[i].br, K[i + 1].br) > 0) {
                    char tmp[16]; int temp = 0;
                    strcpy(tmp, K[i].br); // порода
                    strcpy(K[i].br, K[i + 1].br);
                    strcpy(K[i + 1].br, tmp);
                    temp = K[i].age;
                    K[i].age = K[i + 1].age;
                    K[i+1].age = temp;
                    strcpy(tmp, K[i].color); // цвет
                    strcpy(K[i].color, K[i + 1].color);
                    strcpy(K[i + 1].color, tmp);
                    strcpy(tmp, K[i].ph); // телефон
                    strcpy(K[i].ph, K[i + 1].ph);
                    strcpy(K[i + 1].ph, tmp);
                }
            }
        } 
        break;
    case 2:
        for (int j = 0; j < last - 1; j++) {
            for (int i = 0; i < last - 1; i++) {
                if (K[i].age > K[i+1].age) {
                    char tmp[16]; int temp = 0;
                    strcpy(tmp, K[i].br); // порода
                    strcpy(K[i].br, K[i + 1].br);
                    strcpy(K[i + 1].br, tmp);
                    temp = K[i].age;
                    K[i].age = K[i + 1].age;
                    K[i + 1].age = temp;
                    strcpy(tmp, K[i].color); // цвет
                    strcpy(K[i].color, K[i + 1].color);
                    strcpy(K[i + 1].color, tmp);
                    strcpy(tmp, K[i].ph); // телефон
                    strcpy(K[i].ph, K[i + 1].ph);
                    strcpy(K[i + 1].ph, tmp);
                }
            }
        }
        break;
    case 3:
        for (int j = 0; j < last - 1; j++) {
            for (int i = 0; i < last - 1; i++) {
                if (strcmp(K[i].color, K[i + 1].color) > 0) {
                    char tmp[16]; int temp = 0;
                    strcpy(tmp, K[i].br); // порода
                    strcpy(K[i].br, K[i + 1].br);
                    strcpy(K[i + 1].br, tmp);
                    temp = K[i].age;
                    K[i].age = K[i + 1].age;
                    K[i + 1].age = temp;
                    strcpy(tmp, K[i].color); // цвет
                    strcpy(K[i].color, K[i + 1].color);
                    strcpy(K[i + 1].color, tmp);
                    strcpy(tmp, K[i].ph); // телефон
                    strcpy(K[i].ph, K[i + 1].ph);
                    strcpy(K[i + 1].ph, tmp);
                }
            }
        }
        break;
    case 4:
        for (int j = 0; j < last - 1; j++) {
            for (int i = 0; i < last - 1; i++) {
                if (strcmp(K[i].ph, K[i + 1].ph) > 0) {
                    char tmp[16]; int temp = 0;
                    strcpy(tmp, K[i].br); // порода
                    strcpy(K[i].br, K[i + 1].br);
                    strcpy(K[i + 1].br, tmp);
                    temp = K[i].age;
                    K[i].age = K[i + 1].age;
                    K[i + 1].age = temp;
                    strcpy(tmp, K[i].color); // цвет
                    strcpy(K[i].color, K[i + 1].color);
                    strcpy(K[i + 1].color, tmp);
                    strcpy(tmp, K[i].ph); // телефон
                    strcpy(K[i].ph, K[i + 1].ph);
                    strcpy(K[i + 1].ph, tmp);
                }
            }
        }
        break;
    }
}

void del() {
    int k = 0;
    printf("Какой элемент удалить: ");
    scanf("%d", &k);
    strcpy(K[k-1].br, K[last-1].br);
    strcpy(K[last-1].br, "\0");
    K[k - 1].age = K[last - 1].age;
    K[last - 1].age = 0;
    strcpy(K[k - 1].color, K[last - 1].color);
    strcpy(K[last - 1].color, "\0");
    strcpy(K[k - 1].ph, K[last - 1].ph);
    strcpy(K[last - 1].ph, "\0");
    last--;
}


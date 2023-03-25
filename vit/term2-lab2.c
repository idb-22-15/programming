#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

void menu(); void input(); void output(); void add(); void search(); void sort(); void delete();

struct cat  { 
    char br[15]; // Порода
    int age; // Возраст
    char color[10]; // Цвет
    char ph[12]; // Телефон продавца
};

struct cat cats[50]; // База данных

int count = 0; // Сохраняет последний добавленный элемент

void printX(int tx) {
    setlocale(LC_ALL, ".866");
    switch (tx) {
        case 1:
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
            break;
        case 2:
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
            break;
        case 3:
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
            break;
    } 
    setlocale(LC_ALL, ".1251");
}

int main() { 
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
            delete();
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
        scanf("%s", &cats[i].br);
        printf("Возраст: ");
        scanf("%d", &cats[i].age);
        printf("Цвет: ");
        scanf("%s", &cats[i].color);
        printf("Телефон: ");
        scanf("%s", &cats[i].ph);
        count = a;
    } 
}
void output() {
    printX(1);
    printf("|  №  | Порода        |  В. |  Цвет     | Телефон    |\n");
    for (int i = 0; i < count; i++) {
        printX(2);
        printf("|  %d  | %13s | %3d | %9s |%12s|\n", i+1, cats[i].br, cats[i].age, cats[i].color, cats[i].ph);
    }
    printX(3);
}

void add() {
    int a;
    printf("Сколько вы хотите ввести элементов: ");
    scanf("%d", &a);
    for (int i = count; i < a+count; i++) {
        printf("Порода: ");
        scanf("%s", &cats[i].br);
        printf("Возраст: ");
        scanf("%d", &cats[i].age);
        printf("Цвет: ");
        scanf("%s", &cats[i].color);
        printf("Телефон: ");
        scanf("%s", &cats[i].ph);
    }
    count = a + count; // Обновляем счетчик последнего объекта
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
            if (strcmp(cats[i].br, s) == 0 || strcmp(cats[i].color, s) == 0 || strcmp(cats[i].ph, s) == 0) {
                printX(2);
                printf("|  %d  | %13s | %3d | %9s |%12s|\n", i + 1, cats[i].br, cats[i].age, cats[i].color, cats[i].ph);
                
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
            if (d == cats[i].age) {
                printX(2);
                printf("|  %d  | %13s | %3d | %9s |%12s|\n", i + 1, cats[i].br, cats[i].age, cats[i].color, cats[i].ph);
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
        for (int j = 0; j < count-1; j++) {
            for (int i = 0; i < count-1; i++) {
                if (strcmp(cats[i].br, cats[i + 1].br) > 0) {
                    char tmp[16]; int temp = 0;
                    strcpy(tmp, cats[i].br); // порода
                    strcpy(cats[i].br, cats[i + 1].br);
                    strcpy(cats[i + 1].br, tmp);
                    temp = cats[i].age;
                    cats[i].age = cats[i + 1].age;
                    cats[i+1].age = temp;
                    strcpy(tmp, cats[i].color); // цвет
                    strcpy(cats[i].color, cats[i + 1].color);
                    strcpy(cats[i + 1].color, tmp);
                    strcpy(tmp, cats[i].ph); // телефон
                    strcpy(cats[i].ph, cats[i + 1].ph);
                    strcpy(cats[i + 1].ph, tmp);
                    cats[i] = cats[i + 1];
                }
            }
        } 
        break;
    case 2:
        for (int j = 0; j < count - 1; j++) {
            for (int i = 0; i < count - 1; i++) {
                if (cats[i].age > cats[i+1].age) {
                    char tmp[16]; int temp = 0;
                    strcpy(tmp, cats[i].br); // порода
                    strcpy(cats[i].br, cats[i + 1].br);
                    strcpy(cats[i + 1].br, tmp);
                    temp = cats[i].age;
                    cats[i].age = cats[i + 1].age;
                    cats[i + 1].age = temp;
                    strcpy(tmp, cats[i].color); // цвет
                    strcpy(cats[i].color, cats[i + 1].color);
                    strcpy(cats[i + 1].color, tmp);
                    strcpy(tmp, cats[i].ph); // телефон
                    strcpy(cats[i].ph, cats[i + 1].ph);
                    strcpy(cats[i + 1].ph, tmp);
                }
            }
        }
        break;
    case 3:
        for (int j = 0; j < count - 1; j++) {
            for (int i = 0; i < count - 1; i++) {
                if (strcmp(cats[i].color, cats[i + 1].color) > 0) {
                    char tmp[16]; int temp = 0;
                    strcpy(tmp, cats[i].br); // порода
                    strcpy(cats[i].br, cats[i + 1].br);
                    strcpy(cats[i + 1].br, tmp);
                    temp = cats[i].age;
                    cats[i].age = cats[i + 1].age;
                    cats[i + 1].age = temp;
                    strcpy(tmp, cats[i].color); // цвет
                    strcpy(cats[i].color, cats[i + 1].color);
                    strcpy(cats[i + 1].color, tmp);
                    strcpy(tmp, cats[i].ph); // телефон
                    strcpy(cats[i].ph, cats[i + 1].ph);
                    strcpy(cats[i + 1].ph, tmp);
                }
            }
        }
        break;
    case 4:
        for (int j = 0; j < count - 1; j++) {
            for (int i = 0; i < count - 1; i++) {
                if (strcmp(cats[i].ph, cats[i + 1].ph) > 0) {
                    char tmp[16]; int temp = 0;
                    strcpy(tmp, cats[i].br); // порода
                    strcpy(cats[i].br, cats[i + 1].br);
                    strcpy(cats[i + 1].br, tmp);
                    temp = cats[i].age;
                    cats[i].age = cats[i + 1].age;
                    cats[i + 1].age = temp;
                    strcpy(tmp, cats[i].color); // цвет
                    strcpy(cats[i].color, cats[i + 1].color);
                    strcpy(cats[i + 1].color, tmp);
                    strcpy(tmp, cats[i].ph); // телефон
                    strcpy(cats[i].ph, cats[i + 1].ph);
                    strcpy(cats[i + 1].ph, tmp);
                }
            }
        }
        break;
    }
}

void delete() {
    int k = 0;
    printf("Какой элемент удалить: ");
    scanf("%d", &k);
    strcpy(cats[k-1].br, cats[count-1].br);
    strcpy(cats[count-1].br, "\0");
    cats[k - 1].age = cats[count - 1].age;
    cats[count - 1].age = 0;
    strcpy(cats[k - 1].color, cats[count - 1].color);
    strcpy(cats[count - 1].color, "\0");
    strcpy(cats[k - 1].ph, cats[count - 1].ph);
    strcpy(cats[count - 1].ph, "\0");
    count--;
}


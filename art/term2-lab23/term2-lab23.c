#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>

void menu();
void menuFind();
void menuDelete();
void menuSort();

void inputDB();
void outputDB();
void addOne();

void printX();
void printTableTop();
void printTableHead();
void printTableHeadFull();
void printTableBody(struct Consumer, int);
void printTableUnderline();
void printTableBottom();

struct Consumer {
    char name[100];
    char surname[100];
    char email[100];
    int balance;
};

struct Consumer consumers[100];
int count = 0;

int main() {
    menu();
}

void menu() {
    printf("Please, enter command:\n");
    printf("1: input db\n2: output db\n3: add counsumer\n4: find counsumer(s)\n5: delete consumer(s)\n6: sort db\n7: exit\n");
    int command;
    scanf("%d", &command);
    printf("\n");

    switch (command) {
    case 1:
        inputDB();
        menu();
        break;
    case 2:
        outputDB();
        menu();
        break;
    case 3:
        addOne(count);
        menu();
        break;
    case 4:
        menuFind();
        menu();
        break;
    case 5:
        menuDelete();
        menu();
        break;
    case 6:
        menuSort();
        menu();
        break;
    case 7:
        break;
    default:
        menu();
        break;
    }
}

void inputDB() {
    printf("Please, enter items count: ");
    int itemsCount;
    scanf("%d", &itemsCount);
    printf("Please, enter data to DB:\n");
    
    for (int i = 0; i < itemsCount; i++) {
        addOne();
    }
    printf("\n");
}


void outputDB() {
    printTableHeadFull();

    for (int i = 0; i < count; i++) { 
        printTableBody(consumers[i], i);
        if (i + 1 != count) printTableUnderline();
    }
    printTableBottom();
}

void addOne() {
    printf("Please, enter new cunsumer:\n");
    printf("Name    Surname Email   Balance\n");
    scanf("%s%s%s%d", &(consumers[count].name), &(consumers[count].surname), &(consumers[count].email), &(consumers[count].balance));
    count++;
}

void findManyByString();
void findManyByInt();

void menuFind() {
    printf("Find by\n");
    printf("1: name\n2: surname\n3: email\n4: balance\n");
    int findBy;
    scanf("%d", &findBy);

    char string[100];
    int number;
    switch (findBy) {
        case 1:
            printf("Please, enter name: "); 
            scanf("%s", string);
            findManyByString(string, 1);
            break;
        case 2:
            printf("Please, enter surname: ");
            scanf("%s", string);
            findManyByString(string, 2);
            break;
        case 3:
            printf("Please, enter email: ");
            scanf("%s", string);
            findManyByString(string, 3);
            break;
        case 4:
            printf("Please, enter balance: ");
            scanf("%d", &number);
            findManyByInt(number);
            break;
        default:
            menuFind();
            break;
    }
}

void findManyByString(char* string, int findBy) {
    printTableHeadFull();

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
            if (i != 0)  printTableUnderline();
            printTableBody(consumers[i], i);
            if (i != 0 && i + 1 != count) printTableUnderline();
        }
    }
    printTableBottom();
}

void findManyByInt(int number) {
    printTableHeadFull();

    for (int i = 0; i < count; i++) {
        if (consumers[i].balance == number) {
            if (i != 0)  printTableUnderline();
            printTableBody(consumers[i], i);
            if (i != 0 && i + 1 != count) printTableUnderline();
        }
    }
    printTableBottom();
}

void deleteOneByOrder(int);
void deleteManyByString(char*, int);
void deleteManyByInt(int);

void menuDelete() {
    printf("Delete by:\n");
    printf("1: order\n2: name\n3: surname\n4: email\n5: balance\n");
    int deleteBy;
    scanf("%d", &deleteBy);

    char string[100];
    int number;
    switch (deleteBy) {
        case 1:
            printf("Please, enter consumer's order to delete: ");
            int order;
            scanf("%d", &order);
            deleteOneByOrder(order);
            break;
        case 2:
            printf("Please, enter consumers' name to delete: ");
            scanf("%s", &string);
            deleteManyByString(string, 2);
            break;
        case 3:
            printf("Please, enter consumers' surname to delete: ");
            scanf("%s", &string);
            deleteManyByString(string, 3);
            break;
        case 4:
            printf("Please, enter consumers' email to delete: ");
            scanf("%s", &string);
            deleteManyByString(string, 4);
            break;
        case 5:
            printf("Please, enter consumers' balance to delete: ");
            scanf("%d", &number);
            deleteManyByInt(number);
            break;
        default:
            menuDelete();
            break;
    }
}

void deleteOneByOrder(int order) {
    if (order == count) return;

    const index = order - 1;
    for (int i = index; i < count; i++) {
        consumers[i] = consumers[i + 1];
    }
    count--;
    printf("1 consumer was deleted\n");
}

void deleteManyByString(char* string, int deleteBy) {
    int countDeleted = 0;
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
            consumers[i] = consumers[i + 1];
            countDeleted++;
        }
    }
    count -= countDeleted;
    printf("%d consumer(s) was deleted\n\n", countDeleted);
}

void deleteManyByInt(int number) {
    int countDeleted = 0;
    for (int i = 0; i < count; i++) {
        if (consumers[i].balance == number) {
            consumers[i] = consumers[i + 1];
            countDeleted++;
        }
    }
    count -= countDeleted;
    printf("%d consumer(s) was deleted\n\n", countDeleted);
}

void sortSelectionByName();
void sortSelectionBySurname();
void sortSelectionByEmail();
void sortSelectionByBalance();

void menuSort() {
    printf("Sort by:\n");
    printf("1: name\n2: surname\n3: email\n4: balance\n");
    int sortBy;
    scanf("%d", &sortBy);
    switch (sortBy) {
        case 1:
            sortSelectionByName();
            outputDB();
            break;
        case 2:
            sortSelectionBySurname();
            outputDB();
            break;
        case 3:
            sortSelectionByEmail();
            outputDB();
            break;
        case 4:
            sortSelectionByBalance();
            outputDB();
            break;
        default:
            menuSort();
            break;
    }
}

void sortSelectionByName() {
    if (count == 0) return;
    for (int i = 0; i < count; i++) {
        char* min = consumers[i].name;
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (strcmp(consumers[j].name, min) == -1) {
                min = consumers[i].name;
                minIndex = j;
            }
        }
        struct Consumer temp = consumers[i];
        consumers[i] = consumers[minIndex];
        consumers[minIndex] = temp;
    }
}

void sortSelectionBySurname() {
    if (count == 0) return;
    for (int i = 0; i < count; i++) {
        char* min = consumers[i].surname;
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (strcmp(consumers[j].surname, min) == -1) {
                min = consumers[i].surname;
                minIndex = j;
            }
        }
        struct Consumer temp = consumers[i];
        consumers[i] = consumers[minIndex];
        consumers[minIndex] = temp;
    }
}

void sortSelectionByEmail() {
    if (count == 0) return;
    for (int i = 0; i < count; i++) {
        char* min = consumers[i].email;
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (strcmp(consumers[j].email, min) == -1) {
                min = consumers[i].email;
                minIndex = j;
            }
        }
        struct Consumer temp = consumers[i];
        consumers[i] = consumers[minIndex];
        consumers[minIndex] = temp;
    }
}

void sortSelectionByBalance() {
    if (count == 0) return;
    for (int i = 0; i < count; i++) {
        int min = consumers[i].balance;
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (consumers[j].balance < min) {
                min = consumers[i].balance;
                minIndex = j;
            }
        }
        struct Consumer temp = consumers[i];
        consumers[i] = consumers[minIndex];
        consumers[minIndex] = temp;
    }
}


void printX(int tx) {
    const int tw = 196;
    for (int i = 0; i < 13; i++) printf("%c", tw);
    printf("%c", tx);
    for (int i = 0; i < 13; i++) printf("%c", tw);
    printf("%c", tx);
    for (int i = 0; i < 13; i++) printf("%c", tw);
    printf("%c", tx);
    for (int i = 0; i < 13; i++) printf("%c", tw);
    printf("%c", tx);
    for (int i = 0; i < 13; i++) printf("%c", tw);
}

void printTableTop() {
    int ttx = 194;
    int tatl = 218;
    int tatr = 191;

    printf("%c", tatl);
    printX(ttx);
    printf("%c", tatr);
    printf("\n");
}

void printTableHead() {
    int th = 179;
    printf("%c%13s%c%13s%c%13s%c%13s%c%13s%c\n", th, "No", th, "Name", th, "Surname", th, "Email", th, "Balance", th);
}

void printTableHeadFull() {
    printTableTop();
    printTableHead();
    printTableUnderline();
}

void printTableBody(struct Consumer consumer, int index) {
    int order = index + 1;
    int th = 179;
    printf("%c%13d%c%13s%c%13s%c%13s%c%13d%c\n", th, order, th, consumer.name, th, consumer.surname, th, consumer.email, th, consumer.balance, th);
}

void printTableUnderline() {
    int txl = 195;
    int txr = 180;
    int tx = 197;

    printf("%c", txl);
    printX(tx);
    printf("%c", txr);
    printf("\n");
}

void printTableBottom() {
    int tbx = 193;
    int tabl = 192;
    int tabr = 217;

    printf("%c", tabl);
    printX(tbx);
    printf("%c", tabr);
    printf("\n");
}
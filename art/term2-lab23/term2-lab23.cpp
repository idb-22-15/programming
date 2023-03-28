#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

void menu();

void menuInput();
void inputFromDb();
void inputFromConsole();

void menuOutput();
void outputInDb();
void outputInConsole();

void menuAdd();
void addOne();

void menuFind();
void findManyByString(const char*, int);
void findManyByInt(int);

void menuDelete();

void menuSort();
void sortSelectionByName();
void sortSelectionBySurname();
void sortSelectionByEmail();
void sortSelectionByBalance();

void printTableX();
void printTableTop();
void printTableHead();
void printTableHeadFull();
void printTableBody(const struct Consumer, int);
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

const char* UNEXPECTED_COMMAND = "Unexpected command\n";

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void setColor(unsigned int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void resetColor() {
    SetConsoleTextAttribute(hConsole, 15);
}

void setColorMenu() {
    SetConsoleTextAttribute(hConsole, 14);
}

int main() {
    resetColor();
   
    for (int color = 1; color < 16; color++)
    {
        setColor(color);
        printf("%3d  %s\n", color, "I want to be nice today!");
    }
    try {
        menu();
    }
    catch (...) {
        printf("FUCK\n");
        return 0;
    }
}

void menu() {
    setColorMenu();
    printf("Please, enter command:\n");
    printf("1: input db\n2: output db\n3: add counsumer\n4: find counsumer(s)\n5: delete consumer(s)\n6: sort db\n7: exit\n> ");
    resetColor();

    int command;
    try {
        scanf("%d", &command);
    } catch (...) {
        printf(UNEXPECTED_COMMAND);
        menu();
        return;
    }

    switch (command) {
        case 1:
            menuInput();
            menu();
            break;
        case 2:
            menuOutput();
            menu();
            break;
        case 3:
            menuAdd();
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

void menuInput() {
    setColorMenu();
    printf("Enter data from:\n");
    printf("1: db\n2: console\n> ");
    resetColor();

    int command;
    try {
        scanf("%d", &command);
    } catch (...) {
        printf(UNEXPECTED_COMMAND);
        menuInput();
        return;
    }

    switch (command) {
        case 1:
            inputFromDb();
            outputInConsole();
            break;
        case 2:
            inputFromConsole();
            outputInConsole();
            break;
        default:
            menuInput();
    }
}

void inputFromDb() {
    printf("Trying to read from db\n");

    FILE* file = fopen("db.txt", "r");

    if (file == 0) {
        printf("No db file");
        return;
    }

    try {
        count = 0;
        int i = 0;
        while (fscanf(file, "%s%s%s%d", consumers[i].name, consumers[i].surname, consumers[i].email, &consumers[i].balance) != EOF) {
            i++;
            count++;
        }
    } catch (...) {
        printf("Failed to load data from db\n");
    }

    fclose(file);
}

void inputFromConsole() {
    setColorMenu();
    printf("Please, enter items count: ");
    resetColor();

    int itemsCount;
    try {
        scanf("%d", &itemsCount);
    } catch (...) {
        printf(UNEXPECTED_COMMAND);
        inputFromConsole();
        return;
    }

    try {
        setColorMenu();
        printf("Please, enter data to DB:\n");
        resetColor();

        count = 0;
        for (int i = 0; i < itemsCount; i++) {
            addOne();
        }
        printf("\n");
    } catch (...) {
        printf("Failed to add new consumer");
    }
  
}

void menuOutput() {
    setColorMenu();
    printf("Write data to:\n");
    printf("1: db\n2: console\n> ");
    resetColor();

    int command;
    try {
        scanf("%d", &command);
    } catch (...) {
        printf(UNEXPECTED_COMMAND);
        menuOutput();
        return;
    }

    switch (command) {
        case 1:
            outputInDb();
            break;
        case 2:
            outputInConsole();
            break;
        default:
            menuOutput();
            break;
    }
}

void outputInDb() {
    FILE* file = fopen("db.txt", "w");

    if (file == 0) {
        printf("No db file\n");
        return;
    }

    try {
        for (int i = 0; i < count; i++) {
            const struct Consumer consumer = consumers[i];
            fprintf(file, "%s %s %s %d\n", consumer.name, consumer.surname, consumer.email, consumer.balance);
        }
    } catch (...) {
        printf("Failed to write in db\n");
    }

    fclose(file);
}

void outputInConsole() {
    printTableHeadFull();

    for (int i = 0; i < count; i++) {
        printTableBody(consumers[i], i);
        if (i + 1 != count) printTableUnderline();
    }
    printTableBottom();
}

void menuAdd() {
    try {
        addOne();
    } catch (...) {
        printf("Failed to add concumer\n");
    }
    
}

void addOne() {
    setColorMenu();
    printf("Please, enter new cunsumer:\n");
    printf("Name    Surname Email   Balance\n");
    resetColor();

    scanf("%s%s%s%s", consumers[count].name,consumers[count].surname, consumers[count].email, consumers[count].balance);
    count++;
}

void menuFind() {
    setColorMenu();
    printf("Find by\n");
    printf("1: name\n2: surname\n3: email\n4: balance\n> ");
    resetColor();

    int findBy;
    try {
        scanf("%d", &findBy);
    } catch (...) {
        printf(UNEXPECTED_COMMAND);
        menuFind();
        return;
    }
    
    char string[100];
    int number;
    try {
        switch (findBy) {
            case 1:
                setColorMenu();
                printf("Please, enter name: ");
                scanf("%s", string);
                resetColor();

                findManyByString(string, 1);
                break;
            case 2:
                setColorMenu();
                printf("Please, enter surname: ");
                scanf("%s", string);
                resetColor();

                findManyByString(string, 2);
                break;
            case 3:
                setColorMenu();
                printf("Please, enter email: ");
                scanf("%s", string);
                resetColor();

                findManyByString(string, 3);
                break;
            case 4:
                setColorMenu();
                printf("Please, enter balance: ");
                scanf("%d", &number);
                resetColor();

                findManyByInt(number);
                break;
            default:
                menuFind();
                break;
        }
    } catch (...) {
        printf(UNEXPECTED_COMMAND);
        menuFind();
    }
}

void findManyByString(const char* string, int findBy) {
    printTableHeadFull();
    int countFinded = 0;
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
            if (countFinded != 0)  printTableUnderline();
            printTableBody(consumers[i], i);
            countFinded++;
        }
    }
    printTableBottom();
}

void findManyByInt(int number) {
    printTableHeadFull();
    int countFinded = 0;
    for (int i = 0; i < count; i++) {
        if (consumers[i].balance == number) {
            if (countFinded != 0)  printTableUnderline();
            printTableBody(consumers[i], i);
            countFinded++;
        }
    }
    printTableBottom();
}

void menuDelete() {
    void deleteOneByOrder(int);
    void deleteManyByString(const char*, int);
    void deleteManyByInt(int);

    setColorMenu();
    printf("Delete by:\n");
    printf("1: order\n2: name\n3: surname\n4: email\n5: balance\n> ");
    resetColor();

    int deleteBy;
    try {
        scanf("%d", &deleteBy);
    } catch (...) {
        printf(UNEXPECTED_COMMAND);
        return;
    }
   

    char string[100];
    int number;
    switch (deleteBy) {
        case 1:
            setColorMenu();
            printf("Please, enter consumer's order to delete: ");
            int order;
            scanf("%d", &order);
            resetColor();

            deleteOneByOrder(order);
            break;
        case 2:
            setColorMenu();
            printf("Please, enter consumers' name to delete: ");
            scanf("%s", &string);
            resetColor();

            deleteManyByString(string, 2);
            break;
        case 3:
            setColorMenu();
            printf("Please, enter consumers' surname to delete: ");
            scanf("%s", &string);
            resetColor();

            deleteManyByString(string, 3);
            break;
        case 4:
            setColorMenu();
            printf("Please, enter consumers' email to delete: ");
            scanf("%s", &string);
            resetColor();

            deleteManyByString(string, 4);
            break;
        case 5:
            setColorMenu();
            printf("Please, enter consumers' balance to delete: ");
            scanf("%d", &number);
            resetColor();

            deleteManyByInt(number);
            break;
        default:
            menuDelete();
            break;
    }
}

void deleteOneByOrder(int order) {
    if (order > count) {
        printf("No consumer with such order\n");
        return;
    }

    const int index = order - 1;
    for (int i = index; i < count; i++) {
        consumers[i] = consumers[i + 1];
    }
    count--;
    printf("1 consumer was deleted\n");
}

void deleteManyByString(const char* string, int deleteBy) {
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
                if (strcmp(extraParam, string) == 0) i--;
            }
            countDeleted++;
        }
    }
    count -= countDeleted;
    printf("%d consumer(s) was deleted\n\n", countDeleted);
}

void deleteManyByInt(int number) {
    //printf("AAAAA %d\n", number);
    int countDeleted = 0;
    for (int i = 0; i < count; i++) {
        if (consumers[i].balance == number) {
            for (int j = i; j < count; j++) {
                consumers[j] = consumers[j + 1];
                if (consumers[j].balance == number) i--;
            }
            countDeleted++;
        }
    }
    count -= countDeleted;
    printf("%d consumer(s) was deleted\n\n", countDeleted);
}



void menuSort() {
    setColorMenu();
    printf("Sort by:\n");
    printf("1: name\n2: surname\n3: email\n4: balance\n> ");
    resetColor();

    int sortBy;
    try {
        scanf("%d", &sortBy);
    } catch (...) {
        printf("Unexpected command\n");
        menuSort();
        
        return;
    }

    switch (sortBy) {
        case 1:
            sortSelectionByName();
            outputInConsole();
            break;
        case 2:
            sortSelectionBySurname();
            outputInConsole();
            break;
        case 3:
            sortSelectionByEmail();
            outputInConsole();
            break;
        case 4:
            sortSelectionByBalance();
            outputInConsole();
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
                min = consumers[j].balance;
                minIndex = j;
            }
        }

        const struct Consumer temp = consumers[i];
        consumers[i] = consumers[minIndex];
        consumers[minIndex] = temp;
    }
}


void printTableX(int tx) {
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
    const int ttx = 194;
    const int tatl = 218;
    const int tatr = 191;

    printf("%c", tatl);
    printTableX(ttx);
    printf("%c", tatr);
    printf("\n");
}

void printTableHead() {
    const int th = 179;
    printf("%c%13s%c%13s%c%13s%c%13s%c%13s%c\n", th, "No", th, "Name", th, "Surname", th, "Email", th, "Balance", th);
}

void printTableHeadFull() {
    printTableTop();
    printTableHead();
    printTableUnderline();
}

void printTableBody(const struct Consumer consumer, int index) {
    const int order = index + 1;
    const int th = 179;
    printf("%c%13d%c%13s%c%13s%c%13s%c%13d%c\n", th, order, th, consumer.name, th, consumer.surname, th, consumer.email, th, consumer.balance, th);
}

void printTableUnderline() {
    const int txl = 195;
    const int txr = 180;
    const int tx = 197;

    printf("%c", txl);
    printTableX(tx);
    printf("%c", txr);
    printf("\n");
}

void printTableBottom() {
    const int tbx = 193;
    const int tabl = 192;
    const int tabr = 217;

    printf("%c", tabl);
    printTableX(tbx);
    printf("%c", tabr);
    printf("\n");
}
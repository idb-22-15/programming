#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
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
void findManyByString(char*, int);
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
void printTableBody(struct Consumer, int);
void printTableUnderline();
void printTableItemUnderline();
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
    fflush(stdout);
    SetConsoleTextAttribute(hConsole, color);
}

void resetColor() {
    fflush(stdout);
    SetConsoleTextAttribute(hConsole, 15);
}

void setColorMenu() {
    fflush(stdout);
    SetConsoleTextAttribute(hConsole, 14);
}

void setColorError() {
    fflush(stdout);
    SetConsoleTextAttribute(hConsole, 4);
}

void setColorSuccess() {
    fflush(stdout);
    SetConsoleTextAttribute(hConsole, 10);
}

void printSuccess(const char* message) {
    setColorSuccess();
    printf(message);
    resetColor();
}

void printError(const char* message) {
    setColorError();
    printf(message);
    resetColor();
}


int main() {
    resetColor();
    __try {
        menu();
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        printError("\nSomething went wrong :(\n");
    }
    
}

void menu() {
    while (true) {
        fflush(stdout);
        setColorMenu();
        printf("Please, enter command:\n");
        printf("\t1: input db\t\t4: find counsumer(s)\t\t7: exit\n\t2: output db\t\t5: delete consumer(s)\n\t3: add counsumer\t6: sort db\n> ");
        //printf("\t1: input db\n\t2: output db\n\t3: add counsumer\n\t4: find counsumer(s)\n\t5: delete consumer(s)\n\t6: sort db\n\t7: exit\n> ");
        resetColor();

        char commandString[100] = "";
        int command = 0;

        scanf("%s", commandString);
        command = atoi(commandString);
        switch (command) {
            case 1:
                menuInput();
                break;
            case 2:
                menuOutput();
                break;
            case 3:
                menuAdd();
                break;
            case 4:
                menuFind();
                break;
            case 5:
                menuDelete();
                break;
            case 6:
                menuSort();
                break;
            case 7:
                exit(0);
                break;
            default:
                break;
        }
    }
}

void menuInput() {
    setColorMenu();
    printf("Enter data from:\n");
    printf("\t1: db\t\t\t2: console\n> ");
    resetColor();

    char commandString[100] = "";
    int command;

    scanf("%s", commandString);
    command = atoi(commandString);

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

    __try {
        count = 0;
        int i = 0;
        while (fscanf(file, "%s%s%s%d", consumers[i].name, consumers[i].surname, consumers[i].email, &consumers[i].balance) != EOF) {
            i++;
            count++;
        }
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        printError("Failed to load data from db\n");
    }

    fclose(file);
}

void inputFromConsole() {
    setColorMenu();
    printf("Please, enter items count: ");
    resetColor();

    char itemsCountString[100] = "";
    int itemsCount;

   
    scanf("%s", &itemsCountString);
    
    if (!isdigit(itemsCountString[0])) {
        printError(UNEXPECTED_COMMAND);
        return;
    }

    itemsCount = atoi(itemsCountString);

    try {
        setColorMenu();
        printf("Please, enter data to DB:\n");
        resetColor();

        count = 0;
        for (int i = 0; i < itemsCount; i++) {
            addOne();
        }
        printf("\n");
    } catch(const char* errorMessage){
        printError("Failed to add new consumer\n");
    }
  
}

void menuOutput() {
    setColorMenu();
    printf("Write data to:\n");
    printf("\t1: db\t\t\t2: console\n> ");
    resetColor();

    char commandString[100] = "";
    int command;

    scanf("%s", commandString);
    command = atoi(commandString);

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

    __try {
        for (int i = 0; i < count; i++) {
            const struct Consumer consumer = consumers[i];
            fprintf(file, "%s %s %s %d\n", consumer.name, consumer.surname, consumer.email, consumer.balance);
        }
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        printError("Failed to write in db\n");
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
    } catch(const char* errorMessage) {
        printError(errorMessage);
    }
}

void addOne() {
    setColorMenu();
    printf("Please, enter new consumer:\n");
    printf("Name    Surname Email   Balance\n");
    resetColor();
    char balanceString[100] = "";
   
    scanf("%s%s%s%s", consumers[count].name, consumers[count].surname, consumers[count].email, &balanceString);
    consumers[count].balance = atoi(balanceString);

    if (isdigit(balanceString[0])) {
        consumers[count].balance = atoi(balanceString);
    } else if (atoi(balanceString) == 0) throw "Invalid data\n";

    printSuccess("Consumer was added\n");
    count++;
}

void menuFind() {
    setColorMenu();
    printf("Find by\n");
    printf("\t1: name\t\t\t3: email\n\t2: surname\t\t4: balance\n> ");
    resetColor();

    char findByString[100] = "";
    int findBy;

    scanf("%s", findByString);
    findBy = atoi(findByString);
    
    char string[100];
    char numberString[100];
    int number;
   
    switch (findBy) {
        case 1:
            setColorMenu();
            printf("Please, enter name: ");
            resetColor();
            scanf("%s", string);

            findManyByString(string, 1);
            break;
        case 2:
            setColorMenu();
            printf("Please, enter surname: ");
            resetColor();
            scanf("%s", string);

            findManyByString(string, 2);
            break;
        case 3:
            setColorMenu();
            printf("Please, enter email: ");
            resetColor();
            scanf("%s", string);

            findManyByString(string, 3);
            break;
        case 4:
            setColorMenu();
            printf("Please, enter balance: ");
            resetColor();
            scanf("%s", numberString);

            if (!isdigit(numberString[0])) {
                printError(UNEXPECTED_COMMAND);
                break;
            }
            number = atoi(numberString);
            findManyByInt(number);
            break;
        default:
            menuFind();
            break;
    }
  
}

void findManyByString(char* string, int findBy) {
    printTableHeadFull();
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
            if (countFounded != 0)  printTableUnderline();
            printTableBody(consumers[i], i);
            countFounded++;
        }
    }
    printTableBottom();
    setColorSuccess();
    printf("%d consumer(s) was(were) found\n", countFounded);
    resetColor();
}

void findManyByInt(int number) {
    printTableHeadFull();
    int countFounded = 0;
    for (int i = 0; i < count; i++) {
        if (consumers[i].balance == number) {
            if (countFounded != 0)  printTableUnderline();
            printTableBody(consumers[i], i);
            countFounded++;
        }
    }
    printTableBottom();
    setColorSuccess();
    printf("%d consumer(s) was(were) found\n", countFounded);
    resetColor();
}

void menuDelete() {
    void deleteOneByOrder(int);
    void deleteManyByString(const char*, int);
    void deleteManyByInt(int);

    setColorMenu();
    printf("Delete by:\n");
    printf("\t1: order\t\t3: surname\t\t\t5: balance\n\t2: name\t\t\t4: email\n> ");
    resetColor();

    char deleteByString[100] = "";
    int deleteBy;

    scanf("%s", &deleteByString);
    deleteBy = atoi(deleteByString);
   

    char string[100];
    char numberString[100];
    int number;
    switch (deleteBy) {
        case 1:
            setColorMenu();
            printf("Please, enter consumer's order to delete: ");
            resetColor();
            int order;
            scanf("%d", &order);
            
            deleteOneByOrder(order);
            break;
        case 2:
            setColorMenu();
            printf("Please, enter consumers' name to delete: ");
            resetColor();
            scanf("%s", &string);
            
            deleteManyByString(string, 2);
            break;
        case 3:
            setColorMenu();
            printf("Please, enter consumers' surname to delete: ");
            resetColor();
            scanf("%s", &string);
            
            deleteManyByString(string, 3);
            break;
        case 4:
            setColorMenu();
            printf("Please, enter consumers' email to delete: ");
            resetColor();
            scanf("%s", &string);
            
            deleteManyByString(string, 4);
            break;
        case 5:
            setColorMenu();
            printf("Please, enter consumers' balance to delete: ");
            resetColor();
            scanf("%s", numberString);
            if (!isdigit(numberString[0])) {
                printError(UNEXPECTED_COMMAND);
                break;
            }
            number = atoi(numberString);
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
    printSuccess("1 consumer was deleted\n");
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
    setColorSuccess();
    printf("%d consumer(s) was(were) deleted\n", countDeleted);
    resetColor();
}

void deleteManyByInt(int number) {
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
    setColorSuccess();
    printf("%d consumer(s) was deleted\n", countDeleted);
    resetColor();
}



void menuSort() {
    setColorMenu();
    printf("Sort by:\n");
    printf("\t1: name\t\t\t3: email\n\t2: surname\t\t4: balance\n> ");
    resetColor();

    char sortByString[100] = "";
    int sortBy;

    scanf("%s", &sortByString);
    sortBy = atoi(sortByString);

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
        for (int j = i + 1; j < count; j++) {
            if (strcmp(consumers[i].name, consumers[j].name) == 1) {
                struct Consumer temp = consumers[i];
                consumers[i] = consumers[j];
                consumers[j] = temp;
            }
        }
    }

    
}

void sortSelectionBySurname() {
    if (count == 0) return;

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

void sortSelectionByEmail() {
    if (count == 0) return;

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

void sortSelectionByBalance() {
    if (count == 0) return;

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


void printTableItemUnderline() {
    const int tw = 196;
    for (int c = 0; c < 13; c++) printf("%c", tw);
}

void printTableX(int tx) {
   
    const int columns = 5;

    for (int i = 0; i < columns - 1; i++) {
        printTableItemUnderline();
        printf("%c", tx);
    }
    printTableItemUnderline();
    
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

void printTableBody(struct Consumer consumer, int index) {
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
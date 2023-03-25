// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
 // 12 задача
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

void input(int A[10][10], int x, int y) {
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++) {
            scanf_s("%d", &A[i][j]);
        }
         
}
void printline() {
    printf("%c", 195);
    for (int i = 1; i <= 17; i++) {
        if (i % 6 == 0 && i != 0) {
            printf("%c", 197);
        }
        else {
            printf("%c", 196);
        }
    }
    printf("%c\n", 180);
}
void work(int A[10][10], int x, int y, int sum) { 
    printf("%c", 218);
    for (int i = 1; i <= 17; i++) {
        if (i % 6 == 0 && i != 0) {
            printf("%c", 194);
        }
        else {
            printf("%c", 196);
        }
    }
    printf("%c\n", 191);
    printf("%c  i  %c  j  %c Res %c\n", 179, 179, 179, 179);
    int max = 0;
    for (int k = 0; k < x; k++) {
        for (int m = 0; m < y; m++) {
            int max = -8888888;
            for (int i = 1; (k+i) < x; i++) { // проверка вниз
                if (A[k+i][m] > max) {
                    max = A[k+i][m];
                    sum = k+i + m+2;
                }
            }
            for (int j = m; j < y; j++) { // проверка право
                if (A[k][j] > max) {
                    max = A[k][j];
                    sum = k + j+2;
                }
            }
            for (int j = m; j >= 0; j--) { // влево снизу
                if (k + 3 < x) {
                    if (A[k + 3][j] > max) {
                        max = A[k + 3][j];
                        sum = k + 3 + j + 2;
                    }
                }
            }
            printline();
            printf("%c  %d  %c  %d  %c  %d  %c\n",179, k+1, 179, m+1, 179 ,sum,179);
            
        }
    }
    printf("%c", 192);
    for (int i = 1; i <= 17; i++) {
        if (i % 6 == 0 && i != 0) {
            printf("%c", 193);
        }
        else {
            printf("%c", 196);
        }
    }
    printf("%c\n", 217);
    
}

int main()
{
    srand(time(NULL));
    int x, y, A[10][10];
    int sum = 0;
    printf("Size of matrix: "); 
    scanf_s("%d %d", &x, &y);
    input(A, x, y);
    work(A, x, y, sum);
}
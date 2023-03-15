#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

void inputArray(int array[10][10], int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("Input array element i = %d, j = %d:", i, j);
			scanf("%d", &array[i][j]);
		}
	}
}

int getResult(int array[10][10], int n, int m, int row, int col) {
	int max = array[row][col];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int isAbove = ((i == (j + row - col)) && i < row&& j < col);
			int isRect = (i >= row && j >= col);
			if (isAbove || isRect) {

				if (max < array[i][j]) max = array[i][j];
				//printf("%d ", array[i][j]);
			}
			else {
				//printf("* ");
			}
		}
		//printf("\n");
	}

	return max;
}

void printX(int tx) {
	int tw = 196;
	for (int i = 0; i < 7; i++) printf("%c", tw);
	printf("%c", tx);
	for (int i = 0; i < 7; i++) printf("%c", tw);
	printf("%c", tx);
	for (int i = 0; i < 7; i++) printf("%c", tw);
	printf("%c", tx);
	for (int i = 0; i < 7; i++) printf("%c", tw);
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

void printTableBody() {
	int txl = 195;
	int txr = 180;
	int tx = 197;

	printf("%c", txl);
	printX(tx);
	printf("%c", txr);
	printf("\n");
}

void printTableUnderline() {
	int tbx = 193;
	int tabl = 192;
	int tabr = 217;

	printf("%c", tabl);
	printX(tbx);
	printf("%c", tabr);
	printf("\n");
}

int main()
{
	int arr[10][10];

	int n;
	printf("Input n: ");
	scanf("%d", &n);

	int m;
	printf("Input m: ");
	scanf("%d", &m);

	inputArray(arr, n, m);

	int th = 179;

	printTableTop();
	printf("%cNo	%ci	%cj	%cResult	%c\n", th, th, th, th, th);
	printTableBody();

	int number = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {

			int max = getResult(arr, n, m, i, j);

			printf("%c%d	%c%d	%c%d	%c%d	%c\n", th, number, th, i, th, j, th, max, th);

			if (i + 1 == n && j + 1 == m) printTableUnderline();
			else printTableBody();
				
			number++;
		}
	}
}


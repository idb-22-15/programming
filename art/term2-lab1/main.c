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
			bool isAbove = ((i == (j + row - col)) && i < row&& j < col);
			bool isRect = (i >= row && j >= col);
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

void printX(int tx = 197) {
	int tb = 196;
	for (int i = 0; i < 7; i++) printf("%c", tb);
	printf("%c", tx);
	for (int i = 0; i < 7; i++) printf("%c", tb);
	printf("%c", tx);
	for (int i = 0; i < 7; i++) printf("%c", tb);
	printf("%c", tx);
	for (int i = 0; i < 7; i++) printf("%c", tb);
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

	int td = 179;
	int tatl = 218;
	int tatr = 191;
	int tabl = 192;
	int tabr = 217;
	int tb = 196;
	int tl = 195;
	int tr = 180;
	int tx = 197;
	int ttx = 194;
	int tbx = 193;

	printf("%c", tatl);
	printX(ttx);
	printf("%c", tatr);

	printf("\n%cNo	%ci	%cj	%cResult	%c\n", td, td, td, td, td);
	printf("%c", tl);
	printX();
	printf("%c", tr);
	printf("\n");

	int number = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {

			int max = getResult(arr, n, m, i, j);
			
			printf("%c%d	%c%d	%c%d	%c%d	%c\n", td, number, td, i, td, j, td, max, td);
		
			if (i + 1 == n && j + 1 == m) {
				printf("%c", tabl);
				printX(tbx);
				printf("%c", tabr);
				printf("\n");
			}
			else {
				printf("%c", tl);
				printX();
				printf("%c", tr);
				printf("\n");
			}
			number++;
		}
	}
}



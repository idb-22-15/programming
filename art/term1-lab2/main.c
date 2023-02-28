#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>


void example() 
{
	int N, i, k, a[20];
	do {
		printf("Пожалуйста, введите размер массива:\n");
		scanf("%d", &N);
	} while (N < 0 || N > 20);

	printf("Пожалуйста, введите элементы: ");
	i = 0;
	while (i < N)
	{
		scanf("%d", &a[i]);
		i++;
	}

	i = 0;
	k = 0;
	while (i < N)
	{
		if (a[i] > 0)
			if (a[i] < i)
				k++;
		i++;
	}
	printf("Результат, %d", k);
}


void green14() 
{
	int N;

	do {
		printf("Введите количество элементов массива: ");
		scanf("%d", &N);
	} while (N < 0 || N > 10);

	int i = 0;
	int arr[10];
	printf("Введите элементы массива:\n");
	while (i < N)
	{
		scanf("%d", &arr[i]);
		i++;
	}

	i = 0;
	int j;
	while (i < N)
	{

		j = i + 1;
		while (j < N) {
			if (arr[i] == arr[j]) {
				printf("Значение 1: %d, Индекс 1: %d\n", arr[i], i);
				printf("Значение 2: %d, Индекс 2: %d\n", arr[j], j);
			}
			j++;
		}
		i++;
	}
}

void orange47() {

	int N;

	do {
		printf("Введите количество элементов массива: ");
		scanf("%d", &N);
	} while (N <= 0 || N > 10);

	int i = 0;
	int arr[10];
	printf("Введите элементы массива:\n");
	while (i < N)
	{
		scanf("%d", &arr[i]);
		i++;
	}

	int count = 0;

	i = 0;
	while (i < N)
	{
		int flag = 1;
		int j = 0;
		while (j < N) {
			if (i == j) {
				j++;
				continue;
			}
			if (arr[i] == arr[j] || arr[i] == -arr[j]) {
				flag = 0;
				break;
			}
			j++;
		}

		if (flag == 1) count++;

		i++;
	}
	printf("Count: %d", count);
}


int main()
{
    setlocale(0, "");
	orange47();

}

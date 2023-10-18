#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>

void example1();
void example1_input(int[10], int);
int example1_process(int[10], int, int);

void orange47();

int set_array_length();
void array_input(int[10], int*);
int process(int[10], int);
void print_answer(int);

int main() {
  setlocale(0, "");
  orange47();
}

void orange47() {
  int n;
  n = set_array_length();

  int arr[10];
  array_input(arr, &n);

  int count = process(arr, n);

  print_answer(count);
}

int set_array_length() {
  int length;
  do {
    printf("Введите количество элементов массива: ");
    scanf("%d", &length);
  } while (length <= 0 || length > 10);
  return length;
}

void array_input(int array[10], int* plength) {
  int length = *plength;
  printf("Введите элементы массива:\n");
  for (int i = 0; i < length; i++)
    scanf("%d", &array[i]);
}

int process(int arr[10], int N) {
  int count = 0;
  int i = 0;
  while (i < N) {
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

    if (flag == 1)
      count++;

    i++;
  }
}

void print_answer(int count) {
  printf("Count: %d", count);
}

void example1_input(int arr[10], int n) {
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }
}

int example1_process(int arr[10], int count, int n) {
  for (int i = 0; i < n; i++) {
    if (arr[i] > 0)
      count++;
  }
  return count;
}

void example1() {
  int n = 10;
  int arr[10];

  example1_input(arr, n);

  int count = 0;
  count = example1_process(arr, count, n);

  printf("%d", count);
}

void green14() {
  int N;

  do {
    printf("Введите количество элементов массива: ");
    scanf("%d", &N);
  } while (N < 0 || N > 10);

  int i = 0;
  int arr[10];
  printf("Введите элементы массива:\n");
  while (i < N) {
    scanf("%d", &arr[i]);
    i++;
  }

  i = 0;
  int j;
  while (i < N) {
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

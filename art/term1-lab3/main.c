#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void example() {
  int N, M, arr[20][20];
  do {
    printf("Input N and M:");
    scanf("%d%d", &N, &M);
  } while ((N <= 0 || N > 20) || (M <= 0 || M > 20));

  printf("Input matrix:\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      scanf("%d", &arr[i][j]);
    }
  }

  for (int j = 0; j < M; j++) {
    int otr = 0;
    int max = arr[0][j];
    for (int i = 0; i < N; i++) {
      if (max < arr[i][j])
        max = arr[i][j];
      if (arr[i][j] < 0)
        otr++;
      if (arr[i][j] > 0)
        otr--;
    }
    if (otr > 0)
      arr[N - 1][j] = max;
  }

  for (int i = 0; i < N; i++) {
    printf("\n");
    for (int j = 0; j < M; j++) {
      printf("%d ", arr[i][j]);
    }
  }
}

void green10() {
  // провека на дурака
  int N, M, arr[20][20];
  do {
    printf("Input N and M:");
    scanf("%d%d", &N, &M);
  } while ((N <= 0 || N > 20) || (M <= 0 || M > 20));

  // ввод массива
  printf("Input matrix:\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      scanf("%d", &arr[i][j]);
    }
  }

  int sum_max = 0;
  for (int i = 0; i < N; i++) {
    int row_max = arr[i][0];
    for (int j = 1; j < M; j++) {
      if (arr[i][j] > row_max)
        row_max = arr[i][j];
    }
    sum_max += row_max;
  }

  int arifm = sum_max / N;
  printf("Arifm: %d", arifm);
}

void red70() {
  // провека на дурака
  int N, M, arr[20][20];
  do {
    printf("Input N and M:");
    scanf("%d%d", &N, &M);
  } while ((N <= 0 || N > 20) || (M <= 0 || M > 20));

  // ввод массива
  printf("Input matrix:\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      scanf("%d", &arr[i][j]);
    }
  }

  int rows[20];

  for (int i = 0; i < N; i++) {
    int count = 0;
    for (int j = 0; j < M; j++) {
      int el = arr[i][1];
      if (arr[i][j] > el)
        count++;
    }
    rows[i] = count;
  }

  int row = rows[0];
  for (int i = 1; i < N; i++) {
    if (rows[i] < row) {
      row = rows[i];
    }
  }

  for (int i = 0; i < N; i++) {
    if (rows[i] == row)
      printf("Row index: %d\n", i);
  }
}

int main() {
  red70();
}

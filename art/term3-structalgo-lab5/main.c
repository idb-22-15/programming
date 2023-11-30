#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* first, int* second) {
  int tmp = *first;
  *first = *second;
  *second = tmp;
}

void println_array(const int* const arr, unsigned len) {
  for (int i = 0; i < len; i++) {
    printf("%d\t", arr[i]);
  }
  printf("\n");
}

void println_array_with_pointers(const int* const arr,
                                 unsigned len,
                                 const int* const p1,
                                 const int* const p2) {
  for (int i = 0; i < len; i++) {
    if (&arr[i] == p1 || &arr[i] == p2)
      printf("[%d]\t", arr[i]);
    else
      printf("%d\t", arr[i]);
  }
  printf("\n");
}

int* copy_arr(const int* const src_arr, const unsigned len) {
  int* copy = calloc(sizeof(int), len);
  memcpy(copy, src_arr, sizeof(int) * len);
  return copy;
}

int* bubble_sorted(const int* const src_arr, const unsigned len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
      println_array_with_pointers(arr, len, &arr[j], &arr[j + 1]);
    }
  }

  println_array(arr, len);

  return arr;
}

int* selection_sorted(const int* const src_arr, unsigned len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  for (int i = 0; i < len - 1; i++) {
    unsigned min_index = i;
    for (int j = i + 1; j < len; j++) {
      if (arr[j] < arr[min_index])
        min_index = j;
    }
    swap(&arr[i], &arr[min_index]);
    println_array_with_pointers(arr, len, &arr[i], &arr[min_index]);
  }

  println_array(arr, len);
  return arr;
}

int* shaker_sorted(const int* const src_arr, unsigned len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  for (int i = 0; i < len / 2; i++) {
    bool is_swapped = false;
    for (int j = i; j < len - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        is_swapped = true;
      }
      println_array_with_pointers(arr, len, &arr[j], &arr[j + 1]);
    }

    for (int j = len - i - 2; j > i; j--) {
      if (arr[j] < arr[j - 1]) {
        swap(&arr[j], &arr[j - 1]);
        is_swapped = true;
      }
      println_array_with_pointers(arr, len, &arr[j], &arr[j - 1]);
    }

    if (!is_swapped)
      break;
  }

  println_array(arr, len);
  return arr;
}

void quick_sort(int* arr, unsigned len) {}

int* quick_sorted(const int* const src_arr, unsigned len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  println_array(arr, len);
  return arr;
}

int main() {
  const int len = 10;
  const int arr[10] = {6, 40, 3, 9, 6, 10, 0, -80, 100, 90};

  // bubble_sorted(arr, len);
  // selection_sorted(arr, len);
  shaker_sorted(arr, len);
}
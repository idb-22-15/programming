#include <malloc.h>
#include <stdio.h>
#include <string.h>

void swap(int* first, int* second) {
  int tmp = *first;
  *first = *second;
  *second = tmp;
}

void println_array(const int arr[], size_t len) {
  for (int i = 0; i < len; i++) {
    printf("%d\t", arr[i]);
  }
  printf("\n");
}

void println_array_with_pointers(const int arr[],
                                 size_t len,
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

int* copy_arr(const int src_arr[], size_t len) {
  int* copy = (int*)calloc(len, sizeof(int));
  memcpy(copy, src_arr, sizeof(int) * len);
  return copy;
}

bool is_sorted(int arr[], size_t len) {
  bool is_sorted = true;
  for (int i = 0; i < len - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      is_sorted = false;
      break;
    }
  }
  return is_sorted;
}
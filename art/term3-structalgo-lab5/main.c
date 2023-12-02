#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* first, int* second) {
  int tmp = *first;
  *first = *second;
  *second = tmp;
}

void println_array(const int arr[], unsigned len) {
  for (int i = 0; i < len; i++) {
    printf("%d\t", arr[i]);
  }
  printf("\n");
}

void println_array_with_pointers(const int arr[],
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

int* copy_arr(const int src_arr[], unsigned len) {
  int* copy = calloc(sizeof(int), len);
  memcpy(copy, src_arr, sizeof(int) * len);
  return copy;
}

bool is_sorted(int arr[], unsigned len) {
  bool is_sorted = true;
  for (int i = 0; i < len - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      is_sorted = false;
      break;
    }
  }
  return is_sorted;
}

int* selection_sorted(const int src_arr[], unsigned len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  for (int i = 0; i < len - 1; i++) {
    unsigned min_index = i;
    for (int j = i + 1; j < len; j++) {
      if (arr[j] < arr[min_index])
        min_index = j;
    }
    println_array_with_pointers(arr, len, &arr[i], &arr[min_index]);
    swap(&arr[i], &arr[min_index]);
  }

  println_array(arr, len);
  return arr;
}

int* insertion_sorted(const int src_arr[], unsigned len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  for (int i = 0; i < len - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      unsigned index = i;
      while (index >= 0 && arr[index] > arr[index + 1]) {
        println_array_with_pointers(arr, len, &arr[index], &arr[index + 1]);
        swap(&arr[index], &arr[index + 1]);
        if (index == 0)
          break;
        index--;
      }
    }
  }

  println_array(arr, len);
  return arr;
}

int* bubble_sorted(const int src_arr[], const unsigned len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - i - 1; j++) {
      println_array_with_pointers(arr, len, &arr[j], &arr[j + 1]);
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }

  println_array(arr, len);

  return arr;
}

int* shaker_sorted(const int src_arr[], unsigned len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  for (int i = 0; i < len / 2; i++) {
    bool is_swapped = false;
    for (int j = i; j < len - i - 1; j++) {
      println_array_with_pointers(arr, len, &arr[j], &arr[j + 1]);
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        is_swapped = true;
      }
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

int partititate_array(int arr[], unsigned len, unsigned low, unsigned high) {
  unsigned pivot_index = high;
  int pivot_value = arr[pivot_index];

  unsigned new_pivot_index = low;
  for (int i = low; i <= high; i++) {
    println_array_with_pointers(arr, len, &arr[low], &arr[i]);
    if (arr[i] < pivot_value) {
      swap(&arr[low], &arr[i]);
      new_pivot_index++;
    }
  }
  println_array_with_pointers(arr, len, &arr[new_pivot_index], &arr[high]);
  swap(&arr[new_pivot_index], &arr[high]);
  return new_pivot_index;
}

void quick_sort(int arr[], unsigned len, unsigned low, unsigned high) {
  if (low < high) {
    unsigned pivot_index = partititate_array(arr, len, low, high);
    quick_sort(arr, len, low, pivot_index - 1);
    quick_sort(arr, len, pivot_index + 1, high);
  }
}

int* quick_sorted(const int src_arr[], unsigned len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  quick_sort(arr, len, 0, len - 1);

  println_array(arr, len);
  return arr;
}

void merge_sort(int arr[]) {}

void merge(int arr[], unsigned left, unsigned middle, unsigned right) {}

int* merge_sorted(const int src_arr[], unsigned len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  println_array(arr, len);
  return arr;
}

int main() {
  const int len = 10;
  const int arr[10] = {6, 40, 3, 9, 6, 10, 0, -80, 100, 90};

  // selection_sorted(arr, len);
  // insertion_sorted(arr, len);
  // bubble_sorted(arr, len);

  // shaker_sorted(arr, len);

  // quick_sorted(arr, len);
}
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
  int* copy = calloc(sizeof(int), len);
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

int* selection_sorted(const int src_arr[], size_t len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  for (int i = 0; i < len - 1; i++) {
    size_t min_index = i;
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

int* insertion_sorted(const int src_arr[], size_t len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  for (int i = 0; i < len - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      size_t index = i;
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

int* bubble_sorted(const int src_arr[], const size_t len) {
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

int* shaker_sorted(const int src_arr[], size_t len) {
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

int partititate_array(int arr[], size_t len, size_t low, size_t high) {
  size_t pivot_index = high;
  int pivot_value = arr[pivot_index];

  size_t new_pivot_index = low;
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

void quick_sort(int arr[], size_t len, size_t low, size_t high) {
  if (low < high) {
    size_t pivot_index = partititate_array(arr, len, low, high);
    quick_sort(arr, len, low, pivot_index - 1);
    quick_sort(arr, len, pivot_index + 1, high);
  }
}

int* quick_sorted(const int src_arr[], size_t len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);

  quick_sort(arr, len, 0, len - 1);

  println_array(arr, len);
  return arr;
}

void merge(int arr[], size_t left, size_t mid, size_t right) {
  int left_arr_count_elements = mid - left + 1;
  int right_arr_count_elements = right - mid;

  int* left_arr = calloc(left_arr_count_elements, sizeof(int));
  int* right_arr = calloc(right_arr_count_elements, sizeof(int));

  for (size_t i = 0; i < left_arr_count_elements; i++)
    left_arr[i] = arr[left + i];
  for (size_t i = 0; i < right_arr_count_elements; i++)
    right_arr[i] = arr[mid + 1 + i];

  size_t left_arr_index = 0;
  size_t right_arr_index = 0;
  size_t merged_arr_index = left;

  // Merge the temp arrays back into array[left..right]
  while (left_arr_index < left_arr_count_elements &&
         right_arr_index < right_arr_count_elements) {
    if (left_arr[left_arr_index] <= right_arr[right_arr_index]) {
      arr[merged_arr_index] = left_arr[left_arr_index];
      left_arr_index++;
    } else {
      arr[merged_arr_index] = right_arr[right_arr_index];
      right_arr_index++;
    }
    merged_arr_index++;
  }

  for (; left_arr_index < left_arr_count_elements;
       left_arr_index++, merged_arr_index++) {
    arr[merged_arr_index] = left_arr[left_arr_index];
  }

  for (; right_arr_index < right_arr_count_elements;
       right_arr_index++, merged_arr_index++) {
    arr[merged_arr_index] = right_arr[right_arr_index];
  }

  free(left_arr);
  free(right_arr);
}

void merge_sort(int array[], int start, int end) {
  if (start >= end)
    return;

  int mid = start + (end - start) / 2;
  merge_sort(array, start, mid);
  merge_sort(array, mid + 1, end);
  merge(array, start, mid, end);
}

int* merge_sorted(const int src_arr[], size_t len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);
  merge_sort(arr, 0, len);
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

  // merge_sorted(arr, len);
}
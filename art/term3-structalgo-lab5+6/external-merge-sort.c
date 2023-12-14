#include <malloc.h>
#include <stdbool.h>
#include "utils.c"

void merge(int arr[], size_t left, size_t mid, size_t right) {
  int left_arr_count_elements = mid - left + 1;
  int right_arr_count_elements = right - mid;

  int* left_arr = (int*)calloc(left_arr_count_elements, sizeof(int));
  int* right_arr = (int*)calloc(right_arr_count_elements, sizeof(int));

  for (size_t i = 0; i < left_arr_count_elements; i++)
    left_arr[i] = arr[left + i];
  for (size_t i = 0; i < right_arr_count_elements; i++)
    right_arr[i] = arr[mid + 1 + i];

  size_t left_arr_index = 0;
  size_t right_arr_index = 0;
  size_t merged_arr_index = left;

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

  while (left_arr_index < left_arr_count_elements) {
    arr[merged_arr_index] = left_arr[left_arr_index];
    left_arr_index++;
    merged_arr_index++;
  }

  while (right_arr_index < right_arr_count_elements) {
    arr[merged_arr_index] = right_arr[right_arr_index];
    right_arr_index++;
    merged_arr_index++;
  }

  free(left_arr);
  free(right_arr);
}

void merge_sort(int array[], size_t start, size_t end, size_t len) {
  if (start >= end)
    return;

  int mid = start + (end - start) / 2;
  merge_sort(array, start, mid, len);
  merge_sort(array, mid + 1, end, len);
  merge(array, start, mid, end);
  println_array(&array[start], end - start);
}

int* merge_sorted(const int src_arr[], size_t len) {
  int* arr = copy_arr(src_arr, len);
  println_array(arr, len);
  merge_sort(arr, 0, len - 1, len);
  println_array(arr, len);
  return arr;
}

void merge_files(FILE* file1, FILE* file2, FILE* output) {
  rewind(file1);
  rewind(file2);

  int num1, num2;
  fscanf(file1, "%d", &num1);
  fscanf(file2, "%d", &num2);

  while (!feof(file1) && !feof(file2)) {
    if (num1 <= num2) {
      fprintf(output, "%d ", num1);
      fscanf(file1, "%d", &num1);
    } else {
      fprintf(output, "%d ", num2);
      fscanf(file2, "%d", &num2);
    }
  }

  while (!feof(file1)) {
    fprintf(output, "%d ", num1);
    fscanf(file1, "%d", &num1);
  }

  while (!feof(file2)) {
    fprintf(output, "%d ", num2);
    fscanf(file2, "%d", &num2);
  }
}

void external_merge_sort(FILE* input, FILE* output) {
  size_t first_arr_size = 0;
  size_t second_arr_size = 0;

  int* first_arr = (int*)malloc(sizeof(int) * first_arr_size);
  int* second_arr = (int*)malloc(sizeof(int) * second_arr_size);

  int num;
  size_t count = 0;
  while (fscanf(input, "%d", &num) == 1) {
    count++;
    if (count % 2 == 1) {
      first_arr_size++;
      first_arr = (int*)realloc(first_arr, sizeof(int) * first_arr_size);
      first_arr[first_arr_size - 1] = num;
    } else {
      second_arr_size++;
      second_arr = (int*)realloc(second_arr, sizeof(int) * second_arr_size);
      second_arr[second_arr_size - 1] = num;
    }
  }
  merge_sort(first_arr, 0, first_arr_size - 1, first_arr_size);
  merge_sort(second_arr, 0, second_arr_size - 1, second_arr_size);

  const char* temp_filename1 = "temp1.txt";
  const char* temp_filename2 = "temp2.txt";
  FILE* temp1 = fopen(temp_filename1, "w");
  FILE* temp2 = fopen(temp_filename2, "w");

  for (int i = 0; i < first_arr_size; i++)
    fprintf(temp1, "%d ", first_arr[i]);
  for (int i = 0; i < second_arr_size; i++)
    fprintf(temp2, "%d ", second_arr[i]);

  fclose(temp1);
  fclose(temp2);

  temp1 = fopen(temp_filename1, "r");
  temp2 = fopen(temp_filename2, "r");
  merge_files(temp1, temp2, output);

  fclose(temp1);
  fclose(temp2);
  // remove(temp_filename1);
  // remove(temp_filename2);
  free(first_arr);
  free(second_arr);
}

void lab6() {
  const char* input_filename = "input.txt";
  const char* output_filename = "output.txt";
  FILE* input = fopen(input_filename, "r");
  FILE* output = fopen(output_filename, "w");
  external_merge_sort(input, output);
  fclose(input);
  fclose(output);

  output = fopen(output_filename, "r");
  int* arr = (int*)malloc(0);
  size_t arr_size = 0;
  int num;
  while (fscanf(output, "%d", &num)) {
    if (feof(output))
      break;
    arr_size++;
    arr = (int*)realloc(arr, sizeof(int) * arr_size);
    arr[arr_size - 1] = num;
  }
  println_array(arr, arr_size);
}

int main() {
  lab6();
}

// A 10 20 40 | 30 50 60 80 | 70

// B 10 20 40 | 70
// C 30 50 60 80

// A 10 20 30 40 50 60 80 | 70

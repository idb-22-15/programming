#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "get_string.h"

void mutate_string(char* string, int length) {
  char* res_string = string;

  bool is_started = false;
  int res_string_index = 0;
  for (int i = 0; i < length; i++) {
    if ((is_started == true && string[i] == ':') || string[i] == '\0') {
      break;
    }
    if (string[i] == ':' && is_started == false) {
      is_started = true;
      continue;
    }

    if (!is_started)
      continue;

    res_string[res_string_index] = string[i];
    res_string_index++;
  }
  res_string[res_string_index] = '\0';
}

void task1() {
  char* string = get_string_by_malloc(stdin);
  printf("%s\n", string);
  mutate_string(string, strlen(string));
  printf("%s\n", string);

  free(string);
  string = NULL;
}

void task2() {
  char* string = get_string_by_realloc(stdin);
  printf("%s\n", string);

  mutate_string(string, strlen(string));
  printf("%s\n", string);

  free(string);
  string = NULL;
}

void write_string_to_file(char* string, const char* filename) {
  FILE* file = fopen(filename, "w");
  if (file == NULL) {
    perror("Error");
    return;
  }

  fputs(string, file);
  fclose(file);
}

void task3() {
  char* string_to_write_in_file = get_string_by_realloc(stdin);
  const char* input_filename = "text.txt";

  write_string_to_file(string_to_write_in_file, input_filename);

  free(string_to_write_in_file);
  string_to_write_in_file = NULL;

  FILE* fileptr = fopen(input_filename, "r");
  char* str = get_string_by_malloc(fileptr);

  mutate_string(str, strlen(str));

  char* output_filename = "out.txt";
  write_string_to_file(str, output_filename);
  printf("%s\n", str);

  free(str);
  str = NULL;
}

int main() {
  // task1();
  // task2();
  task3();
}

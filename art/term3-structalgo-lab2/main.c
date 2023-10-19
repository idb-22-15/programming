#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void handle_error(char* string) {
  if (string == NULL) {
    printf("Error");
    exit(1);
  }
}

char* get_string_by_malloc(FILE* stream) {
  char* string = NULL;
  string = (char*)malloc(sizeof(char));
  handle_error(string);

  char c = 0;
  while ((c = getc(stream)) != '\n') {
    if (c == EOF)
      break;
    char* tmp = NULL;
    tmp = (char*)malloc((strlen(string) + 1) * sizeof(char));
    handle_error(string);

    strcpy(tmp, string);

    string = (char*)malloc((strlen(string) + 1) * sizeof(char));
    handle_error(string);

    strcpy(string, tmp);
    string[strlen(string)] = c;

    free(tmp);
    // printf("%s\n", string);
  }
  // string[strlen(string) - 1] = '\0';
  return string;
}

void task1() {
  char* string = get_string_by_malloc(stdin);
  printf("%s\n", string);
  mutate_string(string, strlen(string));
  printf("%s\n", string);

  free(string);
  string = NULL;
}

char* get_string_by_realloc(FILE* stream) {
  char* string = NULL;

  int len_allocated = 5;
  string = calloc(len_allocated, sizeof(char));
  handle_error(string);

  int c = 0;
  while ((c = getc(stream)) != '\n') {
    if (strlen(string) + 1 > len_allocated) {
      len_allocated += 5;
      string = realloc(string, len_allocated * sizeof(char));
      handle_error(string);
    }

    string[strlen(string)] = c;
  }

  return string;
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

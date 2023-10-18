#include <stdbool.h>
#include <stdio.h>

#define MAX_STRING_LENGTH 100

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

void read_string_by_chars(char* string) {
  char c = 0;
  int string_index = 0;

  while ((c = getchar()) != '\n') {
    string[string_index] = c;
    string_index++;
  }
}

void task1() {
  char string[MAX_STRING_LENGTH] = {0};

  read_string_by_chars(string);
  mutate_string(string, MAX_STRING_LENGTH);

  printf("%s\n", string);
}

void task2() {
  char string[MAX_STRING_LENGTH] = {0};
  fgets(string, MAX_STRING_LENGTH, stdin);

  mutate_string(string, MAX_STRING_LENGTH);
  printf("%s\n", string);
}

void read_string_from_file(char* string, int length, const char* filename) {
  FILE* file = fopen(filename, "r");

  if (file == NULL) {
    printf("Error");
    return;
  }

  fgets(string, length, file);
  fclose(file);
}

void write_string_to_file(char* string, const char* filename) {
  FILE* file = fopen(filename, "w");
  if (file == NULL) {
    printf("Error");
    return;
  }

  fputs(string, file);
  fclose(file);
}

void task3() {
  char string[MAX_STRING_LENGTH] = {0};

  const char* input_filename = "text.txt";
  read_string_from_file(string, MAX_STRING_LENGTH, input_filename);
  mutate_string(string, MAX_STRING_LENGTH);

  const char* output_filename = "out.txt";
  write_string_to_file(string, output_filename);
}

int main() {
  // task1();
  // task2();
  task3();
}

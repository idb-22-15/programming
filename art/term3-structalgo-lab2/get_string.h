#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void handle_error(char* string) {
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
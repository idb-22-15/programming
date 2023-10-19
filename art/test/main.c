#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

char* get_string() {
  char* string = NULL;

  char c;
  int len = 0;
  while ((c = getc(stdin)) != '\n') {
    len++;
    string = (char*)realloc(string, len * sizeof(char));
    if (string == NULL) {
      perror("Memory not available");
      exit(1);
    }
    string[len - 1] = c;
  }

  return string;
}

int main() {
  // char* string = get_string();

  // printf("%s", string);
  // printf("%d", strlen(string));

  // free(string);
  // string = NULL;

  linked_list* list = malloc(sizeof(linked_list));

  list->data = 5;
  list->next = malloc(sizeof(linked_list));

  // free(list->next);
  // free(list);
  printf("%d", linked_list_len(list));
  free_linked_list(list);
}

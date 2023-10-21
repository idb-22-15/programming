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
  list->value = 66;
  list->next = ll_new_node(67);
  ll_push_back(list, 68);
  ll_push_forward(&list, 1);
  ll_insert_after(list, 0, 99);
  int last = ll_pop(list);
  int first = ll_pop_first(&list);

  printf("First %d\n", first);
  printf("Length %d\n", ll_len(list));
  ll_print(list);

  printf("\nLast %d", last);
  int value = ll_pop_index(&list, 0);
  printf("\nValue %d\n", value);
  ll_print(list);
  ll_free(&list);

  int arr[] = {1, 2, 3, 4};
  linked_list* list2 = ll_from_array(arr, 4);
  ll_reverse(&list2);
  printf("\n======\n");
  ll_println(list2);
  ll_free(&list2);

  linked_list* string_list = ll_new_from_stream(stdin);
  linked_list* string_copy = ll_new_copy(string_list);
  ll_reverse(&string_list);

  ll_println_as_string(string_list);
  ll_println_as_string(string_copy);

  ll_slice(&string_copy, 2, 3);
  ll_println_as_string(string_copy);
  printf("%c", ll_get_node_by_index(string_copy, 0)->value);

  ll_free(&string_list);
  ll_free(&string_copy);
}

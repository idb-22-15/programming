#include <stdbool.h>
#include <stdio.h>

#include "double_list.c"
#include "linked_list.c"

// void mutate_string(char* string, int length) {
//   char* res_string = string;

//   bool is_started = false;
//   int res_string_index = 0;
//   for (int i = 0; i < length; i++) {
//     if ((is_started && string[i] == ':') || string[i] == '\0') {
//       break;
//     }
//     if (string[i] == ':' && is_started == false) {
//       is_started = true;
//       continue;
//     }

//     if (!is_started)
//       continue;

//     res_string[res_string_index] = string[i];
//     res_string_index++;
//   }
//   res_string[res_string_index] = '\0';
// }

void mutate_ll(linked_list** p_head) {
  ll_handle_error_p(p_head);

  linked_list* prev_node = NULL;
  linked_list** current_node = p_head;

  linked_list* new_head = *p_head;

  bool is_started = false;
  while ((*current_node) != NULL) {
    if (is_started && (*current_node)->value == ':') {
      if (prev_node != NULL)
        prev_node->next = NULL;
      ll_free(current_node);
      *current_node = NULL;
      break;
    }

    if (!is_started && (*current_node)->value == ':') {
      is_started = true;
      new_head = (*current_node)->next;

      prev_node = (*current_node);
      *current_node = (*current_node)->next;
      free(prev_node);
      prev_node = NULL;
      continue;
    }

    if (!is_started) {
      prev_node = (*current_node);
      *current_node = (*current_node)->next;
      free(prev_node);
      prev_node = NULL;
      continue;
    }

    prev_node = (*current_node);
    (*current_node) = (*current_node)->next;
  }
  *p_head = new_head;
}

void mutate_dl(double_list** p_head) {
  dl_handle_error_p(p_head);

  double_list* prev_node = NULL;
  double_list** current_node = p_head;

  double_list* new_head = *p_head;

  bool is_started = false;
  while ((*current_node) != NULL) {
    if (is_started && (*current_node)->value == ':') {
      if (prev_node != NULL)
        prev_node->next = NULL;
      dl_free(current_node);
      *current_node = NULL;
      break;
    }

    if (!is_started && (*current_node)->value == ':') {
      is_started = true;
      new_head = (*current_node)->next;

      prev_node = (*current_node);
      *current_node = (*current_node)->next;
      free(prev_node);
      prev_node = NULL;
      continue;
    }

    if (!is_started) {
      prev_node = (*current_node);
      *current_node = (*current_node)->next;
      free(prev_node);
      prev_node = NULL;
      continue;
    }

    prev_node = (*current_node);
    (*current_node) = (*current_node)->next;
  }
  *p_head = new_head;
}

void task1_ll() {
  linked_list* list = ll_new_from_stream(stdin);
  printf("from stdin:\t");
  ll_println_as_string(list);

  mutate_ll(&list);
  printf("mutated:\t");
  ll_println_as_string(list);

  ll_free(&list);
}

void task1_dl() {
  double_list* list = dl_new_from_stream(stdin);
  printf("from stdin:\t");
  dl_println_as_string(list);

  mutate_dl(&list);
  printf("mutated:\t");
  dl_println_as_string(list);

  dl_free(&list);
}

void task3_ll() {
  linked_list* list_to_write_in_file = ll_new_from_stream(stdin);
  printf("from stdin:\t");
  ll_println_as_string(list_to_write_in_file);

  const char* input_filename = "tmp/ll-in.txt";
  FILE* input_fileptr = fopen(input_filename, "wr");
  if (input_fileptr == NULL) {
    perror("error: ");
    exit(EXIT_FAILURE);
  }

  ll_write_to_stream(list_to_write_in_file, input_fileptr);

  fclose(input_fileptr);
  ll_free(&list_to_write_in_file);
  list_to_write_in_file = NULL;

  input_fileptr = fopen(input_filename, "r");
  if (input_fileptr == NULL) {
    perror("error: ");
    exit(EXIT_FAILURE);
  }
  linked_list* list_from_file = ll_new_from_stream(input_fileptr);
  fclose(input_fileptr);
  printf("from file:\t");
  ll_println_as_string(list_from_file);

  char* output_filename = "tmp/ll-out.txt";
  FILE* output_fileptr = fopen(output_filename, "w");
  if (output_fileptr == NULL) {
    perror("error: ");
    exit(EXIT_FAILURE);
  }

  mutate_ll(&list_from_file);
  printf("mutated:\t");
  ll_println_as_string(list_from_file);
  ll_write_to_stream(list_from_file, output_fileptr);

  fclose(output_fileptr);
  ll_free(&list_from_file);
  list_from_file = NULL;
}

void task3_dl() {
  double_list* list_to_write_in_file = dl_new_from_stream(stdin);
  printf("from stdin:\t");
  dl_println_as_string(list_to_write_in_file);

  const char* input_filename = "tmp/dl-in.txt";
  FILE* input_fileptr = fopen(input_filename, "wr");
  if (input_fileptr == NULL) {
    perror("error: ");
    exit(EXIT_FAILURE);
  }

  dl_write_to_stream(list_to_write_in_file, input_fileptr);

  fclose(input_fileptr);
  dl_free(&list_to_write_in_file);
  list_to_write_in_file = NULL;

  input_fileptr = fopen(input_filename, "r");
  if (input_fileptr == NULL) {
    perror("error: ");
    exit(EXIT_FAILURE);
  }
  double_list* list_from_file = dl_new_from_stream(input_fileptr);
  fclose(input_fileptr);
  printf("from file:\t");
  dl_println_as_string(list_from_file);

  char* output_filename = "tmp/dl-out.txt";
  FILE* output_fileptr = fopen(output_filename, "w");
  if (output_fileptr == NULL) {
    perror("error: ");
    exit(EXIT_FAILURE);
  }

  mutate_dl(&list_from_file);
  printf("mutated:\t");
  dl_println_as_string(list_from_file);
  dl_write_to_stream(list_from_file, output_fileptr);

  fclose(output_fileptr);
  dl_free(&list_from_file);
  list_from_file = NULL;
}

int main() {
  // task1_ll();
  // task3_ll();
  // task1_dl();
  task3_dl();
}

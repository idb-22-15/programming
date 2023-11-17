#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "double_list.h"
#include "utils.h"

bool dl_is_empty(double_list* head) {
  return head == NULL;
}

static void dl_handle_error(double_list* head) {
  if (dl_is_empty(head)) {
    exit(1);
  }
}

static void dl_handle_error_p(double_list** p_head) {
  if (p_head == NULL || dl_is_empty(*p_head))
    exit(1);
}

double_list* dl_new_node(int value, double_list* prev) {
  double_list* node = malloc(sizeof(double_list));
  if (node == NULL)
    return NULL;

  node->prev = prev;
  node->value = value;
  node->next = NULL;

  return node;
}

double_list* dl_new_copy(double_list* head) {
  if (head == NULL)
    return NULL;

  double_list* copy_head = dl_new_node(head->value, head->prev);
  double_list* current_copy_node = copy_head;

  double_list* current_node = head->next;

  while (current_node != NULL) {
    double_list* copy_node =
        dl_new_node(current_node->value, current_copy_node->prev);
    current_copy_node->next = copy_node;

    current_copy_node = current_copy_node->next;
    current_node = current_node->next;
  }

  return copy_head;
}

double_list* dl_new_from_stream(FILE* stream) {
  char c = fgetc(stream);
  if (is_stream_end(c))
    return NULL;

  double_list* head = dl_new_node(c, NULL);
  double_list* current_node = head;

  while (!is_stream_end((c = fgetc(stream)))) {
    double_list* new_node = dl_new_node(c, current_node);
    current_node->next = new_node;
    current_node = current_node->next;
  }
  return head;
}

double_list* dl_new_from_array(int array[], unsigned array_len) {
  double_list* head = dl_new_node(array[0], NULL);
  double_list* current_node = head;

  for (int i = 1; i < array_len; i++) {
    current_node->next = dl_new_node(array[i], current_node);
    current_node = current_node->next;
  }

  return head;
}

void dl_free(double_list** p_head) {
  dl_handle_error_p(p_head);

  double_list* current_node = *p_head;

  while (current_node != NULL) {
    current_node = current_node->next;
    free(*p_head);
    *p_head = current_node;
  }
}

int dl_len(double_list* head) {
  dl_handle_error(head);

  double_list* current_node = head;
  int len = 0;

  while (current_node != NULL) {
    current_node = current_node->next;
    len++;
  }
  return len;
}

void dl_push_back(double_list* head, int value) {
  dl_handle_error(head);

  double_list* current_node = head;

  while (current_node->next != NULL) {
    current_node = current_node->next;
  };
  current_node->next = dl_new_node(value, current_node);
}

void dl_push_forward(double_list** p_head, int value) {
  dl_handle_error_p(p_head);

  double_list* new_head = dl_new_node(value, NULL);
  new_head->next = *p_head;
  *p_head = new_head;
}

void dl_print(double_list* head) {
  dl_handle_error(head);

  double_list* current_node = head;

  while (current_node != NULL) {
    printf("%d ", current_node->value);
    current_node = current_node->next;
  }
}

void dl_println(double_list* head) {
  dl_print(head);
  printf("\n");
}

void dl_print_as_string(double_list* head) {
  dl_handle_error(head);

  double_list* current_node = head;

  while (current_node != NULL) {
    printf("%c", current_node->value);
    current_node = current_node->next;
  }
}

void dl_println_as_string(double_list* head) {
  dl_print_as_string(head);
  printf("\n");
}

int dl_pop(double_list* head) {
  dl_handle_error(head);

  double_list* prev_node = NULL;
  double_list* current_node = head;

  while (current_node->next != NULL) {
    prev_node = current_node;
    current_node = current_node->next;
  }

  int value = current_node->value;

  prev_node->next = NULL;

  free(current_node);
  current_node = NULL;

  return value;
}

int dl_pop_first(double_list** p_head) {
  dl_handle_error_p(p_head);

  double_list* head = *p_head;
  int value = head->value;
  *p_head = (*p_head)->next;
  (*p_head)->prev = NULL;

  free(head);
  head = NULL;
  return value;
}

int dl_pop_index(double_list** p_head, unsigned index) {
  dl_handle_error_p(p_head);

  if (index == 0)
    return dl_pop_first(p_head);

  double_list* prev_node = NULL;
  double_list* current_node = *p_head;
  unsigned current_index = 0;

  while (current_node != NULL && current_index != index) {
    prev_node = current_node;
    current_node = current_node->next;
    current_index++;
  }

  prev_node->next = current_node->next;
  current_node->next->prev = prev_node;

  int value = current_node->value;
  free(current_node);
  current_node = NULL;

  return value;
}

double_list* dl_get_node_by_index(double_list* head, unsigned index) {
  dl_handle_error(head);

  double_list* current_node = head;
  unsigned current_index = 0;

  while (current_node != NULL && current_index != index) {
    current_node = current_node->next;
    current_index++;
  }

  if (current_index != index)
    return NULL;

  return current_node;
}

void dl_insert_after(double_list* head, unsigned index, int value) {
  dl_handle_error(head);

  double_list* new_node = dl_new_node(value, NULL);
  unsigned current_index = 0;
  double_list* current_node = head;

  while (current_index != index) {
    current_node = current_node->next;
    current_index++;
  }
  new_node->next = current_node->next;
  new_node->prev = current_node;
  current_node->next = new_node;
}

void dl_reverse(double_list** p_head) {
  dl_handle_error_p(p_head);

  double_list* prev_node = NULL;
  double_list* current_node = *p_head;
  double_list* next_node = current_node->next;

  while (next_node != NULL) {
    current_node->next = prev_node;
    prev_node = current_node;
    current_node = next_node;
    next_node = next_node->next;
  }

  current_node->next = prev_node;
  *p_head = current_node;
}

void dl_slice(double_list** p_head, unsigned start_index, unsigned end_index) {
  dl_handle_error_p(p_head);

  if (start_index >= end_index) {
    dl_free(p_head);
    return;
  }

  double_list* current_node = *p_head;
  unsigned current_index = 0;

  while (current_index != start_index && current_node != NULL) {
    double_list* tmp = current_node;
    current_node = current_node->next;
    current_index++;

    free(tmp);
    tmp = NULL;
    current_node->prev = NULL;
  }

  *p_head = current_node;

  // double_list* prev_node = NULL;

  // while (current_index != end_index && current_node != NULL) {
  //   prev_node = current_node;
  //   current_node = current_node->next;
  //   current_index++;
  // }

  if (current_index == end_index && current_node != NULL) {
    current_node->prev->next = NULL;
    dl_free(&current_node);
    // prev_node->next = NULL;
  }
}

void dl_write_to_stream(double_list* head, FILE* stream) {
  double_list* current_node = head;

  while (current_node != NULL) {
    fwrite((void*)&current_node->value, sizeof(current_node->value), 1, stream);
    current_node = current_node->next;
  }
}
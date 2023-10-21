#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_stream_end(char c) {
  return c == '\n' || c == EOF;
}
typedef struct linked_list {
  int value;
  struct linked_list* next;
} linked_list;

bool ll_is_empty(linked_list* head) {
  return head == NULL;
}

static void ll_handle_error(linked_list* head) {
  if (ll_is_empty(head)) {
    exit(1);
  }
}

static void ll_handle_error_p(linked_list** p_head) {
  if (p_head == NULL || ll_is_empty(*p_head))
    exit(1);
}

linked_list* ll_new_node(int value) {
  linked_list* node = (linked_list*)malloc(sizeof(linked_list));
  node->value = value;
  node->next = NULL;

  return node;
}

linked_list* ll_new_copy(linked_list* head) {
  if (head == NULL)
    return NULL;

  linked_list* copy_head = ll_new_node(head->value);
  linked_list* current_copy_node = copy_head;

  linked_list* current_node = head->next;

  while (current_node != NULL) {
    linked_list* copy_node = ll_new_node(current_node->value);
    current_copy_node->next = copy_node;

    current_copy_node = current_copy_node->next;
    current_node = current_node->next;
  }

  return copy_head;
}

linked_list* ll_new_from_stream(FILE* stream) {
  char c = fgetc(stream);
  if (is_stream_end(c))
    return NULL;

  linked_list* head = ll_new_node(c);
  linked_list* current_node = head;

  while (!is_stream_end((c = fgetc(stream)))) {
    linked_list* new_node = ll_new_node(c);
    current_node->next = new_node;
    current_node = current_node->next;
  }
  return head;
}

void ll_free(linked_list** p_head) {
  ll_handle_error_p(p_head);

  linked_list* current_node = *p_head;

  while (current_node != NULL) {
    current_node = current_node->next;
    free(*p_head);
    *p_head = current_node;
  }
}

int ll_len(linked_list* head) {
  ll_handle_error(head);

  linked_list* current_node = head;
  int len = 0;

  while (current_node != NULL) {
    current_node = current_node->next;
    len++;
  }
  return len;
}

void ll_push_back(linked_list* head, int value) {
  ll_handle_error(head);

  linked_list* current_node = head;

  while (current_node->next != NULL) {
    current_node = current_node->next;
  }
  current_node->next = ll_new_node(value);
}

void ll_push_forward(linked_list** p_head, int value) {
  ll_handle_error_p(p_head);

  linked_list* new_head = ll_new_node(value);
  new_head->next = *p_head;
  *p_head = new_head;
}

void ll_print(linked_list* head) {
  ll_handle_error(head);

  linked_list* current_node = head;

  while (current_node != NULL) {
    printf("%d ", current_node->value);
    current_node = current_node->next;
  }
}

void ll_println(linked_list* head) {
  ll_print(head);
  printf("\n");
}

void ll_print_as_string(linked_list* head) {
  ll_handle_error(head);

  linked_list* current_node = head;

  while (current_node != NULL) {
    printf("%c", current_node->value);
    current_node = current_node->next;
  }
}

void ll_println_as_string(linked_list* head) {
  ll_print_as_string(head);
  printf("\n");
}

int ll_pop(linked_list* head) {
  ll_handle_error(head);

  linked_list* prev_node = NULL;
  linked_list* current_node = head;

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

int ll_pop_first(linked_list** p_head) {
  ll_handle_error_p(p_head);

  linked_list* head = *p_head;
  int value = head->value;
  *p_head = (*p_head)->next;

  free(head);
  head = NULL;
  return value;
}

int ll_pop_index(linked_list** p_head, unsigned index) {
  ll_handle_error_p(p_head);

  if (index == 0)
    return ll_pop_first(p_head);

  linked_list* prev_node = NULL;
  linked_list* current_node = *p_head;
  unsigned current_index = 0;

  while (current_node != NULL && current_index != index) {
    prev_node = current_node;
    current_node = current_node->next;
    current_index++;
  }

  prev_node->next = current_node->next;

  int value = current_node->value;
  free(current_node);
  current_node = NULL;

  return value;
}

linked_list* ll_get_node_by_index(linked_list* head, unsigned index) {
  ll_handle_error(head);

  linked_list* current_node = head;
  unsigned current_index = 0;

  while (current_node != NULL && current_index != index) {
    current_node = current_node->next;
    current_index++;
  }

  if (current_index != index)
    return NULL;

  return current_node;
}

void ll_insert_after(linked_list* head, unsigned index, int value) {
  ll_handle_error(head);

  linked_list* new_node = ll_new_node(value);
  int current_index = 0;
  linked_list* current_node = head;

  while (current_index != index) {
    current_node = current_node->next;
    current_index++;
  }
  new_node->next = current_node->next;
  current_node->next = new_node;
}

linked_list* ll_from_array(int array[], unsigned array_len) {
  linked_list* head = ll_new_node(array[0]);
  linked_list* current_node = head;

  for (int i = 1; i < array_len; i++) {
    current_node->next = ll_new_node(array[i]);
    current_node = current_node->next;
  }

  return head;
}

void ll_reverse(linked_list** p_head) {
  ll_handle_error_p(p_head);

  linked_list* prev_node = NULL;
  linked_list* current_node = *p_head;
  linked_list* next_node = current_node->next;

  while (next_node != NULL) {
    current_node->next = prev_node;
    prev_node = current_node;
    current_node = next_node;
    next_node = next_node->next;
  }

  current_node->next = prev_node;
  *p_head = current_node;
}

void ll_slice(linked_list** p_head, unsigned start_index, unsigned end_index) {
  ll_handle_error_p(p_head);

  if (start_index >= end_index) {
    ll_free(p_head);
    return;
  }

  linked_list* current_node = *p_head;
  unsigned current_index = 0;

  while (current_index != start_index && current_node != NULL) {
    linked_list* tmp = current_node;
    current_node = current_node->next;
    current_index++;

    free(tmp);
    tmp = NULL;
  }

  *p_head = current_node;

  linked_list* prev_node = NULL;

  while (current_index != end_index && current_node != NULL) {
    prev_node = current_node;
    current_node = current_node->next;
    current_index++;
  }

  if (current_index == end_index && current_node != NULL) {
    ll_free(&current_node);
    prev_node->next = NULL;
  }
}

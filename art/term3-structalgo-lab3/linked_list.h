#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct linked_list {
  char value;
  struct linked_list* next;
} linked_list;

bool ll_is_empty(linked_list* head);
bool ll_is_end(linked_list* node);

int ll_get_index(linked_list* head, linked_list* node);
int ll_get_node_value(linked_list* node);
void ll_set_node_value(linked_list* node, int value);

static void ll_handle_error(linked_list* head);
static void ll_handle_error_p(linked_list** p_head);

linked_list* ll_new_node(int value);
linked_list* ll_new_copy(linked_list* head);
linked_list* ll_new_from_stream(FILE* stream);
linked_list* ll_new_from_array(int array[], unsigned array_len);

void ll_free(linked_list** p_head);
void ll_make_empty(linked_list** p_head);

int ll_len(linked_list* head);

void ll_push_back(linked_list* head, int value);
void ll_push_forward(linked_list** p_head, int value);

void ll_print(linked_list* head);
void ll_println(linked_list* head);
void ll_print_as_string(linked_list* head);
void ll_println_as_string(linked_list* head);

int ll_pop(linked_list* head);
int ll_pop_first(linked_list** p_head);
int ll_pop_index(linked_list** p_head, unsigned index);

linked_list* ll_get_node_by_index(linked_list* head, unsigned index);

void ll_insert_after(linked_list* head, unsigned index, int value);
void ll_reverse(linked_list** p_head);
void ll_slice(linked_list** p_head, unsigned start_index, unsigned end_index);

void ll_write_to_stream(linked_list* head, FILE* stream);
#endif

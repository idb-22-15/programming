#ifndef __DOUBLE_LIST_H
#define __DOUBLE_LIST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct double_list {
  struct double_list* prev;
  char value;
  struct double_list* next;

} double_list;

bool dl_is_empty(double_list* head);
bool dl_is_start(double_list* node);
bool dl_is_end(double_list* node);

int dl_get_index(double_list* head, double_list* node);
int dl_get_node_value(double_list* node);
void dl_set_node_value(double_list* node, int value);

static void dl_handle_error(double_list* head);
static void dl_handle_error_p(double_list** p_head);

double_list* dl_new_node(int value, double_list* prev);
double_list* dl_new_copy(double_list* head);
double_list* dl_new_from_stream(FILE* stream);
double_list* dl_new_from_array(int array[], unsigned array_len);

void dl_free(double_list** p_head);
void dl_make_empty(double_list** p_head);

int dl_len(double_list* head);

void dl_push_back(double_list* head, int value);
void dl_push_forward(double_list** p_head, int value);

void dl_print(double_list* head);
void dl_println(double_list* head);
void dl_print_as_string(double_list* head);
void dl_println_as_string(double_list* head);

int dl_pop(double_list* head);
int dl_pop_first(double_list** p_head);
int dl_pop_index(double_list** p_head, unsigned index);

double_list* dl_get_node_by_index(double_list* head, unsigned index);

void dl_insert_after(double_list* head, unsigned index, int value);
void dl_reverse(double_list** p_head);
void dl_slice(double_list** p_head, unsigned start_index, unsigned end_index);

void dl_write_to_stream(double_list* head, FILE* stream);
#endif

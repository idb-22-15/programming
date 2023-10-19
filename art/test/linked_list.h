typedef struct linked_list {
  int data;
  struct linked_list* next;
} linked_list;

int linked_list_len(linked_list* list) {
  linked_list* current_node = list;
  int len = 0;

  while (current_node != NULL) {
    current_node = current_node->next;
    len++;
  }
  return len;
}

void free_linked_list(linked_list* list) {
  linked_list* current = list;
  linked_list* next = current->next;

  while (next != NULL) {
    free(current);
    current = next;
    next = next->next;
  }
}

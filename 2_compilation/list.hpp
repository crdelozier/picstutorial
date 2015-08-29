#pragma once

typedef struct int_node{
  struct int_node *_next;
  int _value;
} int_node;

typedef struct int_linked_list{
  int_node *_start;
} int_linked_list;

void int_linked_list_init(int_linked_list *l);
void int_linked_list_insert(int_linked_list *l, int value);
void int_linked_list_print_all(int_linked_list *l);

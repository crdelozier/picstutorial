#include <iostream>

#include "list.hpp"

int_node* new_int_node()
{
  int_node *node = new int_node;
  node->_next = nullptr;
  node->_value = 0;
  return node;
}

void int_linked_list_init(int_linked_list *l)
{
  l->_start = nullptr;
}

void int_linked_list_insert(int_linked_list *l, int value)
{
  if(l->_start == nullptr){
    l->_start = new_int_node();
    l->_start->_value = value;
    return;
  }

  int_node *current = l->_start;
  while(current->_next != nullptr){
    current = current->_next;
  }

  current->_next = new_int_node();
  current->_next->_value = value;
}

void int_linked_list_print_all(int_linked_list *l)
{
  int_node *current = l->_start;
  while(current != nullptr){
    std::cout << current->_value << "\n";
    current = current->_next;
  }
}

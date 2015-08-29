#include "list.hpp"

int main(){
  int_linked_list *l = new int_linked_list;
  int_linked_list_init(l);

  int_linked_list_insert(l,5);
  int_linked_list_insert(l,2);
  int_linked_list_insert(l,33);

  int_linked_list_print_all(l);
  
  return 0;
}

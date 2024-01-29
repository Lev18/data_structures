#include "AVL_tree.hpp"
#include <iostream>

int main() {
  
  AVL<int>  root;
  root.insert(20);
  root.insert(25);
  root.insert(9);
  root.insert(12);
  root.insert(27);
  root.insert(6);
  root.insert(14);
  root.insert(4);
  root.insert(10);
  // root.delete_node(10);

  //root.print();
  std::cout << std::endl;
  // root.get_successor(14);

  return 0;
}

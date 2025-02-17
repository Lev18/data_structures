#include "AVL_tree.hpp"
#include <iostream>

int main() {
AVL<int>  root;

#ifdef DEL_TEST
    std::vector arr_vals {171, 285, 210, 190, 155, 118, 108, 131, 141, 128, 122, 195};   
    for (const auto& it : arr_vals) {
        root.insert(it);
    }
#endif

    std::cout << "Tree before deletion" << '\n'; 
    root.print();
    for (const auto& it : arr_vals) {
        root.delete_elem(it);
    }

    std::cout << "Tree after deletion" << '\n'; 
  //root.print();
  std::cout << std::endl;
  // root.get_successor(14);

  return 0;
}

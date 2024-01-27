#include "AVL_tree.hpp"
#include <iostream>

template <typename T>
void do_print(Node<T>* root, int level) {
  if (root == nullptr) {
    return;
  }
    const int dist = 4;

    do_print<T>(root->left, level + 1);

    for(int i = 0; i < level * dist; ++i) {
      std::cout << " ";
    }
    std::cout << root->value << '\n';

    do_print<T>(root->right, level + 1);
}

int main() {
  
  Node<int>* root = nullptr;
  root = insert(root, 12);
  root = insert(root, 8);
  root = insert(root, 4);
  root = insert(root, 16);
  root = insert(root, 10);
  root = insert(root, 18);
  root = insert(root, 11);
  root = insert(root, 21);
  root = insert(root, 7);

  root = delete_node(root, 10);

  do_print<int>(root, 0);

  return 0;
}

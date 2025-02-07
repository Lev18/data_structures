#include "BST.hpp"

int main() {
    BinSearchTree<int> tree;

#ifdef RAND_INSERT
    // case when doing random insertion
    for (int i = 0; i < 20; ++i) {
        tree.insert_element(rand() % 50);
    }
#endif

#if SEQ_INSERT
    // case when insertion is sequental
     for (int i = 0; i < 15; ++i) {
        tree.insert_element(i);
    }
#endif

    tree.print_tree();
    return 0;
}

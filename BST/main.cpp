#include <vector>

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

#elif DEGEN_TREE1
    std::vector arr_vals {20, 9, 15, 14, 13, 11, 12};   
    for (const auto& it : arr_vals) {
        tree.insert_element(it);
    }

#elif DEGEN_TREE2
    std::vector arr_vals {924, 220, 911, 244, 898, 258, 362, 363, 411};   
    for (const auto& it : arr_vals) {
        tree.insert_element(it);
    }

#elif SUCC_TEST
    std::vector arr_vals {171, 285, 210, 190, 200, 195};   
    for (const auto& it : arr_vals) {
        tree.insert_element(it);
    }
#endif


#ifdef DEBUG
    //std::cout << tree.get_min_val() << '\n';
    tree.print_tree();
    int curr_key = 210;
    std::cout << "Successor of curr_ket " << curr_key << " is "<<tree.succ_of_node(curr_key) << '\n';
#endif

    return 0;
}

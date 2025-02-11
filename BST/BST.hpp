#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <cstddef>

template <typename T>
class BinSearchTree {
public:
    BinSearchTree<T>() : m_size{0}, m_root{nullptr} {}
    explicit BinSearchTree<T>(T value) : m_size{1}, m_root(new Node(value)){}
    BinSearchTree<T>(const BinSearchTree<T>& src) = default;
    BinSearchTree<T>(BinSearchTree<T>&& src) = default;
    BinSearchTree<T>& operator=(const BinSearchTree<T>& src) = default;
    BinSearchTree<T>& operator=(BinSearchTree<T>&& src) = default;
    ~BinSearchTree<T>() {
        if (m_root) delete m_root;
    }

public: // function interface   
    // T& at(T key);
    void insert_element(T value);
    void delete_element(T value);
    std::size_t size();
    void print_tree();
    const T& at(T key);

// functions for debuging
#if DEBUG
    T get_min_val();
    T get_max_val();
    T pred_of_node(T key);
    T succ_of_node(T key);
#endif

private:
    std::size_t m_size;
    struct Node {
        Node* left;
        Node* right;
        T key;
        explicit Node(T value) : left{nullptr}, right{nullptr}, key{value} {}
    };
    Node* m_root;

private: // auxilary functions
    void postord_traversal(const Node* node);
    void inorder_traversal(const Node* node, int level);
    Node* do_insertion(Node* root, T value);
    const Node* get_max(const Node* node);
    const Node* get_min(const Node* node);
    const std::size_t get_height() const;
    const Node* get_predecessor(const Node* node);
    const Node* get_successor(const Node* node);
    void inord_print(T value, int level);
    bool bin_search(T key);
    const Node* find(T key);
};

template<typename T>
void BinSearchTree<T>::print_tree() {
    inorder_traversal(m_root, 0);
}

template<typename T>
void BinSearchTree<T>::inord_print(T value, int level) {

    const int dist = 4;
     for (int i = 0; i < dist * level; ++i) {
        std::cout << ' ';
    }
    std::cout << value << '\n';
}

template <typename T>
void BinSearchTree<T>::inorder_traversal(const Node* node, int level) {
    if (node == nullptr)  {
        return;
    }

    BinSearchTree<T>::inorder_traversal(node->left, level + 1);
    inord_print(node->key, level);
    BinSearchTree<T>::inorder_traversal(node->right, level + 1);
}

template <typename T>
typename BinSearchTree<T>::Node* BinSearchTree<T>::do_insertion(BinSearchTree<T>::Node* node, T value) {
      if (node == nullptr) {
        return new BinSearchTree<T>::Node(value);
     }
      else if(node->key > value) {
        node->left = do_insertion(node->left, value);
     }
      else {
        node->right = do_insertion(node->right, value);
     }
  return node;
}

template <typename T>
void BinSearchTree<T>::insert_element(T value) {
    if (m_root == nullptr) {
        m_root = do_insertion(m_root, value);
    }
    else  {
        do_insertion(m_root, value);
    }
}



template <typename T>
const typename BinSearchTree<T>::Node* BinSearchTree<T>::get_min(const BinSearchTree<T>::Node* node) {
    const BinSearchTree<T>::Node* ptr = node;
    while (ptr->left != nullptr) {
        ptr = ptr->left;
    }
    return ptr;
}

template <typename T>
const typename BinSearchTree<T>::Node* BinSearchTree<T>::get_max(const BinSearchTree<T>::Node* node) {
    const BinSearchTree<T>::Node* ptr = node;
    while (ptr->right != nullptr) {
        ptr = ptr->right;
    }
    return ptr;
}

#ifdef DEBUG
template <typename T>
T BinSearchTree<T>::get_min_val() {
    const BinSearchTree<T>::Node* pt = BinSearchTree<T>::get_min(m_root);
    return pt->key;
}

template <typename T>
T BinSearchTree<T>::get_max_val() {
    const BinSearchTree<T>::Node* pt = BinSearchTree<T>::get_min(m_root);
    return pt->key;
}

template <typename T>
T BinSearchTree<T>::pred_of_node(T key) {
    return get_predecessor(find(key))->key;
}

template <typename T>
T BinSearchTree<T>::succ_of_node(T key) {
    return get_successor(find(key))->key;
}

#endif

template <typename T>
const typename BinSearchTree<T>::Node* BinSearchTree<T>::get_predecessor(const BinSearchTree<T>::Node* node) {
    if (node == nullptr) return nullptr;

    if (node->left) return get_max(node->left);

    const BinSearchTree<T>::Node* pred = nullptr;
    const BinSearchTree<T>::Node* ancestor = m_root;

    while (ancestor != nullptr) {
        if (ancestor->key < node->key) {
            pred = ancestor;
            ancestor = ancestor->right;
        }
        else {
            ancestor = ancestor->left;
        }
    }
    return pred;
}

template <typename T>
const typename BinSearchTree<T>::Node* BinSearchTree<T>::get_successor(const BinSearchTree<T>::Node* node) {
    /* 
     * get successor is return back the node which is smallest from greater nodes
     * for that, first of all we need to check if right subtree of given node is existing
     * if it is then we return smallest node of that subtree
     * if it is not then we need keep track of decessors and successors, we move successor only in case 
     * when decessor key is greater than given node key
     */
    if (node == nullptr) return nullptr;

    if (node->right) return get_min(node->right);

    const BinSearchTree<T>::Node* succ = nullptr;
    const BinSearchTree<T>::Node* decessor = m_root;

    while (decessor != nullptr) {
        if (decessor->key > node->key) {
            succ = decessor;
            decessor = decessor->left;
        }
        decessor = decessor->right;
    }
    return succ;
}

template <typename T>
const typename BinSearchTree<T>::Node* BinSearchTree<T>::find(T key) {
    BinSearchTree<T>::Node* node  = m_root;
    while (node != nullptr && node->key != key) {
        if (node->key > key) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return node;
}

#endif

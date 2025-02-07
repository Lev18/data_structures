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
    T get();
    void insert_element(T value);
    void delete_element(T value);
    std::size_t size();
    void print_tree();
    const T& at(T key);

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
    Node* get_max(const Node* node);
    Node* get_min(const Node* node);
    const std::size_t get_height() const;
    Node* get_predecessor(const Node* node);
    Node* get_successor(const Node* node);
    void inord_print(T value, int level);
    bool bin_search(T key);

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



#endif

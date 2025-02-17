#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <cstddef>
#include <vector>

#define ITER_INS
enum class NODE_STATUS {
    ACTIVE,
    DEAD
};

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
        /*
        for(auto& iter : all_nodes) {
            if (iter) {
             delete iter;
            }
        }
        */
        delete m_root;
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
        NODE_STATUS m_status;
        explicit Node(T value) : left{nullptr}, right{nullptr}, key{value}, m_status{NODE_STATUS::ACTIVE} {}
    };
    Node* m_root;
    std::vector<Node*> all_nodes;

private: // auxilary functions
    void postord_traversal(const Node* node);
    void inorder_traversal(const Node* node, int level);
    void insert_iter(Node* node, T key);
    Node* do_insertion(Node* root, T value);
    Node* do_deletion(Node* node, T value);
    const Node* get_max(const Node* node);
    Node* get_min(Node* node);
    const std::size_t get_height() const;
    const Node* get_predecessor(const Node* node);
    const Node* get_successor(const Node* node);
    void inord_print(T value, int level);
    bool bin_search(T key);
    Node* find(T key);
};

template<typename T>
void BinSearchTree<T>::print_tree() {
    inorder_traversal(m_root, 0);
}

template <typename T>
void BinSearchTree<T>::insert_element(T value) {
#ifdef REC_INS
    if (m_root == nullptr) {
        m_root = do_insertion(m_root, value);
    }
    else  {
        do_insertion(m_root, value);
    }
#endif
    
#ifdef ITER_INS
    BinSearchTree<T>::Node* new_node = new BinSearchTree<T>::Node(value);
    insert_iter(new_node, value);
#endif
    ++m_size;
}
 
//TODO: delete node from tree
template <typename T>
void BinSearchTree<T>::delete_element(T value) { 
    // BinSearchTree<T>::Node* del_node = this->find(value);
    do_deletion(m_root, value);
}

template <typename T>
typename BinSearchTree<T>::Node* BinSearchTree<T>::do_deletion(BinSearchTree<T>::Node *node, T value) { 
    if (!node) return nullptr;

    if (node->key > value) {
        node->left = do_deletion(node->left, value);
    }
    else if (node->key < value) {
        node->right = do_deletion(node->right, value);
    }
    else {
        if (node->left == nullptr || node->right == nullptr) {
            BinSearchTree<T>::Node* tmp = node->left ? node->left : node->right;
            if (!node->left && node == m_root) {
                m_root = node->right;
            }
            if (!node->right && node == m_root) {
                m_root = node->left;
            }

            delete node;
            return tmp;
        }
        else {
            BinSearchTree<T>::Node* repl_node = get_min(node->right);
            node->key = repl_node->key;      
            node->right = do_deletion(node->right, repl_node->key);
        }
    }
    return node;
}

// belowi are private auxilary functions impementation
template <typename T>
typename BinSearchTree<T>::Node* BinSearchTree<T>::get_min(BinSearchTree<T>::Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    BinSearchTree<T>::Node* ptr = node;
    while (ptr->left != nullptr) {
        ptr = ptr->left;
    }
    return ptr;
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
    if (node->m_status == NODE_STATUS::ACTIVE) {
        inord_print(node->key, level);
    }
    BinSearchTree<T>::inorder_traversal(node->right, level + 1);
}

template <typename T>
typename BinSearchTree<T>::Node* BinSearchTree<T>::do_insertion(BinSearchTree<T>::Node* node, T value) {
      if (node == nullptr) {
        return new BinSearchTree<T>::Node(value);
     }
      else if (node->key > value) {
        node->left = do_insertion(node->left, value);
     }
      else {
        node->right = do_insertion(node->right, value);
     }
  return node;
}

template <typename T>
void BinSearchTree<T>::insert_iter(BinSearchTree<T>::Node* node, T value) {
    BinSearchTree<T>::Node* temp = nullptr;
    BinSearchTree<T>::Node* iter = m_root;
    all_nodes.push_back(node);

    while (iter != nullptr) {
        temp = iter;
        if (iter->key < value) {
            iter = iter->right;
        }
        else if (iter->key > value) {
            iter = iter->left;
        }
    }

    if (m_root == nullptr) {
        m_root = node;
    }
    else if (temp->key < value) {
        temp->right = node;
    }
    else if (temp->key > value) {
        temp->left = node;
    }
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
typename BinSearchTree<T>::Node* BinSearchTree<T>::find(T key) {
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

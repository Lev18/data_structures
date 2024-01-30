#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <queue> 

template <typename T>
class AVL {
private:
  struct Node {
    T value;
    short height;
    Node* left;
    Node* right;
    explicit Node(T val) : value{val}, height{1}, left{nullptr}, right{nullptr}{}
  };

  Node* m_root;
  int m_size;

private:

  int max(int a, int b) {
    return a > b ? a : b;
  }

  int height(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    return node->height;
  }

  int get_balance(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    return height(node->left) - height(node->right); 
  }

  Node* left_rotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
  
    return y;
  }

  Node* right_rotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return x;
  }

  Node* do_balancing(Node** node, T key, int balance) {

    if (balance > 1) {
      if ((*node)->left->value > key) {
        return right_rotate(*node);
      }
      else {
        (*node)->left = left_rotate((*node)->left);
        return right_rotate(*node);
      }
    }
    
    if (balance < -1) {
      if ((*node)->right->value < key) {
        return left_rotate(*node);
      }
      else {
        (*node)->right = right_rotate((*node)->right);
        return left_rotate(*node);
      }
    }
    return *node;
  }

  Node* do_insert(Node* node, T key) {
    if (node == nullptr) {
      return new Node(key);
    }
    
    if (node->value > key) {
      node->left = do_insert(node->left, key);
    }
    
    else if (node->value < key) {
      node->right = do_insert(node->right, key);
    }
    
    else {
      return node;
    }
    
    node->height = 1 + max(height(node->left),height(node->right));
    //++m_size;
    
    int balance = get_balance(node);

    return do_balancing(&node,key,balance);
  }


  Node* min_value(Node* root) {
    if (root == nullptr) {
      return nullptr;
    }

    Node* cntr = root;

    while(cntr->left != nullptr) {
      cntr = cntr->left;
    }
    return cntr;
  }

  Node* delete_node(Node* node, T key) {
    if (node == nullptr) {
      return node;
    }

    if (key > node->value) {
      node->right = delete_node(node->right, key);
    }

    else if (key < node->value) {
      node->left = delete_node(node->left, key);
    }

    else {
      if (node->left == nullptr ||
          node->right == nullptr) {
        Node* tmp = node->left ?
          node->left :
          node->right;
        if (tmp == nullptr) {
          tmp = node;
          node = nullptr;
        }
        else { 
          *node = *tmp;
        }
        delete tmp;
      }

      else {
        Node* tmp = min_value(node->right);

        node->value = tmp->value;

        node->right = delete_node(node->right, tmp->value);
      }
    }

    if (node == nullptr) {
      return node;
    }

    node->height = 1 + max(height(node->left),height(node->right));

    int balance = get_balance(node);

    if (balance > 1) {
      if (get_balance(node->left) >= 0) {
        return right_rotate(node);
      }
      else if(get_balance(node->left) < 0) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
      }
    }
    if (balance < -1) {
      if (get_balance(node->right) >= 0) {
        return left_rotate(node);
      }
      else if (get_balance(node->right) < 0) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
      }
    }
    return node;
    }

    void do_inorder_print(Node* root, int level) {
      if (root == nullptr) {
        return;
      }

      const int dist = 4;
      do_inorder_print(root->left, level + 1);
      for (int i = 0; i < dist * level; ++i) {
        std::cout << " ";
      }
      std::cout << root->value << std::endl;
      do_inorder_print(root->right, level + 1);
    }

    template <typename F>
    void do_post_order(F fun, Node* node) {
      if (node == nullptr) {
        return;
      }
      do_post_order(node->left);
      do_post_order(node->right);
      fun(node->value);
    }

    void do_level_order(Node* root) {
      if (root == nullptr) {
        return;
      }
      std::queue<Node*> q;
      q.push(root);

      Node* current_node = nullptr;
      while (!q.empty()) {
        current_node = q.front();
        q.pop();

        if (current_node->left != nullptr) {
          q.push(current_node->left);
        }
        if (current_node->right != nullptr) {
          q.push(current_node->right);
        }
      }
    }

    Node* get_node(Node* root, const T& value) {
      if (root == nullptr) {
        return root;
      }

      Node* ctr = root;

      while (ctr && ctr->value != value) {
        if (ctr->value > value) {
          ctr = ctr->left;
        }
        else {
          ctr = ctr->right; 
        }
      }
      return ctr;
    }

    Node* get_successor(Node* root, const T& value) {
      if (root == nullptr) {
        return root;
      }

      Node* node = get_node(root, value);

      if (!node) {
        return node;
      }

      if (node->right) {
        return min_value(node->right);
      }

      Node* successor = nullptr;
      while (root && root->value != value) {
        if (root->value < value) {
          root = root->right;
        }
        else {
          successor = root;
          root = root->left;
        }
      }
      return root ? root : successor;
    }

public:
  AVL<T>() : m_root( nullptr), m_size(0) {}
  explicit AVL<T>(const T& value) : m_root(new Node(value)), m_size{1} {}
  AVL<T>(const AVL<T>& oth) {}
  AVL<T>(AVL<T>&& src){}
  AVL<T>& operator=(const AVL<T>& rhs) {}
  AVL<T>& operator=(AVL<T>&& src){}  
  
  void insert(T value) {
    m_root = do_insert(m_root, value);
    ++m_size;
  }

  void print() {
    do_inorder_print(m_root, 0);
    // std::cout << m_size << std::endl;
    std::cout << get_successor(m_root, 30)->value << std::endl;
  }

  template<typename F>
  void post_order(F fun) {
    do_post_order(fun, m_root);
  }

  std::size_t size() {
    return m_size;
  }

};
#endif

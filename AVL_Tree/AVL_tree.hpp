#ifndef AVL_TREE_H
#define AVL_TREE_H

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
  Node* root;
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

    
public:
  AVL<T>() : root( nullptr){}
  explicit AVL<T>(const T& value) : root(new Node(value)) {}
  
  void insert(T value) {
    root = do_insert(root, value);
  }

  void print() {
    do_print(root, 0);
  }
};
#endif

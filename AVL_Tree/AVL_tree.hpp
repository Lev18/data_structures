#ifndef AVL_TREE_H
#define AVL_TREE_H

template <typename T>
struct Node {
  T value;
  short height;
  Node* left;
  Node* right;
  explicit Node<T>(T val) : value{val}, height{1}, left{nullptr}, right{nullptr}{}
};

template <typename T>
int max(int a, int b) {
  return a > b ? a : b;
}

template<typename T>
int height(Node<T>* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

template <typename T>
int get_balance(Node<T>* node) {
  if (node == nullptr) {
    return 0;
  }
  return height(node->left) - height(node->right); 
}

template <typename T> 
Node<T>* left_rotate(Node<T>* x) {
  Node<T>* y = x->right;
  Node<T>* T2 = y->left;
  
  y->left = x;
  x->right = T2;
  
  x->height = max<T>(height(x->left), height(x->right)) + 1;
  y->height = max<T>(height(y->left), height(y->right)) + 1;
 
  return y;
}

template <typename T>
Node<T>* right_rotate(Node<T>* y) {
  Node<T>* x = y->left;
  Node<T>* T2 = x->right;
  
  x->right = y;
  y->left = T2;
  
  x->height = max<T>(height(x->left), height(x->right)) + 1;
  y->height = max<T>(height(y->left), height(y->right)) + 1;
  
  return x;
}

template<typename T> 
Node<T>* do_balancing(Node<T>** node, T key, int balance) {

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

template <typename T>
Node<T>* insert(Node<T>* node, T key) {
  if (node == nullptr) {
    return new Node<T>(key);
  }
  
  if (node->value > key) {
    node->left = insert(node->left, key);
  }
  
  else if (node->value < key) {
    node->right = insert(node->right, key);
  }
  
  else {
    return node;
  }
  
  node->height = 1 + max<T>(height(node->left),height(node->right));
  
  int balance = get_balance(node);

  return do_balancing(&node,key,balance);
}

template <typename T> 
Node<T>* min_value(Node<T>* root) {
  if (root == nullptr) {
    return nullptr;
  }

  Node<T>* cntr = root;

  while(cntr->left != nullptr) {
    cntr = cntr->left;
  }
  return cntr;
}

template <typename T> 
Node<T>* delete_node(Node<T>* node, T key) {
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
      Node<T>* tmp = node->left ?
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
      Node<T>* tmp = min_value(node->right);

      node->value = tmp->value;

      node->right = delete_node(node->right, tmp->value);
    }
  }

  if (node == nullptr) {
    return node;
  }

  node->height = 1 + max<T>(height(node->left),height(node->right));

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

#endif

#include <iostream>
#include <queue>

struct Node {
  Node(int val) : value {val},
                  left {nullptr},
                  right {nullptr} {}
  int value;
  Node* left;
  
  Node* right;
};

struct Heap {
  Heap() : root{nullptr}, size{0}, l{false} {} 
  
  void insert(int val) {
    if (is_empty()) {
      root = new Node(val);
    }
    
    else {
      doinsert(root, val);
    }
    
    ++size;
  }
  
  bool is_empty() const {
    return size == 0;
  }
  
  size_t get_size() const { 
    return size;
  }

  void print_tree() {
    if (root) {
      do_print(root, 0);
    }
  }
private:
  void doinsert(Node* node, int val) {
   std::queue<Node*> queue;
  queue.push(node);

  while (!queue.empty()) {
    Node* current = queue.front();
    queue.pop();

    if (current->left == nullptr) {
      current->left = new Node(val);
      break;
    } else if (current->right == nullptr) {
      current->right = new Node(val);
      break;
    } else {
      queue.push(current->left);
      queue.push(current->right);
    }
  }
  }

  void do_print(Node* node, int depth) {
    if (node == nullptr) {
      return;
    } 
    const int sp = 4;

    do_print(node->right, depth + 1);
    for (int i = 0; i < sp *depth; ++i) {
      std::cout << " ";
    }
    std::cout << node->value << '\n';

    do_print(node->left, depth + 1);
  }

  Node* root;
  size_t size;
  bool l;
  bool r;
};

int main() {
  Heap h;
  h.insert(12);
  h.insert(13);
  h.insert(14);
  h.insert(15);
  h.insert(16);
  h.insert(17);
  h.insert(18);
  h.insert(19);
  h.insert(20);
  h.insert(21);
  h.insert(22);
  h.insert(23);
  h.insert(24); 
  h.insert(25);
  h.insert(26);
  h.print_tree();
  return 0;
}

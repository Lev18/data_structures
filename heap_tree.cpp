#include <iostream>
#include <vector>

struct Node {
  explicit Node(int val) : value {val},
                  left {nullptr},
                  right {nullptr} {}
  int value;
  Node* left; 
  Node* right;
};

struct Heap {
  Heap() : root{nullptr}, size{0}, l{false} {} 

   void insert(int val) {
    heap.push_back(new Node(val));
    if (is_empty()) {
      root = new Node(val);
    }
    
    else {
      int i = heap.size() - 1;
      while (i != 0 && heap[parent(i)] > heap[i]) {
        std::swap(heap[parent(i)], heap[i]);
        i = parent(i);
      }

      for (int in = heap.size() / 2 - 1; i >= 0; --i ) {
             doinsert(root, i);
        }
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
      do_print(0, 0);
    }
   
  }

private:
  int parent(int i) {
    return (i - 1) / 2;
  }

  int left_child(int i) const {
    return 2 * i + 1; 
  }

  int right_child(int i) const {
    return 2 * i + 2;
  }

  void doinsert(Node* node, int index) {
    if (heap[index]->left == nullptr) {
      heap[index]->left = heap[left_child(index)];
      return;
    }
    else if (heap[index]->right == nullptr) {
      heap[index]->right = heap[right_child(index)];
      return;
    }

  }

  void do_print(int index, int depth) {
   if (index >= heap.size()) {
      return;
    } 
    const int sp = 4;

    do_print(right_child(index), depth + 1);
    for (int i = 0; i < sp *depth; ++i) {
      std::cout << " ";
    }
    std::cout << heap[index]->value << '\n';

    do_print(left_child(index), depth + 1);
  }

  std::vector<Node*> heap;
  Node* root;
  size_t size;
  bool l;
  bool r;
};

int main() {
  Heap h;
  h.insert(8);
  h.insert(13);
  h.insert(14);
  h.insert(12);
  h.insert(16);
  h.insert(11);
  h.insert(18);
  h.insert(19);
  h.insert(10);
  h.insert(21);
  h.insert(22);
  h.insert(2);
  h.insert(4); 
  h.insert(9);
  h.insert(26);
  h.print_tree();
  return 0;
}

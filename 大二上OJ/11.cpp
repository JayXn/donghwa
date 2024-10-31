#include <iostream>
#include <string>

using namespace std;

template <class T>
class BinarySearchTree {
 private:
  struct Node {
    T data;
    Node *left, *right;
  };
  void inorder(Node* cur) {
    if (!cur)
      return;
    inorder(cur->left);
    cout << cur->data << " ";
    inorder(cur->right);
  }
  Node* root;

 public:
  BinarySearchTree() : root(nullptr) {}
  void insertElement(T d) {
    if (!root) {
      root = new Node();
      root->data = d;
    }

    Node* cur = root;
    while (true) {
      if (d == cur->data)
        break;

      if (d < cur->data) {
        if (!cur->left) {
          cur->left = new Node();
          cur->left->data = d;
          break;
        }
        cur = cur->left;
      } else {
        if (!cur->right) {
          cur->right = new Node();
          cur->right->data = d;
          break;
        }
        cur = cur->right;
      }
    }
  }
  void print() {
    inorder(root);
    cout << endl;
  }
  bool search(T d) {
    if (!root) {
      return false;
    }

    Node* cur = root;
    while (true) {
      if (d == cur->data)
        return true;

      if (d < cur->data) {
        if (!cur->left) {
          return false;
        }
        cur = cur->left;
      } else {
        if (!cur->right) {
          return false;
        }
        cur = cur->right;
      }
    }
  }
  int height() { return height(root); }
  int height(Node* node) {
    if (!node)
      return 0;

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    return 1 + max(leftHeight, rightHeight);
  }
};

int main() {
  int data;
  string command;
  BinarySearchTree<int>* bst = new BinarySearchTree<int>();
  while (true) {
    cin >> command;
    if (command == "insert") {
      cin >> data;
      bst->insertElement(data);
    } else if (command == "search") {
      cin >> data;
      if (bst->search(data))
        cout << "true" << endl;
      else
        cout << "false" << endl;
    } else if (command == "height") {
      cout << bst->height() << endl;
    } else if (command == "print") {
      bst->print();
    } else if (command == "exit") {
      break;
    }
  }
}

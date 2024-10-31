#include <cmath>
#include <iostream>
#include <queue>

using namespace std;

// 對於節點i 左節點為2i+1 右節點為2i+2
// 對於節點i 父節點為(i-1)/2
// 假設層數為k 有2^k-1個節點

template <class T>
class BinaryTreeInArray {
 private:
  T* array;
  int height;
  int numOfElement;

  void resize(int size) {
    T* temp = new T[numOfElement];
    int j;
    for (j = 0; j < numOfElement; j++)
      temp[j] = array[j];
    delete[] array;
    array = new T[static_cast<int>(pow(2, height + 1)) - 1];
    for (j = 0; j < numOfElement; j++)
      array[j] = temp[j];
    height++;
    delete[] temp;
  }

 public:
  BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0) {
    array = new T[1];
  }

  void addElementAsCompleteTree(T data) {
    int cap = pow(2, height) - 1;
    if (numOfElement + 1 > cap)
      resize((cap + 1) * 2 - 1);
    array[numOfElement] = data;
    numOfElement++;
  }

  void displayInorder(int index = 0) {
    if (index >= numOfElement)
      return;
    displayInorder(2 * index + 1);  // 左子樹
    cout << array[index] << " ";    // 根節點
    displayInorder(2 * index + 2);  // 右子樹
  }

  void displayPreorder(int index = 0) {
    if (index >= numOfElement)
      return;
    cout << array[index] << " ";     // 根節點
    displayPreorder(2 * index + 1);  // 左子樹
    displayPreorder(2 * index + 2);  // 右子樹
  }

  void displayPostorder(int index = 0) {
    if (index >= numOfElement)
      return;
    displayPostorder(2 * index + 1);  // 左子樹
    displayPostorder(2 * index + 2);  // 右子樹
    cout << array[index] << " ";      // 根節點
  }
};

template <class T>
class BinaryTreeInLinkedList {
 private:
  class TreeNode {
   public:
    TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}
    TreeNode *left, *right;
    T data;
  };

  TreeNode* root;
  int numOfElement;

 public:
  BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}

  void addElementAsCompleteTree(T data) {
    TreeNode* newNode = new TreeNode(data);
    if (root == nullptr) {
      root = newNode;  // 根節點
    } else {
      queue<TreeNode*> q;
      q.push(root);
      while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        if (current->left == nullptr) {
          current->left = newNode;  // 插入左子節點
          break;
        } else {
          q.push(current->left);
        }
        if (current->right == nullptr) {
          current->right = newNode;  // 插入右子節點
          break;
        } else {
          q.push(current->right);
        }
      }
    }
    numOfElement++;
  }

  void displayInorder(TreeNode* node = nullptr) {
    if (node == nullptr)
      node = root;  // 從根節點開始
    if (node->left != nullptr)
      displayInorder(node->left);  // 左子樹
    cout << node->data << " ";     // 根節點
    if (node->right != nullptr)
      displayInorder(node->right);  // 右子樹
  }

  void displayPreorder(TreeNode* node = nullptr) {
    if (node == nullptr)
      node = root;              // 從根節點開始
    cout << node->data << " ";  // 根節點
    if (node->left != nullptr)
      displayPreorder(node->left);  // 左子樹
    if (node->right != nullptr)
      displayPreorder(node->right);  // 右子樹
  }

  void displayPostorder(TreeNode* node = nullptr) {
    if (node == nullptr)
      node = root;  // 從根節點開始
    if (node->left != nullptr)
      displayPostorder(node->left);  // 左子樹
    if (node->right != nullptr)
      displayPostorder(node->right);  // 右子樹
    cout << node->data << " ";        // 根節點
  }
};

int main() {
  BinaryTreeInArray<int>* b = new BinaryTreeInArray<int>;
  BinaryTreeInLinkedList<int>* tree = new BinaryTreeInLinkedList<int>;
  int j, n;
  cin >> n;
  for (j = 0; j < n; j++) {
    b->addElementAsCompleteTree(j);
    tree->addElementAsCompleteTree(j);
  }
  b->displayInorder();
  cout << endl;
  tree->displayInorder();
  cout << endl;
  b->displayPreorder();
  cout << endl;
  tree->displayPreorder();
  cout << endl;
  b->displayPostorder();
  cout << endl;
  tree->displayPostorder();
  cout << endl;
  return 0;
}

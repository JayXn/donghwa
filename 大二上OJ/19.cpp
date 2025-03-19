#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

template <class T>
class TreeNode {
 public:
  T* data;
  TreeNode *left, *right;  // 左右指標
  bool isThread;           // 標記右指標是否為Thread（true 表示是Thread）

  // 節點建構函數，初始化資料和指標
  TreeNode(T d) : right(nullptr), left(nullptr), isThread(false) {
    data = new T{d};
  }
  TreeNode() : data(nullptr), right(nullptr), left(nullptr), isThread(false) {}
};

// 線索二元搜尋樹類別
template <class T>
class Tree {
 private:
  TreeNode<T>* root;  // root指標

  // 建立Thread結構：將每個節點的空右指標設為中序遍歷的後繼節點
  void createThread(TreeNode<T>* node, TreeNode<T>*& prev) {
    if (!node || !node->data)
      return;  // 遞迴終止條件，當節點為空或無資料時返回

    // 遞迴處理左子樹
    createThread(node->left, prev);

    // 線索處理：如果前一個節點的右指標為空，將其設為當前節點
    if (prev && prev->right == nullptr) {
      prev->right = node;
      prev->isThread = true;  // 標記為線索
    }

    prev = node;  // 更新前一個節點為當前節點

    // 遞迴處理右子樹（如果右指標不是線索）
    if (!node->isThread)
      createThread(node->right, prev);
  }

 public:
  Tree() : root(nullptr) {}  // 建構函數，初始化根節點為空

  // 插入新節點，維持二元搜尋樹性質
  Tree<T>* insert(T d) {
    if (!root) {  // 如果樹為空，直接將新節點設為根節點
      root = new TreeNode<T>(d);
      return this;
    }

    TreeNode<T>* current = root;  // 從根節點開始插入
    while (true) {
      if (*current->data > d) {  // 小的插左
        if (!current->left) {    // 如果左node為空，插入新節點
          current->left = new TreeNode<T>(d);
          return this;
        }
        current = current->left;  // 繼續往左子樹遞迴
      } else {                    // 如果新值大於或等於當前節點的值，往右子樹找
        if (!current->right || current->isThread) {  // 如果右子節點為空或是線索
          current->right = new TreeNode<T>(d);
          return this;
        }
        current = current->right;  // 繼續往右子樹遞迴
      }
    }
  }

  // 建立線索二元樹
  void CreateThread() {
    TreeNode<T>* prev = nullptr;
    createThread(root, prev);  // 遞迴建立線索結構
  }

  // 中序遍歷並輸出節點資料
  void print() {
    TreeNode<T>* current = root;

    // 找到中序遍歷的第一個節點（最左）
    while (current && current->left) {
      current = current->left;
    }

    // 使用線索進行中序遍歷
    while (current) {
      // 輸出當前節點資料
      cout << *(current->data) << " ";

      // 如果右指標是線索，直接跳到下一個節點
      if (current->isThread) {
        current = current->right;
      } else {
        // 如果右指標不是線索，進入右子樹，找到其最左節點
        current = current->right;
        while (current && current->left) {
          current = current->left;
        }
      }
    }
  }
};

// 主程式
int main() {
  int j;
  Tree<int> tree;
  srand(time(nullptr));

  for (j = 0; j < 10; j++)
    tree.insert(rand() % 100);
  tree.CreateThread();  // CreateThread
  tree.print();

  return 0;
}
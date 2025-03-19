#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// SuffixTreeNode definition
class SuffixTreeNode {
 public:
  std::unordered_map<char, SuffixTreeNode*> children;
  std::vector<int> indexes;  // Store all starting indexes of suffixes

  ~SuffixTreeNode() {
    for (auto& child : children) {
      delete child.second;
    }
  }
};

class SuffixTree {
 private:
  SuffixTreeNode* root;
  std::string text;

  // Insert suffix into the tree starting from the given index
  void insertSuffix(const std::string& suffix, int index) {
    SuffixTreeNode* current = root;

    for (char ch : suffix) {
      if (current->children.find(ch) == current->children.end()) {
        current->children[ch] = new SuffixTreeNode();
      }
      current = current->children[ch];
      current->indexes.push_back(index);
    }
  }

  // Helper to check if a substring exists in the tree
  SuffixTreeNode* searchNode(const std::string& substring) {
    SuffixTreeNode* current = root;

    for (char ch : substring) {
      if (current->children.find(ch) == current->children.end()) {
        return nullptr;
      }
      current = current->children[ch];
    }

    return current;
  }

 public:
  SuffixTree(const std::string& text) : text(text) {
    root = new SuffixTreeNode();

    // Insert all suffixes of the text into the tree
    for (size_t i = 0; i < text.size(); ++i) {
      insertSuffix(text.substr(i), i);
    }
  }

  // Check if a substring exists in the text
  bool exist(const std::string& substring) {
    return searchNode(substring) != nullptr;
  }

  // Count occurrences of a substring in the text
  int count(const std::string& substring) {
    SuffixTreeNode* node = searchNode(substring);
    if (node == nullptr)
      return 0;
    return node->indexes.size();
  }

  ~SuffixTree() { delete root; }
};

int main() {
  std::string text = "";
  while (true) {
    std::string temp;
    getline(std::cin, temp);
    if (temp == "")
      break;
    text += temp;
  }
  SuffixTree tree(text);

  std::string substring;
  while (true) {
    getline(std::cin, substring);
    if (substring == "")
      break;
    std::cout << "Existence of '" << substring
              << "': " << (tree.exist(substring) ? "Yes" : "No") << std::endl;
    std::cout << "Count of '" << substring << "': " << tree.count(substring)
              << std::endl;
  }

  return 0;
}
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TrieNode {
 public:
  vector<TrieNode*> children;
  int isTerminal;
  char word;

  TrieNode() : isTerminal(false), word(0), children(26, nullptr) {}
};

class Trie {
 private:
  TrieNode* root;

  void preorderHelper(TrieNode* node, int level) {
    if (node == nullptr)
      return;

    if (level == 0)
      cout << "[]";
    else {
      string indent(level * 2, ' ');
      cout << indent << node->word;
    }
    cout << endl;

    for (auto& child : node->children) {
      if (child != nullptr) {
        preorderHelper(child, level + 1);
      }
    }
  }

 public:
  Trie() { root = new TrieNode(); }

  void insert(string word) {
    TrieNode* currentNode = root;
    for (char ch : word) {
      int index = ch - 'a';
      if (currentNode->children[index] == nullptr) {
        currentNode->children[index] = new TrieNode();
        currentNode->children[index]->word = ch;
      }
      currentNode = currentNode->children[index];
    }
    currentNode->isTerminal = true;
  }

  bool search(string key) {
    TrieNode* currentNode = root;
    for (char ch : key) {
      int index = ch - 'a';
      if (currentNode->children[index] == nullptr) {
        return false;
      }
      currentNode = currentNode->children[index];
    }
    return currentNode->isTerminal;
  }

  void preorder() { preorderHelper(root, 0); }
};

int main() {
  Trie* trie = new Trie();
  string command, key, word;

  while (1) {
    cin >> command;
    if (command == "insert") {
      cin >> word;
      trie->insert(word);
    } else if (command == "search") {
      cin >> key;
      if (trie->search(key))
        cout << "exist" << endl;
      else
        cout << "not exist" << endl;
    } else if (command == "print") {
      trie->preorder();
    } else if (command == "exit") {
      break;
    }
  }

  delete trie;
  return 0;
}

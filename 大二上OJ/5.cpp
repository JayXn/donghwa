#include <cstdlib>
#include <ctime>
#include <iostream>

#define SIZE 100

using namespace std;

class Node {
 public:
  Node() {
    next = NULL;
    pre = NULL;
  }
  Node(int n) {
    data = n;
    next = NULL;
    pre = NULL;
  }
  int getData() { return data; }
  Node* getNext() { return next; }
  Node* getPre() { return pre; }
  void setData(int d) { data = d; }
  void setNext(Node* n) { next = n; }
  void setPre(Node* p) { pre = p; }

 private:
  int data;
  Node *next, *pre;
};

class List {
 public:
  List() { list = NULL; }
  List(int n) { generate(n); }

  void generate(int n) {
    int j;
    list = NULL;
    for (j = 0; j < n; j++)
      generate();
  }

  void generate() {
    Node* buf = new Node(rand() % 100); 
    buf->setNext(list);
    if (list != NULL)
      list->setPre(buf);
    list = buf;
  }

  void bubbleSort() {
    if (!list)
      return;  
      
    bool swapped;
    do {
      swapped = false;
      Node* cur = list;
      while (cur->getNext() != NULL) {
        if (cur->getData() > cur->getNext()->getData()) {
          int temp = cur->getData();
          cur->setData(cur->getNext()->getData());
          cur->getNext()->setData(temp);
          swapped = true;
        }
        cur = cur->getNext();
      }
    } while (swapped);
  }

  void selectionSort() {
    if (!list)
      return;  

    Node* cur = list;
    while (cur != NULL) {
      Node* minNode = cur;
      Node* nextNode = cur->getNext();

      while (nextNode != NULL) { //找到最小的
        if (nextNode->getData() < minNode->getData()) {
          minNode = nextNode;
        }
        nextNode = nextNode->getNext();
      }

      if (minNode != cur) {
        int temp = cur->getData();
        cur->setData(minNode->getData());
        minNode->setData(temp);
      }
      cur = cur->getNext();
    }
  }

  void insertionSort() {
    if (!list)
      return;  

    Node* sorted = NULL;

    Node* cur = list;
    while (cur != NULL) {
      Node* next = cur->getNext();
      if (sorted == NULL || sorted->getData() >= cur->getData()) {  //放sorted開頭
        cur->setNext(sorted);
        sorted = cur;
      } else {  // 插sorted中間
        Node* current = sorted;
        while (current->getNext() != NULL && current->getNext()->getData() < cur->getData()) { 
          current = current->getNext();
        }
        cur->setNext(current->getNext());
        current->setNext(cur);
      }
      cur = next;
    }
    list = sorted;
  }

  void print() {
    Node* cur = list;
    while (cur != NULL) {
      cout << cur->getData() << " ";
      cur = cur->getNext();
    }
    cout << endl;
  }

 private:
  Node* list;
};

int main() {
  srand(time(NULL));
  List* l = new List(10);
  l->print();
  l->bubbleSort();
  l->print();

  l = new List(10);
  l->print();
  l->insertionSort();
  l->print();

  l = new List(10);
  l->print();
  l->selectionSort();
  l->print();
}

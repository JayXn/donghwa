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
    Node* buf =
        new Node(rand() % 100);  
    buf->setNext(list);
    if (list != NULL)
      list->setPre(buf);
    list = buf;
  }

  void bubbleSort() {
    bool swapped;
    do {
      swapped = false;
      Node* cur = list;
      while (cur != NULL && cur->getNext() != NULL) {
        Node* next = cur->getNext();
        if (cur->getData() > next->getData()) {
          swap(cur, next);
          swapped = true;
        }
        cur = next;
      }
    } while (swapped);
  }

  void selectionSort() {
    Node* cur = list;

    while (cur != NULL) {
      Node* minNode = cur;  
      Node* next = cur->getNext();

      while (next != NULL) {
        if (next->getData() < minNode->getData()) {
          minNode = next; 
        }
        next = next->getNext();
      }

      if (minNode != cur) {
        swap(cur, minNode);  
        cur = minNode;
      }

      cur = cur->getNext();
    }
  }

  void insertionSort() {
    if (list == NULL)
      return;

    Node* sorted = NULL;
    Node* cur = list;

    while (cur != NULL) {
      Node* next = cur->getNext();
      insertSorted(&sorted, cur);
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

  void swap(Node* a, Node* b) {
    if (a == b)
      return;

    Node* aPrev = a->getPre();
    Node* aNext = a->getNext();
    Node* bPrev = b->getPre();
    Node* bNext = b->getNext();

    if (aNext == b)  
    {
      a->setNext(bNext);
      if (bNext != NULL)
        bNext->setPre(a);
      b->setPre(aPrev);
      b->setNext(a);
      a->setPre(b);
      if (aPrev != NULL)
        aPrev->setNext(b);
    } else if (bNext == a)  
    {
      b->setNext(aNext);
      if (aNext != NULL)
        aNext->setPre(b);
      a->setPre(bPrev);
      a->setNext(b);
      b->setPre(a);
      if (bPrev != NULL)
        bPrev->setNext(a);
    } else  
    {
      if (aPrev != NULL)
        aPrev->setNext(b);
      if (aNext != NULL)
        aNext->setPre(b);
      if (bPrev != NULL)
        bPrev->setNext(a);
      if (bNext != NULL)
        bNext->setPre(a);

      Node* tempPrev = a->getPre();
      Node* tempNext = a->getNext();

      a->setPre(b->getPre());
      a->setNext(b->getNext());

      b->setPre(tempPrev);
      b->setNext(tempNext);
    }

    if (list == a)
      list = b;
    else if (list == b)
      list = a;
  }

  void insertSorted(Node** sorted, Node* newNode) {
    if (*sorted == NULL || (*sorted)->getData() >= newNode->getData()) {
      newNode->setNext(*sorted);
      if (*sorted != NULL)
        (*sorted)->setPre(newNode);
      *sorted = newNode;
    } else {
      Node* cur = *sorted;
      while (cur->getNext() != NULL && cur->getNext()->getData() < newNode->getData()) {
        cur = cur->getNext();
      }
      newNode->setNext(cur->getNext());
      if (cur->getNext() != NULL)
        cur->getNext()->setPre(newNode);
      cur->setNext(newNode);
      newNode->setPre(cur);
    }
  }
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
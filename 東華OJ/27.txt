#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class LinkedList {
  public:
    LinkedList():head(nullptr){}
    ~LinkedList() {
      Node* current = head;
      while (current) {
          Node* next = current->getNext();
          delete current;
          current = next;
      }
    }

  public:
    class Node {
    public:
       Node(): next(nullptr), data(0) {}
       Node(int d): next(nullptr), data(d) {}
       Node(Node* n): next(n), data(0) {}
       Node(Node* n, int d): next(n), data(d) {}
       int data;
       Node* next;

    public:
      Node *&getNext(){
        return next;
      }
      int &getData(){
        return data;
      }
    };

    class iterator {
    public:
      Node * it;
      iterator(Node * p) : it(p) {}

      iterator &operator++(){
        it = it -> getNext();
        return *this;
      }
      bool operator==(iterator i){
        return it == i.it;
      }
      bool operator!=(iterator i){
        return it != i.it;
      }
      int &operator*(){
        return it->getData();
      }
    };

    iterator begin(){
      return iterator(head);
    }
    iterator end(){
      return iterator(NULL);
    }

    bool addFromHead(int d) {
      Node *newnode = new Node(d);
      newnode -> next = head;
      head = newnode;
      return true;
    }
    bool addFromTail(int d) {
      Node *newnode = new Node(d);
      if(!head){
        head = newnode;
        return true;
      }
      else{
        Node *temp = head;
        while(temp -> getNext()){
          temp = temp -> getNext();
        }
        temp -> getNext() = newnode;
        return true;
      }
      return false;
    }
    bool removeFromHead() {
      if(!head){
        return false;
      }
      Node *temp = head;
      head = head -> getNext();
      delete temp;
      return true;
    }
    bool removeFromTail() {
      if(!head){
        return false;
      }
      if(head -> getNext() == nullptr){
         delete head;
         head = nullptr;
         return true;
      }
      Node *temp = head;
      while(temp -> getNext() -> getNext()){
        temp = temp -> getNext();
      }
      delete temp -> getNext();
      temp -> next = nullptr;
      return true;
    }

    size_t getSize() const {
      size_t size = 0;
      Node * temp = head;
      while(temp){
        size++;
        temp = temp -> getNext();
      }
      return size;
    }
   
    friend ostream& operator<<(ostream& o, LinkedList *l) {
      size_t size = l -> getSize();
      int output_times = 0;
      if(size == 0){
        cout << "{}" << endl;
        return o;
      }
      if(size == 1){
        cout << "{" << l->head->data << "}" << endl;
        return o;
      }
      cout << "{";
      for_each(l -> begin() , l -> end() , 
        [&output_times , &size](int j){
          if(output_times == size-1){
            cout << j;
          }
          else{
            cout << j << ", ";
            output_times++;
          }
      });
      cout << "}" << endl;
      return o;
    }
  
   protected:
    Node* head;
};

int main() {
    LinkedList *list = new LinkedList();
    list->addFromHead(5);
    list->addFromHead(1);
    list->addFromHead(2);
    list->addFromTail(9);
    list->addFromTail(9);
    list->addFromTail(9);
    cout << list << endl;

    return 0;
}

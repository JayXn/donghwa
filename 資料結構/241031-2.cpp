#include <iostream>
#include <string>

using namespace std;

template <typename T> class DLinkedList;

template <typename T>
class DNode {
 public:
  DNode* prev;
  DNode* next;
  T elem;
  friend class DLinkedList<T>;
};

template <typename T>
class DLinkedList {
 public:
  DLinkedList() {
    header = new DNode<T>;
    trailer = new DNode<T>;
    header->next = trailer;
    trailer->prev = header;
  }

  ~DLinkedList() {
    while (!empty()) {
      removefront();
    }
    delete header;
    delete trailer;
  }

  // empty
  bool empty() const { return (header->next == trailer); }

  // getfront
  const T& getfront() const { return header->next->elem; }

  // getback
  const T& getback() const { return trailer->prev->elem; }

  // addfront
  void addfront(const T& e) { add(header->next, e); }

  // addback
  void addback(const T& e) { add(trailer, e); }

  // removefront
  void removefront() { remove(header->next); }

  // removeback
  void removeback() { remove(trailer->prev); }

 private:
  DNode<T>* header;
  DNode<T>* trailer;

 protected:
  // add
  void add(DNode<T>* v, const T& e) {
    DNode<T>* u = new DNode<T>;
    u->elem = e;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = u;
    v->prev = u;
  }

  // remove
  void remove(DNode<T>* v) {
    DNode<T>* p = v->prev;
    DNode<T>* n = v->next;
    p->next = n;
    n->prev = p;
    delete v;
  }
};

int main() {
  DLinkedList<string> list;

  list.addfront("Jay");
  list.addback("Gary");
  list.addback("Antony");
  list.addfront("TA");

  cout << "Front: " << list.getfront() << endl;  
  cout << "Back: " << list.getback() << endl;    

  list.removefront();                                        
  cout << "Front after remove: " << list.getfront() << endl;  

  list.removeback();                                        
  cout << "Back after remove: " << list.getback() << endl;  

  return 0;
}

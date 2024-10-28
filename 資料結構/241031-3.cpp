#include <iostream>
#include <stdexcept>
using namespace std;


typedef string Elem;
class CNode {
 private:
  Elem elem;
  CNode* next;

  friend class CircleList;
};

class CircleList {
 public:
  CircleList() : cursor(nullptr) {}
  ~CircleList() {
    while (!empty()) {
      remove();
    }
  }

  bool empty() const;
  const Elem& front() const;
  const Elem& back() const;
  void advance();
  void add(const Elem& e);
  void remove();

  class Exception : public runtime_error {
   public:
    Exception(): runtime_error("Wrong operation, List is empty!!") {}
  };

 private:
  CNode* cursor;
};

bool CircleList::empty() const {
  return cursor == nullptr;
}

const Elem& CircleList::front() const {
  if (empty()) {
    throw Exception();
  }
  return cursor->next->elem;
}

const Elem& CircleList::back() const {
  if (empty()) {
    throw Exception();
  }
  return cursor->elem;
}

void CircleList::advance() {
  if (empty()) {
    throw Exception();
  }
  cursor = cursor->next;
}

void CircleList::add(const Elem& e) {
  CNode* v = new CNode;
  v->elem = e;
  if (cursor == nullptr) {
    v->next = v;
    cursor = v;
  } else {
    v->next = cursor->next;
    cursor->next = v;
  }
}

void CircleList::remove() {
  if (empty()) {
    throw Exception();
  }
  CNode* old = cursor->next;
  if (old == cursor) {
    cursor = nullptr; 
  } else {
    cursor->next = old->next;
  }
  delete old;
}

int main() {
  CircleList cl;

  try {
    cl.front();  
  } catch (const CircleList::Exception& e) {
    cout << e.what() << endl;
  }

  cl.add("Jay");
  cout << "Back element: " << cl.back() << endl;

  cl.add("Gary");
  cout << "Front element: " << cl.front() << endl;

  cl.add("Antony");
  cout << "Front element: " << cl.front() << endl;

  cl.advance();
  cout << "Front element after advance: " << cl.front() << endl;

  cl.advance();
  cout << "Front element after advance: " << cl.front() << endl;

  cl.remove();
  cout << "Back element after removing: " << cl.back() << endl;


  try {
    cl.front();  
  } catch (const CircleList::Exception& e) {
    cout << e.what() << endl;
  }

  return 0;
}

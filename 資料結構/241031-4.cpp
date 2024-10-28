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
  int size() const;

  class EmptyListException : public std::runtime_error {
   public:
    EmptyListException()
        : runtime_error("Invalid operation: circular list is empty") {}
  };

 private:
  CNode* cursor;
};

bool CircleList::empty() const {
  return cursor == nullptr;
}

const Elem& CircleList::front() const {
  if (empty()) {
    throw EmptyListException();
  }
  return cursor->next->elem;
}

const Elem& CircleList::back() const {
  if (empty()) {
    throw EmptyListException();
  }
  return cursor->elem;
}

void CircleList::advance() {
  if (empty()) {
    throw EmptyListException();
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
    throw EmptyListException();
  }
  CNode* old = cursor->next;
  if (old == cursor) {
    cursor = nullptr;
  } else {
    cursor->next = old->next;
  }
  delete old;
}

int CircleList::size() const {
  int count = 0;
  CNode* temp = cursor;
  while(temp != nullptr) {
    count++;
    temp = temp->next;
    if (temp == cursor) {
      break;
    }
  }
  return count;
}

int main() {
  CircleList cl;

  cl.add("Jay");

  cl.add("Antony");

  cout << "There are " << cl.size() << " nodes" << endl;

  cl.add("Gary");

  cout << "There are " << cl.size() << " nodes" << endl;

  return 0;
}

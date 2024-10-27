#include <iostream>

using namespace std;

class StringNode{
private:
  string elem;
  StringNode* next;

  friend class StringLinkedList;
};

class StringLinkedList{
public:
  StringLinkedList():head(nullptr){}
  ~StringLinkedList() {
    while(!empty()){
      removeFront();
    }
  }
  bool empty() const;
  const string& front() const;
  void addFront(const string& e);
  void removeFront();
  int size();

private:
  StringNode* head;
};

bool StringLinkedList::empty() const{
  return head == nullptr;
}
const string& StringLinkedList::front() const{
  return head->elem;
}
void StringLinkedList::addFront(const string& e){
  StringNode* newnode = new StringNode;
  newnode->elem = e;
  newnode->next = head;
  head = newnode;
}
void StringLinkedList::removeFront(){
  StringNode* old = head;
  head = head -> next;
  delete old;
}
int StringLinkedList::size(){
  int s = 0;
  StringNode* current = head;
  while(current != nullptr){
    s += 1;
    current = current -> next;
  }
  return s;
}

int main(){
  StringLinkedList test;

  test.addFront("Jay");
  test.addFront("Antony");
  test.addFront("Gary");

  cout << "Size = " << test.size() << endl;    

  test.addFront("TA");

  cout << "Size = " << test.size() << endl;
}
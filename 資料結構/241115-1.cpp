#include <iostream>
#include <vector>

using namespace std;

template <class T>
class stack {
 private:
  vector<T> data;

 public:
  void push(T value) { data.push_back(value); }
  void pop() { data.pop_back(); }
  T top() { return data.back(); }
  bool empty() { return data.empty(); }
  int size() { return data.size(); }
};

int main() {
  stack<int> myStack;
  myStack.push(100);
  myStack.push(200);
  myStack.push(300);
  cout << myStack.top() << endl;
  myStack.pop();
  cout << myStack.top() << endl;
  cout << myStack.size() << endl;
  cout << myStack.empty() << endl;
  myStack.pop();
  myStack.pop();
  cout << myStack.empty() << endl;
  return 0;
}

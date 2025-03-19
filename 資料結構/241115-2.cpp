#include <iostream>
#include <stdexcept>

using namespace std;

class CircularArrayDeque{
public:
  int size(){
    return count;
  }
  bool empty(){
    return count == 0;
  }
  int front(){
    if(count == 0){
      throw runtime_error("Queue is empty");
    }
    return data[IndexFront];
  }
  int back(){
    if(count == 0){
      throw runtime_error("Queue is empty");
    }
    return data[(IndexRear - 1 + 100) % 100];
  }
  void enqueueFront(int value){
    if(count == 100){
      throw runtime_error("Queue is full");
    }
    IndexFront = (IndexFront - 1 + 100) % 100;
    data[IndexFront] = value;
    count++;
  }
  void enqueueBack(int value){
    if(count == 100){
      throw runtime_error("Queue is full");
    }
    data[IndexRear] = value;
    IndexRear = (IndexRear + 1) % 100;
    count++;
  }
  void dequeueFront(){
    if(count == 0){
      throw runtime_error("Queue is empty");
    }
    IndexFront = (IndexFront + 1) % 100;
    count--;
  }
  void dequeueBack(){
    if(count == 0){
      throw runtime_error("Queue is empty");
    }
    IndexRear = (IndexRear - 1 + 100) % 100;
    count--;
  }
private:
  int data[100];
  int count = 0;
  int IndexFront = 0;
  int IndexRear = 0;
};


int main(){
  CircularArrayDeque q;
  q.enqueueBack(100);
  q.enqueueBack(200);
  q.enqueueBack(300);
  cout << "q.front(): " << q.front() << endl;
  cout << "q.back(): " << q.back() << endl;
  q.dequeueFront();
  cout << "q.front(): " << q.front() << endl;
  cout << "q.back(): " << q.back() << endl;
  q.dequeueBack();
  cout << "q.front(): " << q.front() << endl;
  cout << "q.back(): " << q.back() << endl;
  q.dequeueFront();
  cout << "q.empty(): " << q.empty() << endl;
}

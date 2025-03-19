#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class CircularArrayQueue {
 public:
  CircularArrayQueue(int initial_capacity = 100) : capacity(initial_capacity), data(new T[capacity]) {}

  ~CircularArrayQueue() { delete[] data; }

  int size() const { return count; }

  bool empty() const { return count == 0; }

  T front() const {
    if (empty()) {
      throw runtime_error("Queue is empty");
    }
    return data[IndexFront];
  }

  void enqueue(const T& value) {
    if (count == capacity) {
      resize();
    }
    data[IndexRear] = value;
    IndexRear = (IndexRear + 1) % capacity;
    count++;
  }

  void dequeue() {
    if (empty()) {
      throw runtime_error("Queue is empty");
    }
    IndexFront = (IndexFront + 1) % capacity;
    count--;
  }

 private:
  T* data;
  int capacity;
  int count = 0;
  int IndexFront = 0;
  int IndexRear = 0;

  void resize() {
    int new_capacity = capacity * 2;
    T* new_data = new T[new_capacity];

    for (int i = 0; i < count; i++) {
      new_data[i] = data[(IndexFront + i) % capacity];
    }

    delete[] data;
    data = new_data;
    capacity = new_capacity;
    IndexFront = 0;
    IndexRear = count;
  }
};

int main() {
  CircularArrayQueue<int> queue;

  queue.enqueue(10);
  queue.enqueue(20);
  queue.enqueue(30);

  cout << "Front element: " << queue.front() << endl;
  queue.dequeue();

  cout << "Front element after dequeue: " << queue.front() << endl;
  cout << "Queue size: " << queue.size() << endl;

  return 0;
}

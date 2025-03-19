#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Position {
 public:
  T value;
  int index;

  Position(T val, int idx) : value(val), index(idx) {}
};

template <typename T>
class CircularSequence {
 private:
  Position<T>** data;
  int front, rear, size, capacity;

 public:
  CircularSequence(int cap) : front(0), rear(0), size(0), capacity(cap) {
    data = new Position<T>*[capacity];
  }

  ~CircularSequence() {
    for (int i = 0; i < size; ++i) {
      delete data[(front + i) % capacity];
    }
    delete[] data;
  }

  int getSize() const { return size; }
  bool isEmpty() const { return size == 0; }

  class Iterator {
   private:
    const CircularSequence* seq;
    int idx;

   public:
    Iterator(const CircularSequence* s, int start) : seq(s), idx(start) {}

    Position<T>* operator*() { return seq->data[idx]; }

    Iterator& operator++() {
      idx = (idx + 1) % seq->capacity;
      return *this;
    }

    Iterator& operator--() {
      idx = (idx - 1 + seq->capacity) % seq->capacity;
      return *this;
    }

    bool operator!=(const Iterator& other) const { return idx != other.idx; }
  };

  Iterator begin() { return Iterator(this, front); }
  Iterator end() { return Iterator(this, (front + size) % capacity); }

  Iterator atIndex(int i) const {
    if (i < 0 || i >= size)
      throw out_of_range("Index out of range");
    return Iterator(this, (front + i) % capacity);
  }

  int indexOf(const T& value) const {
    for (int i = 0; i < size; ++i) {
      if (data[(front + i) % capacity]->value == value)
        return i;
    }
    return -1;
  }

  void insertFront(const T& value) {
    if (size == capacity)
      throw overflow_error("Sequence is full");
    front = (front - 1 + capacity) % capacity;
    data[front] = new Position<T>(value, 0);
    for (int i = 1; i < size; ++i) {
      data[(front + i) % capacity]->index = i;
    }
    ++size;
  }

  void insertBack(const T& value) {
    if (size == capacity)
      throw overflow_error("Sequence is full");
    data[rear] = new Position<T>(value, size);
    rear = (rear + 1) % capacity;
    ++size;
  }

  void insert(int index, const T& value) {
    if (index < 0 || index > size)
      throw out_of_range("Index out of range");
    if (size == capacity)
      throw overflow_error("Sequence is full");

    if (index == 0) {
      insertFront(value);
    } else if (index == size) {
      insertBack(value);
    } else {
      for (int i = size; i > index; --i) {
        data[(front + i) % capacity] = data[(front + i - 1) % capacity];
        data[(front + i) % capacity]->index = i;
      }
      data[(front + index) % capacity] = new Position<T>(value, index);
      ++size;
    }
  }

  void erase(int index) {
    if (isEmpty())
      throw underflow_error("Sequence is empty");
    if (index < 0 || index >= size)
      throw out_of_range("Index out of range");

    delete data[(front + index) % capacity];

    for (int i = index; i < size - 1; ++i) {
      data[(front + i) % capacity] = data[(front + i + 1) % capacity];
      data[(front + i) % capacity]->index = i;
    }
    rear = (rear - 1 + capacity) % capacity;
    --size;
  }
};

int main() {
  CircularSequence<int> seq(5);

  seq.insertBack(20);
  seq.insertBack(30);
  seq.insert(2, 40);
  seq.insertFront(10);

  cout << "Print sequence: ";
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    cout << (*it)->value << " ";
  }
  cout << endl;

  seq.erase(3);
  cout << "Print sequence after erasing index 3: ";
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    cout << (*it)->value << " ";
  }
  cout << endl;

  auto it = seq.atIndex(0);
  cout << "atIndex(0): " << (*it)->value << endl;
  cout << "Index of 20: " << seq.indexOf(20) << endl;

  return 0;
}

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

template <class T>
class MinMaxHeap {
 public:
  MinMaxHeap() {}

  void insert(T value) {
    data.push_back(value);
    bubbleUp(data.size() - 1);
  }

  T getMin() const {
    if (data.empty())
      throw std::out_of_range("Heap is empty");
    return data[0];
  }

  T getMax() const {
    if (data.empty())
      throw std::out_of_range("Heap is empty");
    if (data.size() == 1)
      return data[0];
    if (data.size() == 2)
      return data[1];
    return std::max(data[1], data[2]);
  }

  void deleteMin() {
    if (data.empty())
      throw std::out_of_range("Heap is empty");
    data[0] = data.back();
    data.pop_back();
    if (!data.empty())
      trickleDown(0);
  }

  void deleteMax() {
    if (data.empty())
      throw std::out_of_range("Heap is empty");
    int maxIndex = (data.size() == 2) ? 1 : (data[1] > data[2] ? 1 : 2);
    data[maxIndex] = data.back();
    data.pop_back();
    if (maxIndex < data.size())
      trickleDown(maxIndex);
  }

 private:
  std::vector<T> data;

  bool isMinLevel(int index) const {
    return static_cast<int>(std::log2(index + 1)) % 2 == 0;
  }

  void bubbleUp(int index) {
    if (index == 0)
      return;
    int parent = (index - 1) / 2;

    if (isMinLevel(index)) {
      if (data[index] > data[parent]) {
        std::swap(data[index], data[parent]);
        bubbleUpMax(parent);
      } else {
        bubbleUpMin(index);
      }
    } else {
      if (data[index] < data[parent]) {
        std::swap(data[index], data[parent]);
        bubbleUpMin(parent);
      } else {
        bubbleUpMax(index);
      }
    }
  }

  void bubbleUpMin(int index) {
    int grandparent = (index - 3) / 4;
    if (index >= 3 && data[index] < data[grandparent]) {
      std::swap(data[index], data[grandparent]);
      bubbleUpMin(grandparent);
    }
  }

  void bubbleUpMax(int index) {
    int grandparent = (index - 3) / 4;
    if (index >= 3 && data[index] > data[grandparent]) {
      std::swap(data[index], data[grandparent]);
      bubbleUpMax(grandparent);
    }
  }

  void trickleDown(int index) {
    if (isMinLevel(index)) {
      trickleDownMin(index);
    } else {
      trickleDownMax(index);
    }
  }

  void trickleDownMin(int index) {
    if (index >= data.size())
      return;

    int m = index;
    int child1 = 2 * index + 1;
    int child2 = 2 * index + 2;
    int grandchild1 = 4 * index + 3;
    int grandchild2 = 4 * index + 4;
    int grandchild3 = 4 * index + 5;
    int grandchild4 = 4 * index + 6;

    if (child1 < data.size() && data[child1] < data[m])
      m = child1;
    if (child2 < data.size() && data[child2] < data[m])
      m = child2;

    if (grandchild1 < data.size() && data[grandchild1] < data[m])
      m = grandchild1;
    if (grandchild2 < data.size() && data[grandchild2] < data[m])
      m = grandchild2;
    if (grandchild3 < data.size() && data[grandchild3] < data[m])
      m = grandchild3;
    if (grandchild4 < data.size() && data[grandchild4] < data[m])
      m = grandchild4;

    if (m != index) {
      if (m == child1 || m == child2) {
        std::swap(data[index], data[m]);
      } else {
        std::swap(data[index], data[m]);
        int parent = (m - 1) / 2;
        if (data[m] > data[parent])
          std::swap(data[m], data[parent]);
        trickleDownMin(m);
      }
    }
  }

  void trickleDownMax(int index) {
    if (index >= data.size())
      return;

    int m = index;
    int child1 = 2 * index + 1;
    int child2 = 2 * index + 2;
    int grandchild1 = 4 * index + 3;
    int grandchild2 = 4 * index + 4;
    int grandchild3 = 4 * index + 5;
    int grandchild4 = 4 * index + 6;

    if (child1 < data.size() && data[child1] > data[m])
      m = child1;
    if (child2 < data.size() && data[child2] > data[m])
      m = child2;

    if (grandchild1 < data.size() && data[grandchild1] > data[m])
      m = grandchild1;
    if (grandchild2 < data.size() && data[grandchild2] > data[m])
      m = grandchild2;
    if (grandchild3 < data.size() && data[grandchild3] > data[m])
      m = grandchild3;
    if (grandchild4 < data.size() && data[grandchild4] > data[m])
      m = grandchild4;

    if (m != index) {
      if (m == child1 || m == child2) {
        std::swap(data[index], data[m]);
      } else {
        std::swap(data[index], data[m]);
        int parent = (m - 1) / 2;
        if (data[m] < data[parent])
          std::swap(data[m], data[parent]);
        trickleDownMax(m);
      }
    }
  }
};

int main() {
  MinMaxHeap<int> mmHeap;
  int j;
  srand(time(NULL));
  for (j = 0; j < 10; j++)
    mmHeap.insert(rand() % 100);

  while (true) {
    try {
      std::cout << mmHeap.getMin() << " ";
      mmHeap.deleteMin();
    } catch (std::exception&) {
      break;
    }
  }
  std::cout << std::endl;

  for (j = 0; j < 10; j++)
    mmHeap.insert(rand() % 100);

  while (true) {
    try {
      std::cout << mmHeap.getMax() << " ";
      mmHeap.deleteMax();
    } catch (std::exception&) {
      break;
    }
  }

  return 0;
}

#include <iostream>
#include <stdexcept>
#include <vector>

template <class T>
class MaxHeap {
 public:
  MaxHeap() {}

  void insert(T value) {
    heap.push_back(value);
    heapify_up(heap.size() - 1);
  }

  T extract() { //提取最大值
    if (heap.empty()) {
      throw std::out_of_range("Heap is empty");
    }

    T root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapify_down(0);

    return root;
  }

  int count() { return heap.size(); }

 private:
  std::vector<T> heap;

  int parent(int i) { return (i - 1) / 2; }

  int left_child(int i) { return 2 * i + 1; }

  int right_child(int i) { return 2 * i + 2; }

  void swap(int i, int j) {
    T temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
  }

  void heapify_up(int i) { //確保父節點大於子節點
    while (i > 0 && heap[parent(i)] < heap[i]) {
      swap(i, parent(i));
      i = parent(i);
    }
  }

  void heapify_down(int i) { //確保子節點小於父節點
    int largest = i;
    int left = left_child(i);
    int right = right_child(i);

    if (left < heap.size() && heap[left] > heap[largest]) {
      largest = left;
    }

    if (right < heap.size() && heap[right] > heap[largest]) {
      largest = right;
    }

    if (largest != i) {
      swap(i, largest);
      heapify_down(largest);
    }
  }
};

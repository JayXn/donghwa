#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

void bubbleSort(vector<int>& arr, int left, int right) {
  for (int i = left; i < right; i++) {
    for (int j = left; j < right - (i - left); j++) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

int partition(vector<int>& arr, int left, int right) {
  int pivot = arr[right];
  int i = left - 1;
  for (int j = left; j < right; j++) {
    if (arr[j] <= pivot) {
      i++;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[right]);
  return i + 1;
}

void quickSort(vector<int>& arr, int left, int right, int board) {
  if (right - left + 1 <= board) {
    bubbleSort(arr, left, right);
    return;
  }

  if (left < right) {
    int pivotIndex = partition(arr, left, right);
    quickSort(arr, left, pivotIndex - 1, board);
    quickSort(arr, pivotIndex + 1, right, board);
  }
}

int main() {
  vector<int> dataSizes = {1000, 10000, 100000, 1000000};
  int board = 20;

  srand(time(0));

  for (int size : dataSizes) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
      arr[i] = rand() % 100000;
    }

    auto start = high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1, board);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    cout << "Quick Sort 資料量: " << size << ", board: " << board
         << ", 花費時間: " << duration << " μs" << endl;
  }

  return 0;
}

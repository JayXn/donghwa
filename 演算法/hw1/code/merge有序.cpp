#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>  // for std::sort

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

void merge(vector<int>& arr, int left, int mid, int right) {
  vector<int> temp;
  int i = left, j = mid + 1;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp.push_back(arr[i]);
      i++;
    } else {
      temp.push_back(arr[j]);
      j++;
    }
  }
  while (i <= mid) {
    temp.push_back(arr[i]);
    i++;
  }
  while (j <= right) {
    temp.push_back(arr[j]);
    j++;
  }

  for (int k = 0; k < temp.size(); k++) {
    arr[left + k] = temp[k];
  }
}

void mergeSort(vector<int>& arr, int left, int right, int board) {
  if (right - left + 1 <= board) {
    bubbleSort(arr, left, right);
    return;
  }

  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, board);
    mergeSort(arr, mid + 1, right, board);
    merge(arr, left, mid, right);
  }
}

int main() {
  vector<int> dataSizes = {1000, 10000, 100000, 1000000};
  int board = 100;

  srand(time(0));

  for (int size : dataSizes) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
      arr[i] = rand() % 100000;
    }
    sort(arr.begin(), arr.end());

    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1, board);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    cout << "Merge Sort 資料量: " << size << ", board: " << board
         << ", 花費時間: " << duration << " μs" << endl;
  }

  return 0;
}

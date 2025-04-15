#include <algorithm>  // for std::sort
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

int main() {
  vector<int> dataSizes = {1000, 10000, 100000, 1000000};
  int board = 100;

  srand(time(0));

  for (int size : dataSizes) {
    vector<int> arr(size);
    fill(arr.begin(), arr.end(), 1);

    auto start = high_resolution_clock::now();
    std::sort(arr.begin(), arr.end());
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    cout << "std::Sort 資料量: " << size << ", board: " << board
         << ", 花費時間: " << duration << " μs" << endl;
  }

  return 0;
}

#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template <typename T>
T sum(const vector<T>& v) {
  T total = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    total += *it;
  }
  return total;
}

int main() {
  vector<int> intVec = {10, 20, 30, 40, 50};
  cout << "Sum of intVec: " << sum(intVec) << endl;

  vector<float> floatVec = {1.1, 2.2, 3.3, 4.4};
  cout << "Sum of floatVec: " << sum(floatVec) << endl;

  vector<double> doubleVec = {100.5, 200.5, 300.25};
  cout << "Sum of doubleVec: " << sum(doubleVec) << endl;

  vector<int> emptyVec;
  cout << "Sum of emptyVec: " << sum(emptyVec) << endl;

  vector<long> longVec = {100000, 200000, 300000, 400000};
  cout << "Sum of longVec: " << sum(longVec) << endl;

  return 0;
}

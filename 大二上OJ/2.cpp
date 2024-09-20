#include <cstdlib>
#include <iostream>

using namespace std;

template <class T>
class Memory {
 public:
  static T** allocArray(int m, int n) {
    T* data = (T*)malloc(sizeof(T) * m * n);

    T** array = (T**)malloc(sizeof(T*) * m);

    for (int i = 0; i < m; i++) {
      array[i] = &data[i * n];
    }

    return array;
  }
};

int main() {
  int** array = Memory<int>::allocArray(5, 10);

  for (int j = 0; j < 5; j++)
    for (int k = 0; k < 10; k++)
      array[j][k] = j * 10 + k;

  for (int j = 0; j < 5; j++) {
    for (int k = 0; k < 10; k++)
      cout << array[j][k] << " ";
    cout << endl;
  }

  free(array[0]);
  free(array);

  return 0;
}
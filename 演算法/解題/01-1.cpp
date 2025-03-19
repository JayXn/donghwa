#include <iostream>

using namespace std;

int Classify(int a) {
  if (a == 0)
    return 1;
  else if (a == 1)
    return 2;
  else
    return 3;
}

int Classify2(int a) {
  int table[6] = {1, 2, 3, 3, 3, 3};
  return table[a];
}

int main() {
  int ans = Classify2(1);
  cout << ans << endl;
  return 0;
}


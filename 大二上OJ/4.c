#include <stdio.h>

int main() {
  int a, b, c;

  scanf("%d %d %d", &a, &b, &c);

  float average = (a + b + c) / 3.0;

  printf("%.6f\n", average);
  return 0;
}
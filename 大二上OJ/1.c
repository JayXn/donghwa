#include <stdio.h>
#include <stdlib.h>

void allocArray(int*** p, int m, int n) {
  (*p) = malloc(sizeof(int *) * m);
  (*p)[0] = malloc(sizeof(int) * n);

  for(int i = 1 ; i < m ; i++){
    (*p)[i] = (*p)[0] + i * n; //?? 為什麼這邊不是直接數幾個byte
  }
}

int main() {
  int** array;
  int j, k;
  allocArray(&array, 5, 10);

  for (j = 0; j < 5; j++) {
    for (k = 0; k < 10; k++) {
      array[j][k] = j * 10 + k;
    }
  }

  for (j = 0; j < 5; j++) {
    for (k = 0; k < 10; k++) {
      printf("%p ", &(array[j][k]));
    }
    printf("\n");
  }

  // for (j = 0; j < 5; j++) {
  //     for (k = 0; k < 10; k++) {
  //         printf("%d ", array[j][k]);
  //     }
  //     printf("\n");
  // }

  free(array[0]);
  free(array);

  return 0;
}

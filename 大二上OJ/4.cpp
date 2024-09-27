#include <cstring>
#include <iostream>

#define SIZE 100

using namespace std;

class Queue {
 public:
  Queue() {
    top = 0;
    bot = 0;  // 都設為0容易判斷陣列是否空
  }
  int enqueue(int integer) {
    if ((top + 1) % SIZE == bot) {  // 判斷queue full有兩種方法。1. 使用第三變數紀錄容器數量 2. 使用頭尾指標間的關係
      return -1;
    }
    data[top] = integer;
    top = (top + 1) % SIZE;
    return 1;
  }
  int* dequeue() {  // 為什麼回傳值要用指標？
    if (top == bot) {
      return NULL;
    }
    int* result = &data[bot];  // 多設一個result讓bot加完後可以回傳原本的資料
    bot = (bot + 1) % SIZE;
    return result;
  }

 private:
  int data[SIZE];
  int top, bot;
};

int main() {
  int data, *temp;
  char command[50];
  Queue* queue = new Queue();
  while (1) {
    cin >> command;
    if (strcmp(command, "exit") == 0) {
      break;
    } else if (strcmp(command, "enqueue") == 0) {
      cout << "Please input a integer data:";
      cin >> data;
      if (queue->enqueue(data) == 1) {
        cout << "Successfully enqueue data " << data << " into queue." << endl;
      } else {
        cout << "Failed to enqueue data into queue." << endl;
      }
    } else if (strcmp(command, "dequeue") == 0) {
      temp = queue->dequeue();
      if (temp == NULL) {
        cout << "Failed to dequeue a data from queue.\n";
      } else {
        cout << "Dequeue data " << *temp << " from queue." << endl;
      }
    }
  }
}
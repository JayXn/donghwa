#include <cstdlib>
#include <ctime>
#include <iostream>

#define SIZE 10

using namespace std;

class Node {
 public:
  Node() { row = col = 0; }
  Node(int r, int c) : row(r), col(c) {}
  int getRow() { return row; }
  int getCol() { return col; }
  void setRow(int r) {
    if (r >= 0 && r < SIZE)
      row = r;
  }
  void setCol(int c) {
    if (c >= 0 && c < SIZE)
      col = c;
  }

 private:
  int col, row;
};

class List {
 public:
  List() : top(0) {}
  void addElement(int r, int c) {
    if (top < SIZE * SIZE) {
      data[top].setRow(r);
      data[top].setCol(c);
      top++;
    }
  }
  Node* removeElement() {
    if (top > 0) {
      top--;
      return &data[top];
    }
    return NULL;
  }
  void printList() {
    for (int j = 0; j < top; j++) {
      cout << "(" << data[j].getRow() << ", " << data[j].getCol() << ")" << endl;
    }
  }

 private:
  Node data[SIZE * SIZE];
  int top;
};

class Maze {
 public:
  Maze() { initMaze(SIZE); }

  void initMaze(int s) {
    maze = new int*[s];
    for (int i = 0; i < s; i++) {
      maze[i] = new int[s];
    }
    srand(time(NULL));
    for (int i = 0; i < s; i++) {
      for (int j = 0; j < s; j++) {
        maze[i][j] = (rand() % 100 < 20) ? 1 : 0;
      }
    }
    maze[0][0] = 0;
    maze[s - 1][s - 1] = 0;
  }

  List* getPath() {
    List* path = new List();
    bool visited[SIZE][SIZE] = {false};
    if (findPath(0, 0, path, visited))
      return path;
    return new List();
  }

  bool findPath(int row, int col, List* path, bool visited[SIZE][SIZE]) {
    if (row < 0 || col < 0 || row >= SIZE || col >= SIZE || maze[row][col] == 1 || visited[row][col])
      return false;
    path->addElement(row, col);
    visited[row][col] = true;
    if (row == SIZE - 1 && col == SIZE - 1)
      return true;
    if (findPath(row + 1, col, path, visited) ||
        findPath(row, col + 1, path, visited) ||
        findPath(row - 1, col, path, visited) ||
        findPath(row, col - 1, path, visited))
      return true;
    path->removeElement();
    return false;
  }

  void printMaze() {
    for (int j = 0; j < SIZE; j++) {
      for (int k = 0; k < SIZE; k++) {
        cout << (maze[j][k] == 0 ? " " : "*");
      }
      cout << "\n";
    }
  }

  ~Maze() {
    for (int i = 0; i < SIZE; i++) {
      delete[] maze[i];
    }
    delete[] maze;
  }

 private:
  int** maze;
};

int main() {
  Maze* maze = new Maze();
  maze->printMaze();
  maze->getPath()->printList();
  delete maze;
  return 0;
}

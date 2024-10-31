#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid {
 public:
  Grid(int s = 0) : state(s) { fill(begin(dir), end(dir), nullptr); }

  Grid* getDir(int d) { return dir[d]; }
  int getState() const { return state; }
  void setDir(int d, Grid* g) { dir[d] = g; }
  void setState(int s) { state = s; }

 private:
  Grid* dir[4];
  int state;
};

class List {
 public:
  List() : top(0) {}

  void addElement(Grid* g) {
    if (top < SIZE * SIZE) {
      data[top++] = g;
    }
  }

  Grid* removeElement() {
    if (top > 0) {
      return data[--top];
    }
    return NULL;
  }

  Grid* getLastElement() {
    if (top > 0) {
      return data[top - 1];
    }
    return NULL;
  }

  bool isEmpty() { return top == 0; }

  void printPath() {
    for (int i = 1; i < top; ++i) {
      Grid* curr = data[i];
      Grid* prev = data[i - 1];
      if (curr == prev->getDir(UP))
        cout << "UP\n";
      else if (curr == prev->getDir(DOWN))
        cout << "DOWN\n";
      else if (curr == prev->getDir(LEFT))
        cout << "LEFT\n";
      else if (curr == prev->getDir(RIGHT))
        cout << "RIGHT\n";
    }
  }

 private:
  Grid* data[SIZE * SIZE];
  int top;
};

class Maze {
 public:
  Maze() { initMaze(SIZE); }

  ~Maze() { clearMaze(maze); }

  void initMaze(int s) {
    srand(time(NULL));
    Grid* prevRow[SIZE] = {nullptr};
    maze = nullptr;

    for (int i = 0; i < s; ++i) {
      Grid* prev = nullptr;
      for (int j = 0; j < s; ++j) {
        Grid* g = new Grid((rand() % 100 < 20) ? 1 : 0);
        if (i == 0 && j == 0)
          g->setState(0);
        if (i == s - 1 && j == s - 1)
          g->setState(0);

        if (prev) { //不是列頭的話
          prev->setDir(RIGHT, g);
          g->setDir(LEFT, prev);
        }

        if (i > 0 && prevRow[j]) { //跟上行連結
          prevRow[j]->setDir(DOWN, g);
          g->setDir(UP, prevRow[j]);
        }

        prev = g;
        prevRow[j] = g;
        if (!maze)
          maze = g;
      }
    }
  }

  void printPath() {
    List path;
    if (findPath(maze, path)) {
      path.printPath();
    } else {
      cout << "No path found.\n";
    }
  }

  void printMaze() {
    Grid* row = maze;
    while (row) {
      Grid* col = row;
      while (col) {
        cout << col->getState();
        col = col->getDir(RIGHT);
      }
      cout << endl;
      row = row->getDir(DOWN);
    }
  }

 private:
  Grid* maze;

  bool findPath(Grid* g, List& path) {
    if (!g || g->getState() == 1)
      return false;

    path.addElement(g);
    g->setState(1);

    if (g->getDir(DOWN) == nullptr && g->getDir(RIGHT) == nullptr) {
      return true;
    }

    if (findPath(g->getDir(RIGHT), path) || findPath(g->getDir(DOWN), path) ||
        findPath(g->getDir(LEFT), path) || findPath(g->getDir(UP), path)) {
      return true;
    }

    path.removeElement();
    return false;
  }

  void clearMaze(Grid* g) {
    if (!g)
      return;
    Grid* right = g->getDir(RIGHT);
    Grid* down = g->getDir(DOWN);

    delete g;

    clearMaze(right);
    clearMaze(down);
  }
};

int main() {
  Maze maze;
  maze.printMaze();
  maze.printPath();

  return 0;
}

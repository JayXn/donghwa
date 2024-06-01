#include <cmath>
#include <iomanip>
#include <iostream>
#include <cstdio>

using namespace std;

class Point {
 public:
  double x;
  double y;

  Point(): x(0), y(0) {}
  Point(double x, double y): x(x), y(y) {}
};

class HillClimb {
 public:
  void processTestCase() {
    int number;
    cin >> number;

    Point* points = new Point[number];

    for (int i = 0; i < number; i++) {
      double x, y;
      cin >> x >> y;
      points[i] = Point(x, y);
    }

    for (int i = number - 1; i > 0; i--) {  // 依照 x 座標遞減排序
      for (int j = 0; j < i; j++) {
        if (points[j].x < points[j + 1].x) {
          Point temp = points[j];
          points[j] = points[j + 1];
          points[j + 1] = temp;
        }
      }
    }

    double max_height = points[0].y;
    double total_length = 0;

    // 計算總長度  用max_height記錄最高點
    for (int i = 1; i < number; i++) {
      if (points[i].y > points[i - 1].y) {
        if (points[i].y > max_height) {
          double slope_length = sqrt(pow(points[i].x - points[i - 1].x, 2) + pow(points[i].y - points[i - 1].y, 2));
          total_length += slope_length * ((points[i].y - max_height) / (points[i].y - points[i - 1].y));
          max_height = points[i].y;
        }
      }
    }

    printf("%.2f\n", total_length);

    delete[] points;
  }
};

int main() {
  int T;
  cin >> T;

  HillClimb hillClimb;

  for (int i = 0; i < T; i++) {
    hillClimb.processTestCase();
  }

  return 0;
}
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

class Point{
private:
  float x;
  float y;

public:
  Point(): x(0), y(0){};
  Point(float a, float b) : x(a), y(b){};

  void printPoint() {
    cout << "(" << x << ", " << y << ")" << endl;
  }
  float getX(){
    return x;
  }
  float setX(float c){
    x = c;
    return x;
  }
  float getY(){
    return y;
  }
  float setY(float d){
    y = d;
    return y;
  }
  float getDistance(Point p){
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
  }
};


class Segment{
  public:
  	Point p1;
  	Point p2;
  public:
  	Segment(){
      p1.setX(0);
      p1.setY(0);
      p2.setX(0);
      p2.setY(0);
    }
  	Segment(Point _p1,Point _p2){
      p1 = _p1;
      p2 = _p2;
    }
    float getLength(){
      return p1.getDistance(p2);
    }
};


class Shape{
private:
  Segment seg[10];
  int edgeCount;

public:
  Shape() : edgeCount(0){};
  virtual float getArea() = 0;
  Shape(Segment* s, int n) {
      for (int i = 0; i < n - 1; i++) {
        if ((s[i].p2.getX() != s[i + 1].p1.getX() || s[i].p2.getY() != s[i + 1].p1.getY())) {
          throw invalid_argument("shape is not closed");
        }
      }
      if (n < 3 || s[0].p1.getX() != s[n - 1].p2.getX() || s[0].p1.getY() != s[n - 1].p2.getY()) {
        throw invalid_argument("At least 3 edges and first connect to last");
      }
      for (int i = 0; i < n; i++) {
        seg[i] = s[i];
      }
      edgeCount = n;
  }  // to construct a shape with a serial of segment. Throw an invalid_argument if the segment can not construct a close path.

  float getPerimeter() {
    float perimeter = 0;
    for (int i = 0; i < edgeCount; i++) {
        perimeter += seg[i].getLength();
    }
    return perimeter;
  }

  Segment& getSeg(int index) {
      return seg[index];
  }
};

class Rectangle : public Shape {
public:
  Rectangle(Segment *s) : Shape(s, 4){}
  float getArea(){
    return getSeg(0).getLength() * getSeg(1).getLength();
  }
};
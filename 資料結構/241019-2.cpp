#include <cmath>  
#include <cstdio>
#include <iostream>

using namespace std;

class quadraticEq{
public:
  int a,b,c;

  quadraticEq(int A, int B, int C):a(A),b(B),c(C){}

  double d() const {
    return b * b - 4 * a * c;
  }

  void OutputRoots() const {
    if(d() > 0){
      double root1 = (-b + sqrt(d())) / (2 * a);
      double root2 = (-b - sqrt(d())) / (2 * a);
      cout << "Two real roots:" << endl;
      cout << "x1 = " << root1 << endl;
      cout << "x2 = " << root2 << endl;

    }else if(d() == 0){
      double root = -b / (2 * a);
      cout << "A single root:" << endl;
      cout << "x = " << root << endl;
    }else{
      double realPart = -b / (2 * a);
      double imaginaryPart = sqrt(-d()) / (2 * a);
      cout << "Two complex roots:" << endl;
      cout << "x1 = " << realPart << " + " << imaginaryPart << "i" << endl;
      cout << "x2 = " << realPart << " - " << imaginaryPart << "i" << endl;
    }
  }

  quadraticEq operator+(const quadraticEq& other) const {
    return quadraticEq(a + other.a, b + other.b, c + other.c);
  }

  quadraticEq operator-(const quadraticEq& other) const {
    return quadraticEq(a - other.a, b - other.b, c - other.c);
  }

  bool operator==(const quadraticEq& other) const {
    return a == other.a && b == other.b && c == other.c;
  }

  bool operator!=(const quadraticEq& other) const {
    return !(*this == other); 
  }

  friend ostream& operator<<(ostream& os, const quadraticEq& q) {
    if (q.a != 0) {
      os << q.a << "x^2 ";
    }
    if (q.b > 0) {
      os << "+" << q.b << "x ";
    } else if (q.b < 0) {
      os << "-" << -q.b << "x ";
    }
    if (q.c > 0) {
      os << "+" << q.c;
    } else if (q.c < 0) {
      os << "-" << -q.c;
    }
    return os;
  }

  friend istream& operator>>(istream& is,  quadraticEq& q){
    is >> q.a >> q.b >> q.c;
    return is;
  }
};

int main(){
  int a1 = 1, b1 = -2, c1 = 1;
  quadraticEq q1(a1, b1, c1);
  int a2 = 1, b2 = -3, c2 = 2;
  quadraticEq q2(a2, b2, c2);

  cout << q1 << endl;
  cout << q2 << endl;
  cout << "d1 = " << q1.d() << endl;
  cout << "d2 = " << q2.d() << endl;
  q1.OutputRoots();
  q2.OutputRoots();
  cout << "q1 + q2 = " << q1 + q2 << endl;
  cout << "q1 - q2 = " << q1 - q2 << endl;
  cout << "q1 == q2: " << (q1 == q2) << endl;
  cout << "q1 != q2: " << (q1 != q2) << endl;
  return 0;
}
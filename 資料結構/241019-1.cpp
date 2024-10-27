#include <cstdio>
#include <iostream>

using namespace std;

class A {
public:
  A():x(100){};

  int x;
};

class B : public A {
public:
  B():x(200){};

  int x;
};

class C : public B {
public:
  C():x(300){};

  void PrintCBA(){
    cout << "C's x = " << x << endl;
    cout << "B's x = " << B::x << endl;
    cout << "A's x = " << A::x << endl;
  }

  void ModifyCBA(){
    cout << "C'x 300->30" << endl;
    x = 30;
    cout << "B'x 200->20" << endl;
    B::x = 20;
    cout << "A'x 100->10" << endl;
    A::x = 10;
  }


  int x;
};

int main() {

  C TestC;
  TestC.PrintCBA();
  TestC.ModifyCBA();
  TestC.PrintCBA();
}
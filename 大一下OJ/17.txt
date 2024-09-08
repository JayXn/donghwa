#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Fraction {
 public:
  Fraction() : numerator(0), denominator(1) {}
  Fraction(int n, int m) : numerator(n) {
    if (m == 0)
      throw "divided by zero";
    denominator = m;
  }
  int getNumerator() const {
    return numerator;
  }
  int getDenominator() const {
    return denominator;
  }
  void setNumerator(int n) {
    numerator = n;
  }
  void setDenominator(int m) {
    if (m == 0)
      throw "divided by zero";
    denominator = m;
  }


  friend std::ostream& operator<<(std::ostream& cout, const Fraction& f) {
    if (f.denominator != 1) {
      if (f.numerator == 0) {
        cout << 0;
        return cout;
      }
      cout << "[" << f.numerator << "/" << f.denominator << "]";
    } else
      cout << f.numerator;
    return cout;
  }

 private:
  int numerator, denominator;
};

//計算最大公因數
int getGCD(int a, int b) { 
  while (b != 0) {
    int temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}

// 約分函式
Fraction simplify(const Fraction &f) {
  int n = f.getNumerator();
  int m = f.getDenominator();
  int gcd = getGCD(n , m);
  n /= gcd;
  m /= gcd;
  return Fraction(n, m);
}

Fraction operator+(const Fraction& f1, const Fraction& f2) {
  int n = f1.getNumerator() * f2.getDenominator() + f2.getNumerator() * f1.getDenominator();
  int m = f1.getDenominator() * f2.getDenominator();
  return simplify(Fraction(n, m));
}

Fraction operator-(const Fraction& f1, const Fraction& f2) {
  int n = f1.getNumerator() * f2.getDenominator() - f2.getNumerator() * f1.getDenominator();
  int m = f1.getDenominator() * f2.getDenominator();
  return simplify(Fraction(n, m));
}

bool operator==(const Fraction& f1, const Fraction& f2) { //通分比較
  return f1.getNumerator() * f2.getDenominator() == f2.getNumerator() * f1.getDenominator();
}



int main() {
  int n1, n2, m1, m2;
  cin >> n1 >> m1 >> n2 >> m2;
  Fraction f1(n1, m1), f2(n2, m2);
  cout << (f1 + f2) << endl;
  cout << (f1 - f2) << endl;
  cout << (f1 == f2) << endl;
}
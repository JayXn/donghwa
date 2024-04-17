#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Fraction {
private:
    int numerator, denominator;
public:
    Fraction() : numerator(0), denominator(1) {}
    Fraction(int n, int d) : numerator(n) {
        if (d == 0)
            throw "divided by zero";
        else {
            denominator = d;
        }
    }
    int coutGCD(int a, int b) {
        if (b == 0) return a;
        while (b != 0) {
            int gcd = b;
            b = a % b;
            a = gcd;
        }
        return a;
    }
    int coutLCM(int a, int b) {
        return a * b / coutGCD(a, b);
    }
    int checkDeno(int d1, int d2) {
        if (d1 == 0 || d2 == 0) {
            throw "divided by zero";
        }
        return coutLCM(d1, d2);
    }
    Fraction changeSign(int num, int deno) {
        
        if (num > 0 && deno < 0) {
            num *= -1;
            deno = abs(deno);
        }
        return Fraction(num, deno);
    }
    Fraction simplifyFraction(const Fraction& f) {
        int n = f.getNumerator();
        int d = f.getDenominator();
        int gcd = coutGCD(n, d);
        return Fraction(n / gcd, d / gcd);
    }
    Fraction operator+(const Fraction& f) {
        int n1 = this->getNumerator();
        int n2 = f.getNumerator();
        int d1 = this->getDenominator();
        int d2 = f.getDenominator();
        int deno = checkDeno(d1, d2);
        Fraction result = Fraction(((n1 * deno / d1) + (n2 * deno / d2)), deno);
        return simplifyFraction(result);
    }
    Fraction operator-(const Fraction& f) {
        int n1 = this->getNumerator();
        int n2 = f.getNumerator();
        int d1 = this->getDenominator();
        int d2 = f.getDenominator();
        int deno = checkDeno(d1, d2);
        int num = (n1 * deno / d1) - (n2 * deno / d2);
        if (num == 0) {
            return Fraction();
        }
        Fraction result = Fraction(num, deno);
        return simplifyFraction(result);
    }
    Fraction operator*(const Fraction& f) {
        int n1 = this->getNumerator();
        int n2 = f.getNumerator();
        int d1 = this->getDenominator();
        int d2 = f.getDenominator();
        int num = n1 * n2;
        int deno = d1 * d2;
        if (num == 0) {
            return Fraction();
        }
        Fraction result = Fraction(num, deno);
        return simplifyFraction(result);
    }
    Fraction operator/(const Fraction& f) {
        int n1 = this->getNumerator();
        int n2 = f.getNumerator();
        int d1 = this->getDenominator();
        int d2 = f.getDenominator();
        int num = n1 * d2;
        int deno = n2 * d1;
        if (num == 0) {
            return Fraction();
        }
        Fraction result = Fraction(num, deno);
        return simplifyFraction(result);
    }
    Fraction operator!() {
        int n = this->getDenominator();
        int d = this->getNumerator();
        Fraction result = Fraction(n, d);
        return simplifyFraction(result);
    }
    Fraction& operator=(const Fraction& f) {
        numerator = f.getNumerator();
        denominator = f.getDenominator();
        return *this;
    }
    friend ostream& operator<<(ostream &os, Fraction f) {
        int gcd = f.coutGCD(f.numerator, f.denominator);
        f = f.changeSign(f.numerator / gcd, f.denominator / gcd);
        int num = f.getNumerator();
        int deno = f.getDenominator();
        if (deno != 1)
            os << "(" << num << "/" << deno << ")";
        else
            os << "(" << num << ")";
        return os;
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
    void setDenominator(int d) {
        if (d == 0)
            throw "divided by zero";
        else {
            denominator = d;
        }
    }
    void display() {
        int gcd = coutGCD(this->numerator, this->denominator);
        Fraction temp = changeSign(this->numerator / gcd, this->denominator / gcd);
        int num = temp.getNumerator();
        int deno = temp.getDenominator();
        if (deno != 1)
            cout << "(" << num << "/" << deno << ")";
        else
            cout << "(" << num << ")";
    }
};
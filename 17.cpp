#include <iostream>
#include <string>
using namespace std;

class Fraction
{
public:
    Fraction() : numerator(0), denominator(1) {}
    Fraction(int n, int m) : numerator(n)
    {
        if (m == 0)
            throw "divided by zero";
        denominator = m;
    }
    int getNumerator() const
    {
        return numerator;
    }
    int getDenominator() const
    {
        return denominator;
    }
    void setNumerator(int n)
    {
        numerator = n;
    }
    void setDenominator(int m)
    {
        if (m == 0)
            throw "divided by zero";
        denominator = m;
    }
    friend std::ostream &operator<<(std::ostream &out, const Fraction &f)
    {
        if (f.denominator != 1)
            out << "[" << f.numerator << "/" << f.denominator << "]";
        else
            out << f.numerator;
        return out;
    }

private:
    int numerator, denominator;
};

int coutGCD(int a, int b)
{
    while (b != 0)
    {
        int gcd = b;
        b = a % b;
        a = gcd;
    }
    return a;
}
int coutLCM(int a, int b)
{
    return a * b / coutGCD(a, b);
}
int checkDeno(int d1, int d2)
{
    if (d1 == 0 || d2 == 0)
    {
        throw "divided by zero";
    }
    else if (coutGCD(d1, d2) != 1)
    {
        return coutGCD(d1, d2);
    }
    return coutLCM(d1, d2);
}

Fraction simplifyFraction(const Fraction &f)
{
    int n = f.getNumerator();
    int d = f.getDenominator();
    int gcd = coutGCD(n, d);
    return Fraction(n / gcd, d / gcd);
}

Fraction operator+(const Fraction &f1, const Fraction &f2)
{
    int n1 = f1.getNumerator();
    int n2 = f2.getNumerator();
    int d1 = f1.getDenominator();
    int d2 = f2.getDenominator();
    int deno = checkDeno(d1, d2);
    Fraction result = Fraction(((n1 * deno / d1) + (n2 * deno / d2)), deno);
    return simplifyFraction(result);
}
Fraction operator-(const Fraction &f1, const Fraction &f2)
{
    int n1 = f1.getNumerator();
    int n2 = f2.getNumerator();
    int d1 = f1.getDenominator();
    int d2 = f2.getDenominator();
    int deno = checkDeno(d1, d2);
    int num = (n1 * deno / d1) - (n2 * deno / d2);
    if (num == 0)
    {
        return Fraction();
    }
    Fraction result = Fraction(num, deno);
    return simplifyFraction(result);
}
bool operator==(const Fraction &f1, const Fraction &f2)
{
    int gcd1 = coutGCD(f1.getNumerator(), f1.getDenominator());
    int gcd2 = coutGCD(f2.getNumerator(), f2.getDenominator());
    int sim_n1 = f1.getNumerator() / gcd1;
    int sim_n2 = f2.getNumerator() / gcd2;
    int sim_d1 = f1.getDenominator() / gcd1;
    int sim_d2 = f2.getDenominator() / gcd2;
    if (sim_n1 == sim_n2 && sim_d1 == sim_d2)
    {
        return true;
    }
    else if (f1.getNumerator() == 0 && f2.getNumerator() == 0)
    {
        return true;
    }
    return false;
}
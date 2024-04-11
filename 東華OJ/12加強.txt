#include <iostream>
#include <string>

using namespace std;

class Digit { // class Digit represent a digit in base 10
  int digit;
public:
  Digit() : digit(0) {}
  Digit(int d) : digit(d % 10) {}
  void setDigit(int d) { digit = d % 10; }
  int getDigit() const {return digit;}
};
class Integer { //class Integer represent a integer
  Digit value[1000];
  bool sign;
  size_t _size;
public:
  //construct an integer in base 10 using a string.
  //This constructor will convert the given string to integer if possible.
  //Otherwise it will convert the digit part in prefix of the given string.
  Integer(string n) : sign(true), _size(0)
  {
    for(auto c: n) {
      if(c < '0' || c > '9') break;
      value[_size++] = Digit(c - '0');
    }
  }
  //default constructor will construct an Integer object with value 0.
  Integer() : sign(true), _size(1)
  {
    value[0] = Digit(0);
  }
  //function addition will add up two integer and return a new Integer object as result.
  Integer addition(const Integer &b) const
  {
    if((!sign && !b.sign) || (sign && !b.sign && *this < -b)) {
      return -(-*this).addition(-b);
    }
    string str;
    int carry = 0;
    size_t lim = max(_size, b._size);
    for(size_t i = 0; i < lim; i++) {
      carry += sign ? getDigit(i) : -getDigit(i);
      carry += b.sign ? b.getDigit(i) : -b.getDigit(i);
      if(carry >= 0) {
        str += char(carry % 10 + '0');
        carry /= 10;
      } else {
        str += char(carry + 10 + '0');
        carry = -1;
      }
    }
    while(carry > 0) {
      str += char(carry % 10 + '0');
      carry /= 10;
    }
    int z = str.size() - 1;
    for(; z > 0; --z)
      if(str.at(z) != '0') break;
    
    return Integer(string(str.rend() - z - 1, str.rend()));
  }
  //function subtraction will minus b from current object and return a new Integer object as result.
  Integer subtraction(const Integer &b) const
  {
    return addition(-b);
  }

  size_t size() const
  {
    return _size;
  }

  int getDigit(const int n) const
  {
    return (n >= _size) ? 0 : value[_size - n - 1].getDigit();
  }

  Integer operator-() const
  {
    Integer res = *this;
    res.sign = !res.sign;
    return res;
  }

  bool operator<(const Integer& other) const
  {
    if(sign != other.sign)
      return sign < other.sign;
    if(_size != other._size)
      return sign == _size < other._size;
    for(size_t i = 0; i < _size; ++i) {
      if(value[i].getDigit() != other.value[i].getDigit())
        return sign == value[i].getDigit() < other.value[i].getDigit();
    }
    return false;
  }

  void display()
  {
    if(sign == false)
      cout << '-';
    for(size_t i = 0; i < _size; ++i) {
      cout << value[i].getDigit();
    }
  }
  
  friend istream& operator>>(istream& in, Integer& i)
  {
    string str;
    in >> str;
    i = Integer(str);
    return in;
  }
};

#define string Integer
#include <iostream>
#include <string>

using namespace std;

class Digit { // class Digit represent a digit in base 10
  int digit;
public: 
  Digit(){}
  Digit(int d) : digit(d % 10) {}
  void setDigit(int d) { digit = d % 10; }
  int getDigit() const {return digit;}
};

class Integer { //class Integer represent a integer
  friend bool compareStrings(const Integer& str1, const Integer& str2);

  Digit value[1001];
  bool sign = true;
  int m_Length = 0;
public:

  //用字串建構一個十進位的數字
  //可能的話建構子會將給定的字串轉為數字
  //否則會把字串前綴的數字部分轉為字串
  Integer(string n){
    TurnToPositive(n);
    RemoveLeadingZero(n);
    if(n.size() == 0) n = "0";    //如果字串為空，則初始化為0
    m_Length = n.size();
    Initial(n);
  }

  //默認建構函數初始化陣列
  Integer(){
    for(int i = 0 ; i < 1001 ; i++){
      value[i].setDigit(0);
    }
  }
  //加法
  Integer addition(const Integer &b) const;
  //減法
  Integer subtraction(const Integer &b) const;

  void TurnToPositive(string &n) {        //判斷正負並轉為正數
    if (n[0] == '-') {
      sign = false;
      n = n.substr(1);
    }
    else {
      sign = true;
    }
  }

  void RemoveLeadingZero(string &n) {     //移除前導零
    int i = 0;
    while (n[i] == '0') {
      i++;
    }
    n = n.substr(i);
  }

  void Initial(string &n){                //將字串轉為數字儲存在陣列中
    int tempLength = 0;
    for(int i = 0; i < m_Length; i++) {
      if(isdigit(n[i])) {
        value[i].setDigit(n[i] - '0');
        tempLength++;                     //計算數字長度
      } 
      else {
        m_Length = tempLength;
        if(i == 0) {
          value[0].setDigit(0);
          m_Length = 1;
        }
        break;
      }
    }
    m_Length = tempLength;
  }

  //判斷哪個數字較大，並將數字反轉對齊寫到Cal_A, Cal_B
  void AddBigger(const Integer &a, const Integer &b, Integer &Cal_A, Integer &Cal_B) const
  {
    if (a.m_Length > b.m_Length)
    { 
      Cal_A = a;
      for (int i = 0; i < a.m_Length; i++){    //將數字反轉對齊
        Cal_A.value[i].setDigit(a.value[a.m_Length - i - 1].getDigit());
      }
      Cal_B = b;
      for (int i = 0; i < b.m_Length; i++){
        Cal_B.value[i].setDigit(b.value[b.m_Length - i - 1].getDigit());
      }
    }
    else if (a.m_Length < b.m_Length)
    { 
      Cal_A = b;
      for (int i = 0; i < b.m_Length; i++){  
        Cal_A.value[i].setDigit(b.value[b.m_Length - i - 1].getDigit());
      }
      Cal_B = a;
      for (int i = 0; i < a.m_Length; i++){
        Cal_B.value[i].setDigit(a.value[a.m_Length - i - 1].getDigit());
      }
    }
    else if (a.m_Length == b.m_Length)
    {
      for (int i = 0; i < a.m_Length; i++)
      {
        if (a.value[i].getDigit() > b.value[i].getDigit())
        {
          Cal_A = a;
          for (int i = 0; i < a.m_Length; i++)
          {
            Cal_A.value[i].setDigit(a.value[a.m_Length - i - 1].getDigit());
          }
          Cal_B = b;
          for (int i = 0; i < b.m_Length; i++)
          {
            Cal_B.value[i].setDigit(b.value[b.m_Length - i - 1].getDigit());
          }
        }
        else if (a.value[i].getDigit() < b.value[i].getDigit())
        {
          Cal_A = b;
          for (int i = 0; i < b.m_Length; i++)
          {
            Cal_A.value[i] = b.value[b.m_Length - i - 1];
          }
          Cal_B = a;
          for (int i = 0; i < a.m_Length; i++)
          {
            Cal_B.value[i] = a.value[a.m_Length - i - 1];
          }
        }
        else if (a.value[i].getDigit() == b.value[i].getDigit() && i == a.m_Length - 1)
        {
          Cal_A = a;
          for (int i = 0; i < a.m_Length; i++)
          {
            Cal_A.value[i].setDigit(a.value[a.m_Length - i - 1].getDigit());
          }
          Cal_B = b;
          for (int i = 0; i < b.m_Length; i++)
          {
            Cal_B.value[i].setDigit(b.value[b.m_Length - i - 1].getDigit());
          }
        }
      }
    }
  }

  int SubBigger(const Integer &a, const Integer &b, Integer &Cal_A, Integer &Cal_B) const{
    if(a.sign != b.sign){
      Cal_A = a;
      Cal_B = b;
      for(int i = 0 ; i < a.m_Length ; i++){    //將數字反轉對齊
        Cal_A.value[i].setDigit(a.value[a.m_Length - i - 1].getDigit());
      }
      for(int i = 0 ; i < b.m_Length ; i++){
        Cal_B.value[i].setDigit(b.value[b.m_Length - i - 1].getDigit());
      }
      return 0;   //tempResult的正負為a.sign，運算為數字相加
    }
    else{
      if(a.m_Length > b.m_Length){
        Cal_A = a;
        Cal_B = b;
        for(int i = 0 ; i < a.m_Length ; i++){    //將數字反轉對齊
          Cal_A.value[i].setDigit(a.value[a.m_Length - i - 1].getDigit());
        }
        for(int i = 0 ; i < b.m_Length ; i++){
          Cal_B.value[i].setDigit(b.value[b.m_Length - i - 1].getDigit());
        }
        return 1; //tempResult的正負為a.sign，運算為數字相減
      }
      else if(a.m_Length < b.m_Length){
        Cal_A = b;
        Cal_B = a;
        for(int i = 0 ; i < b.m_Length ; i++){    //將數字反轉對齊
          Cal_A.value[i].setDigit(b.value[b.m_Length - i - 1].getDigit());
        }
        for(int i = 0 ; i < a.m_Length ; i++){
          Cal_B.value[i].setDigit(a.value[a.m_Length - i - 1].getDigit());
        }
        return 2; //tempResult的正負為a.sign的變號，運算為數字相減
      }
      else if(a.m_Length == b.m_Length){
        for(int i = 0 ; i < a.m_Length ; i++){
          if(a.value[i].getDigit() > b.value[i].getDigit()){
            Cal_A = a;
            Cal_B = b;
            for(int i = 0 ; i < a.m_Length ; i++){    //將數字反轉對齊
              Cal_A.value[i].setDigit(a.value[a.m_Length - i - 1].getDigit());
            }
            for(int i = 0 ; i < b.m_Length ; i++){
              Cal_B.value[i].setDigit(b.value[b.m_Length - i - 1].getDigit());
            }
            return 1;   //tempResult的正負為a.sign，運算為數字相減
          }
          else if(a.value[i].getDigit() < b.value[i].getDigit()){
            Cal_A = b;
            Cal_B = a;
            for(int i = 0 ; i < b.m_Length ; i++){    //將數字反轉對齊
              Cal_A.value[i].setDigit(b.value[b.m_Length - i - 1].getDigit());
            }
            for(int i = 0 ; i < a.m_Length ; i++){
              Cal_B.value[i].setDigit(a.value[a.m_Length - i - 1].getDigit());
            }
            return 2;   //tempResult的正負為a.sign的變號，運算為數字相減
          }
          else if(a.value[i].getDigit() == b.value[i].getDigit() && i == a.m_Length - 1){
            return 3;  //tempResult的正負為a.sign，運算為數字相減
          }
        }
      }
    }
    return 0;
  }

  void display() const {                  //顯示數字
    if(m_Length == 1 && value[0].getDigit() == 0) {
      cout << '0';
      return;
    }
    if(!sign) cout << '-';
    for(int i = 0; i < m_Length; i++) {
      cout << value[i].getDigit();
    }
  }
};

Integer Integer::addition(const Integer &b) const{
  const Integer &a = *this;
  Integer tempResult;
  Integer Cal_A;  //將數字反轉對齊結果放這裡
  Integer Cal_B;

  //將數字反轉對齊，且判斷哪個數字較長較大
  AddBigger(a, b, Cal_A, Cal_B);
  tempResult.m_Length = Cal_A.m_Length + 1;
  tempResult.sign = Cal_A.sign;

  if(Cal_A.sign == Cal_B.sign){ //同號相加
    int carry = 0;
    for(int i = 0; i < Cal_A.m_Length + 1 ; i++){
      int sum = Cal_A.value[i].getDigit() + Cal_B.value[i].getDigit() + carry;   
      carry = sum / 10;
      sum %= 10;
      tempResult.value[i].setDigit(sum);
    }
  }
  if(Cal_A.sign != Cal_B.sign){ //異號相減
    int borrow = 0;
    for(int i = 0; i < Cal_A.m_Length ; i++){
      int sum = Cal_A.value[i].getDigit() - Cal_B.value[i].getDigit() - borrow;
      if(sum < 0){
        sum += 10;
        borrow = 1;
      }
      else{
        borrow = 0;
      }
      tempResult.value[i].setDigit(sum);
    }
  }

  //去除前導0
  while(tempResult.value[tempResult.m_Length - 1].getDigit() == 0 && tempResult.m_Length > 1){
    tempResult.m_Length--;
  }

  Integer result;
  result = tempResult;
  for(int i = 0 ; i < tempResult.m_Length ; i++){    //將計算的結果反轉
    result.value[i] = tempResult.value[tempResult.m_Length - i - 1];
  }


  return result;
}

//正的數字減負的數字是數字相加 負的數字減正的數字是數字相加 --> 同號相減是數字相減
//異號相減是相加
Integer Integer::subtraction(const Integer &b) const{

  const Integer& a = *this;
  Integer tempResult;
  Integer Cal_A;
  Integer Cal_B;
  int judge = SubBigger(a, b, Cal_A, Cal_B);

  switch(judge){    //判斷tempResult的正負
    case 0:
      tempResult.m_Length = max(Cal_A.m_Length, Cal_B.m_Length) + 1;
      tempResult.sign = a.sign;
      break;
    case 1:
      tempResult.m_Length = Cal_A.m_Length + 1;
      tempResult.sign = a.sign;
      break;
    case 2:
      tempResult.m_Length = Cal_A.m_Length + 1;
      tempResult.sign = !a.sign;
      break;
  }
  if(judge == 0){   //tempResult的運算為數字相加
    //Cal_A的value陣列加上Cal_B的value陣列
    int carry = 0;
    for(int i = 0 ; i < tempResult.m_Length ; i++){
      int sum = Cal_A.value[i].getDigit() + Cal_B.value[i].getDigit() + carry;
      carry = sum / 10;
      sum %= 10;
      tempResult.value[i].setDigit(sum);
    }
  }
  else if(judge == 1 || judge == 2){   //tempResult的運算為數字相減
    int borrow = 0;
    for(int i = 0 ; i < Cal_A.m_Length ; i++){
      int sum = Cal_A.value[i].getDigit() - Cal_B.value[i].getDigit() - borrow;
      if(sum < 0){
        sum += 10;
        borrow = 1;
      }
      else{
        borrow = 0;
      }
      tempResult.value[i].setDigit(sum);
    }
  }
  else if(judge == 3){
    tempResult.m_Length = 1;
    tempResult.value[0].setDigit(0);
  }

  //去除前導0
  while(tempResult.value[tempResult.m_Length - 1].getDigit() == 0 && tempResult.m_Length > 1){
    tempResult.m_Length--;
  }


  Integer result;
  result = tempResult;
  for(int i = 0 ; i < tempResult.m_Length ; i++){    //將計算的結果反轉
    result.value[i] = tempResult.value[tempResult.m_Length - i - 1];
  }

  return result;
}




int main()
{
  string a, b;
  cin >> a >> b;

  Integer num1(a), num2(b);

  num1.addition(num2).display();
  cout << endl;       
  num2.addition(num1).display();
  cout << endl;
  num1.subtraction(num2).display();
  cout << endl;
  num2.subtraction(num1).display();
  cout << endl;
}
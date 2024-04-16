#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>

using namespace std;

class Date {
    private:
        int pos;
        int days;
        string initialTime;
        vector <string> time;
    public:
        Date(): days(0), initialTime("1900/01/01") {};
        Date(string t): days(0) {
            string subtime;
            // 分割字串
            while ((pos = t.find("/")) != string::npos) {
                subtime = t.substr(0, pos);
                time.push_back(subtime);
                t.erase(0, pos + 1);
            }
            time.push_back(t);
            coutDays();
        }
        // 判斷是否為閏年
        bool isLeapYear(int year) const {
            if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
                return true;
            }
            return false;
        }
        // 判斷大小月
        int isBigMonth(int month) const {
            if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                return 31;
            }
            else if (month == 2 && isLeapYear(stoi(time[0]))) {
                return 29;
            }
            else if (month == 2 && !isLeapYear(stoi(time[0]))) {
                return 28;
            }
            return 30;
        }
        // 計算天數
        void coutDays() {
            if (isLeapYear(stoi(time[0]))) {
                for (int i = 1; i <= stoi(time[1]); i++) {
                    if (i == stoi(time[1])) {
                        days += stoi(time[2]);
                    }
                    else {
                        days += isBigMonth(i);
                    }
                }
            }
            else {
                for (int i = 1; i <= stoi(time[1]); i++) {
                    if (i == stoi(time[1])) {
                        days += stoi(time[2]);
                    }
                    else {
                        days += isBigMonth(i);
                    }
                }
            }
        }
        // 計算相差年的天數
        int coutYearDays(int y1, int y2) const {
            int yearDays = 0;
            if (y1 > y2)
                swap(y1, y2);
            for (int i = y1 + 1; i < y2; i++) {
                if (isLeapYear(i)) {
                    yearDays += 366;
                }
                else {
                    yearDays += 365;
                }
            }
            return yearDays;
        }
        int operator-(const Date &d) const {
            int minYear = min(stoi(d.time[0]), stoi(time[0]));
            int minYearDays, maxYearDays;
            if (stoi(d.time[0]) == minYear) {
                minYearDays = d.days;
                maxYearDays = days;
            }
            else {
                minYearDays = days;
                maxYearDays = d.days;
            }
            if (isLeapYear(minYear))
                return coutYearDays(stoi(d.time[0]), stoi(time[0])) + (366 - minYearDays) + maxYearDays;
            else {
                return coutYearDays(stoi(d.time[0]), stoi(time[0])) + (365 - minYearDays) + maxYearDays;
            }
                
        }
        string toString() const {
            stringstream ss;
            if (time.size() != 3)
                return initialTime;
            ss << setw(4) << setfill('0') << time[0] << "/"
               << setw(2) << setfill('0') << time[1] << "/"
               << setw(2) << setfill('0') << time[2];
            return ss.str();
        }
        
};
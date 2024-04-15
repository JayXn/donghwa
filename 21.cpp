#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

class Time {
    private:
        string time, subtime, sec;
        int totalSec;
        vector<string> partTimes;
        int pos;
    public:
        Time(): time{"00:00:00"} {}
        Time(string t): time(t), pos(0) {
            toString();
            split();
            changeToSec();
        }
        void changeToSec() {
            totalSec = (stoi(partTimes[0]) * 3600) + (stoi(partTimes[1]) * 60) + stoi(partTimes[2]);
        }
        void split() {
            while ((pos = time.find(":"))    != string::npos) {
                subtime = time.substr(0, pos);
                partTimes.push_back(subtime);
                time.erase(0, pos + 1);
            }
            partTimes.push_back(time);
        }

        string toString() const {
            if (partTimes.size() != 3) return string("00:00:00");
            ostringstream oss;
            oss << setw(2) << setfill('0') << stoi(partTimes[0]) << ":"
                << setw(2) << setfill('0') << stoi(partTimes[1]) << ":"
                << setw(2) << setfill('0') << stoi(partTimes[2]);
            return oss.str();
        }
        int operator-(const Time &t) const {
            return abs(totalSec - t.totalSec);
        }
};
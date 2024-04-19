#include <iostream>
#include <sstream>
using namespace std;
class DateTime {
    private:
        Date date;
        Time time;
    public:
        DateTime(): date("1900/01/01"), time("00:00:00") {}
        DateTime(string str) {
            stringstream ss(str);
            string subDate, subTime;
            getline(ss, subDate, ' ');
            getline(ss, subTime);
            date = Date(subDate);
            time = Time(subTime);
        }

        string toString() const {
            return date.toString() + " " + time.toString();
        }
};
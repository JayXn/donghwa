#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Friend {
    public:
        int street, avenue;
        Friend(int s, int a): street(s), avenue(a) {}
};

class City {
    public:
        int maxStreet, maxAvenue, resultStreet, resultAvenue, friNum;
        vector <Friend> friends;
        vector <int> streets, avenues;


        City(int s, int a, int f): maxStreet(s), maxAvenue(a), friNum(f) {}
        void addFriend(Friend friend_obj) {
            friends.push_back(friend_obj);
        }

        void addStreetAvenue() {
            for (int i = 0; i < friends.size(); i++) {
                streets.push_back(friends[i].street);
                avenues.push_back(friends[i].avenue);
            }
        }

        void findPoint() {
            sort(streets.begin(), streets.begin() + friNum);
            sort(avenues.begin(),  avenues.begin() + friNum);

            if (friNum % 2 == 1) {
                resultStreet = streets[friNum / 2];
                resultAvenue = avenues[friNum / 2];
            }
            else {
                resultStreet = streets[(friNum - 1) / 2];
                resultAvenue = avenues[(friNum - 1) / 2];
            }
        }
};

int main() {
    int maxStreet, maxAvenue, friends, testcases, street, avenue;
    cin >> testcases;
    for (int i = 0; i < testcases; i++) {
        cin >> maxStreet >> maxAvenue >> friends;
        City city(maxStreet, maxAvenue, friends);
        for (int j = 0; j < friends; j++) {
            cin >> street >> avenue;
            city.addFriend(Friend(street, avenue));
        }
        city.addStreetAvenue();
        city.findPoint();
        cout << "(Street: " << city.resultStreet << ", Avenue: " << city.resultAvenue << ")" << endl;
    }

    return 0;   
}
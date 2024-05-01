#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class PokerCard {
    private:
        string suit;
        int face, suitPos, facePos;

    public:
        PokerCard(string s, int f) {
            suit = s;
            face = f;
            suitPos = findPos(s);
            facePos = findPos(to_string(f));
        }
        friend std::ostream &operator<<(std::ostream &out, const PokerCard &p) {
            out<<"["<<p.face<<" of "<<p.suit<<"]";
            return out;
        }
        int findPos(string s) {
            char suits[4][8] = {"club", "diamond", "heart", "spade"};
            char faces[13][3] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "1"};
            int pos;

            if (s.size() == 2 || s.size() == 1) {
                for (int i = 0; i < 13; i++) {
                    if (s == faces[i]) {
                        pos = i;
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < 4; i++) {
                    if (s == suits[i]) {
                        pos = i;
                        break;
                    }
                }
            }
            return pos;
        }
        bool operator>(PokerCard &b) {
            if (this->facePos > b.facePos) {
                return true;
            }
            else if (this->facePos == b.facePos && this->suitPos > b.suitPos) {
                return true;
            }
            return false;
        }

        bool operator<(PokerCard &b) {
            if (this->facePos < b.facePos) {
                return true;
            }
            else if (this->facePos == b.facePos && this->suitPos < b.suitPos) {
                return true;
            }
            return false;
        }
        bool operator==(PokerCard &b) {
            if (this->facePos == b.facePos && this->suitPos == b.suitPos) {
                return true;
            }
            return false;
        }
};
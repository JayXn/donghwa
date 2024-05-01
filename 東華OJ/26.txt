#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class PokerCard
{
public:
    PokerCard(string s, int f)
    {
        suit = s;
        face = f;
    }
    friend ostream &operator<<(ostream &out, const PokerCard &p)
    {
        out<<"["<<p.face<<" of "<<p.suit<<"]";
        return out;
    }

    //Please finish the comparison operator override
    //compare face first, if the same then compare suit 
    //請完成比較運算子多載
    //先比較 face ， face 一樣再比較 suit
    //1 > 13 > 12 > 11 > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3 > 2
    //spade > heart > diamond > club
    bool operator>(PokerCard& b) {
        if (face == 1 || b.face == 1) {
            if (face == b.face && suit[0] > b.suit[0]) return true;
            return face == 1 && b.face != 1;
        } 
        else if (face > b.face) {
            return true;
        } 
        else if (face == b.face && suit[0] > b.suit[0]) {
            return true;
        }
        return false;
    }

    bool operator==(PokerCard &b){
        return (face == b.face && suit == b.suit);
    }

    bool operator<(PokerCard &b){
        return !(*this > b) && !(*this == b);
    }

private:
    string suit;
    int face;
};

int main() {
    // 建立一些撲克牌物件
    PokerCard card1("spade", 7);
    PokerCard card2("heart", 10);
    PokerCard card3("club", 2);
    PokerCard card4("diamond", 13);
    PokerCard card5("spade", 7);

    // 使用比較運算子來比較撲克牌
    cout << "card1 > card2: " << (card1 > card2) << endl;
    cout << "card3 < card4: " << (card3 < card4) << endl;
    cout << "card1 == card5: " << (card1 == card5) << endl;

    // 建立一個撲克牌容器
    vector<PokerCard> deck = {card1, card2, card3, card4, card5};

    // 使用比較運算子排序撲克牌
    sort(deck.begin(), deck.end());  // 需要引入 <algorithm> 標頭檔案
    cout << "Sorted deck:" << endl;
    for (const auto &card : deck) {
        cout << card << " ";
    }
    cout << endl;

    return 0;
}
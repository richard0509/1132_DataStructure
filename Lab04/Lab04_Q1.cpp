#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
// 表示單張撲克牌的類別
class Card {
public:
    string colors;    // 儲存撲克牌的花色
    string rank;      // 儲存撲克牌的數值
    Card(string s, string r) : colors(s), rank(r)
    {
    }    // 建立constructor來初始化物件，當Card物件建立時，它會自動執行這個函式，並把s和r的值存入colors和rank
    void display() const
    {    // 顯示撲克牌的資訊
        cout << rank << " of " << colors << endl;
    }
};

// 實作Stack
class Stack {
private:
    vector<Card> stack;    // 表示stack是一個能存放Card類別物件的vector

public:
    void push(const Card& card)
    {
        stack.push_back(card);    // 使用vector的函式把牌夾到stack中
    }

    Card pop()
    {
        // 設定stack空的的提醒
        if (isEmpty()) {
            cout << "Stack is empty. Cannot pop.\n";
        }
        Card top = stack.back();    // 把最後一個（即最上面那個）的內容存到top中
        stack.pop_back();           // 把stack中已經儲存好的內容pop掉
        // cout << "pop!" << endl;
        return top;    // 回傳最上面的內容
    }

    bool isEmpty() const
    {
        // cout << "Stack is empty. No top element.\n";
        return stack.empty();    // 使用vector library的函式
    }
};

// 代表一副撲克牌的類別
class Deck {
private:
    vector<Card> cards;    // 存放未洗牌的撲克牌
    Stack shuffledDeck;    // 存放洗過的牌，用實作的stack來管理
public:
    Deck()
    {                                                                                           // 建立constructor來初始化物件
        string colors[] = {"Hearts", "Diamonds", "Clubs", "Spades"};                            // 儲存撲克牌的花色
        string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};    // 儲存撲克牌的數值

        // 利用迴圈將52張牌加入cards這個vector裡面
        for (int i = 0; i < 4; i++) {         // 四種花色
            for (int j = 0; j < 13; j++) {    // 13 種點數
                cards.push_back(Card(colors[i], ranks[j]));
            }
        }
    }

    // 洗牌(Hint:使用shuffle函數)
    void shuffleDeck()
    {
        // 假如沒有用rd = random_device{}，結果都會是一樣，固定同一組。e.g. 只用auto rng = default_random_engine{}; 的話就會是固定的數值。
        auto rd = random_device{};
        auto rng = default_random_engine{rd()};    // 用設定好的種子rd讓隨機數產生器產生亂數rng
        shuffle(begin(cards), end(cards), rng);    // 不同的rng會讓shuffle有不同的洗牌結果
        // 一直洗牌和pop，直到shuffledDeck是空的
        while (!shuffledDeck.isEmpty()) {
            shuffledDeck.pop();
        }
        // 清空shuffledDeck之後，再把所有洗好的牌存進shuffledDeck中。
        for (auto card : cards) {
            shuffledDeck.push(card);
        }
    }

    // 發牌
    void drawAllCards()
    {
        // 只要shuffledDeck不是空的，就逐一的把裡面的內容pop出來，在用寫好的diplay print出來
        while (!shuffledDeck.isEmpty()) {
            Card displayed_card = shuffledDeck.pop();
            displayed_card.display();
        }
    }
};

int main()
{
    Deck deck;             // 建立deck產生52張撲克牌
    deck.shuffleDeck();    // 進行洗牌並放入堆疊
    cout << "Shuffled deck:" << endl;
    deck.drawAllCards();    // 依序取出堆疊內的牌並顯示
    return 0;
}

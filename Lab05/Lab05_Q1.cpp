#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;
struct Player {     // 玩家結構體，包含名稱和分數
    string name;    // 玩家名稱
    int score;      // 玩家分數
};
class Card {    // 建立一個Card類別，用來表示單張撲克牌
public:
    string suit;    // 花色
    string rank;    // 點數
    Card()
    {
    }
    Card(string s, string r) : suit(s), rank(r)
    {
    }
    void display() const
    {
        cout << rank << " of " << suit << endl;
    }
};
class Deck {    // 牌組類別，負責生成和洗牌
private:
    Card cards[52];    // 52 張牌
    int index;         // 目前發牌索引
public:
    Deck() : index(0)
    {                                                                                           // 初始化牌組
        string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};                             // 四種花色
        string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};    // 13 張牌
        int k = 0;
        for (int i = 0; i < 4; i++) {         // 4 種花色
            for (int j = 0; j < 13; j++) {    // 13 種點數
                cards[k] = Card(suits[i], ranks[j]);
                k++;
            }
        }
    }

    void shuffleDeck()
    {    // 洗牌
        srand(time(0));
        for (int i = 51; i > 0; i--) {    // 從最後一張牌開始，向前遍歷
            int j = rand() % (i + 1);     // 生成隨機索引 j
            swap(cards[i], cards[j]);     // 交換牌組中的兩張牌
        }
    }
    // 取得指定位置的牌
    Card getCard(int i) const
    {
        return cards[i];
    }
};
// Queue 類別
class Queue {
private:
    vector<Card> deck;    // 用來存放卡牌的容器
    int Front;            // 指向牌堆的前端
    int Rear;             // 指向牌堆的尾端
    int capacity;         // 容器最大容量
public:
    // 建構函式
    Queue(int size) : Front(-1), Rear(-1), capacity(size)
    {
    }
    // 插入元素到佇列尾端
    void enqueue(Card card)
    {
        // 提示:檢查是否滿，如果滿了請印出提示語；如果不是滿的，
        // 則將card放入到deck(使用push_back)，然後將Rear指標移動
        if (isFull()) {
            cout << "佇列已滿！" << endl;
            return;
        }
        if (Front == -1) {    // 當第一次插入時，將 Front 設為 0，沒這樣設定的話，在初始化玩家的時候，就會因為cardDeck.front()會因為front == rear，所以拿到的Card.suit .name都會是空的，讓stoi產生錯誤。
            Front = 0;
        }
        deck.push_back(card);    // 把這張牌加到牌堆裡
        Rear++;                  // 移動rear來更新queue的狀態

        cout << card.rank << " of " << card.suit << endl;
    }
    // 從佇列中移除最前端元素
    void dequeue()
    {
        // 提示:檢查是否空，如是空的，印出提示語；如果不是空的，移動Front指標
        // 如果Front指標等於Rear，則重置Front和Rear，並清空deck
        //(可以使用clear函數)
        if (isEmpty()) {
            cout << "佇列為空！" << endl;
            return;
        }
        // 移動 Front 指標
        Front++;
        // 移除元素並打印
        // cout << "移除元素: " << deck[Front].rank << " of " << deck[Front].suit << endl;

        // 判斷是否所有元素已移除，佇列需要重置
        if (Front == Rear) {
            Front = -1;      // 重置 Front
            Rear = -1;       // 重置 Rear
            deck.clear();    // 用clear清空 deck
        }
    }
    Card front()            // 從queue取出牌的函式
    {                       // 獲取佇列最前端元素
        if (isEmpty()) {    // 檢查是否空
            cout << "牌堆為空，無法獲取最前端的牌！" << endl;
            return Card("", "");
        }
        return deck[Front];
    }
    bool isEmpty() const
    {                           // 判斷佇列是否為空
        if (Front == Rear) {    // front是頭，rear是尾，頭等於尾就代表中間沒有東西了。
            cout << "佇列為空！" << endl;
            return true;
        }
        else {
            return false;
        }
    }
    bool isFull() const
    {                                  // 判斷佇列是否已滿
        if (Rear == capacity - 1) {    // 到達queue size的最大值了。
            cout << "佇列已滿！" << endl;
            return true;
        }
        else {
            // cout << "佇列未滿！" << endl;
            return false;
        }
        // 提示:deck的大小和capacity的關係
    }
};
void initializeDeck(Queue& cardDeck)
{    // 初始化並洗牌
    Deck deck;
    cout << "初始牌堆: \n";
    for (int i = 0; i < 52; i++) {
        deck.getCard(i).display();    // 印出原始牌堆
    }
    deck.shuffleDeck();    // 洗牌
    cout << "\n洗牌後的牌堆: \n";
    for (int i = 0; i < 52; i++) {
        deck.getCard(i).display();    // 印出洗牌後的牌堆
    }
    // 提示:將洗好的牌放入牌堆
    // 使用for迴圈，將洗好的牌(deck.getCard(i))放入牌堆
    for (int i = 0; i < 52; i++) {
        cardDeck.enqueue(deck.getCard(i));    // 逐一的透過enqueue加入牌堆
    }
}
void initializePlayer(Player* player, string name, Queue& cardDeck)
{                           // 初始化玩家，發兩張牌
    player->name = name;    // 玩家名稱
    player->score = 0;      // 玩家分數
    cout << player->name << " 抽到的牌: ";

    for (int i = 0; i < 2; i++) {             // 發兩張牌
        Card drawnCard = cardDeck.front();    // 提示:從牌堆中取出一張牌，然後從牌堆中移除這張牌
        cardDeck.dequeue();
        // 從牌堆中抽一張牌並設定為 drawnCard
        // 抽完後把該張牌從牌堆中移除
        // 注意:卡牌變數的類型是Card，並且使用front抽牌

        cout << drawnCard.rank << " of " << drawnCard.suit << "  ";    // 印出抽到的牌

        // 計算點數
        if (drawnCard.rank == "A")
            player->score += 1;    // 計算A點數
        else if (drawnCard.rank == "J" || drawnCard.rank == "Q" || drawnCard.rank == "K")
            player->score += 10;    // 計算JQK點數
        else
            player->score += stoi(drawnCard.rank);    // 計算2-10點數 用stoi函式把字串轉為int

        if (i == 0)
            cout << "&  ";
    }
    cout << "\n";
    cout << player->name << " 玩家的初始分數: " << player->score << endl;    // 印出玩家的初始點數
}

void playerTurn(Player* player, Queue& cardDeck)
{    // 玩家回合
    char choice;
    // 大於21就直接輸了，不用再判斷要不要抽了。 cardDeck沒牌了也沒得抽
    while (player->score < 21 && !cardDeck.isEmpty()) {                                                          // 玩家小於21點且牌堆不為空
        cout << player->name << " 您的手牌分數目前為: " << player->score << " 要抽牌嗎？(h = 抽, s = 停) : ";    // 顯示選擇
        cin >> choice;                                                                                           // 輸入選擇

        if (choice == 'h') {    // 如果玩家選擇抽牌
            // 提示:從牌堆中取出一張牌，然後從牌堆中移除這張牌
            // 注意:卡牌變數的類型是Card，並且使用front抽牌
            Card newCard = cardDeck.front();    // 提示:從牌堆中取出一張牌，然後從牌堆中移除這張牌
            cardDeck.dequeue();

            // 計算點數
            if (newCard.rank == "A") {    // bonus A的判斷
                if (player->score < 11) {
                    player->score += 11;
                    cout << "抽到'A'因為玩家點數<11，因此增加11點！";
                }
                else
                    player->score += 1;    // 計算A點數
            }
            else if (newCard.rank == "J" || newCard.rank == "Q" || newCard.rank == "K")
                player->score += 10;    // 計算JQK點數
            else
                player->score += stoi(newCard.rank);    // 計算2-10點數
            // 印出抽到的牌和總點數
            cout << player->name << " 抽到: " << newCard.rank << " of " << newCard.suit << " 總分: " << player->score << endl;
            if (player->score > 21) {                               // 如果玩家大於21點
                cout << player->name << " 爆掉了！遊戲結束。\n";    // 玩家爆牌，莊家獲勝
                return;
            }
        }
        else if (choice == 's') {                                                    // 如果玩家選擇停牌
            cout << player->name << " 選擇停牌，總分: " << player->score << endl;    // 印出總點數
            break;
        }
        else {
            cout << "請輸入有效選項 (h = 抽, s = 停)！" << endl;    // 輸入無效
        }
    }
}

// 基本上跟playerturn一樣，只是把選擇的部分拿掉，加上跟上次lab一樣的設定，就是莊家至少會抽到17點以上。
void dealerTurn(Player* dealer, Queue& cardDeck)
{                                                          // 莊家回合
    while (dealer->score < 17 && !cardDeck.isEmpty()) {    // 莊家小於17點且牌堆不為空
        // 提示:從牌堆中取出一張牌，然後從牌堆中移除這張牌
        // 注意:卡牌變數的類型是Card，並且使用front抽牌
        Card newCard = cardDeck.front();    // 提示:從牌堆中取出一張牌，然後從牌堆中移除這張牌
        cardDeck.dequeue();
        if (newCard.rank == "A")
            dealer->score += 1;    // 計算A點數
        else if (newCard.rank == "J" || newCard.rank == "Q" || newCard.rank == "K")
            dealer->score += 10;    // 計算JQK點數
        else
            dealer->score += stoi(newCard.rank);    // 計算2-10點數
        // 印出抽到的牌和總點數
        cout << "莊家抽到: " << newCard.rank << " of " << newCard.suit << " 莊家目前總分: " << dealer->score << endl;
        if (dealer->score > 21) {                      // 如果莊家大於21點
            cout << "莊家爆了！玩家獲勝！" << endl;    // 玩家獲勝
            return;
        }
    }
}

// 判斷勝負
void determineWinner(Player* player, Player* dealer)
{
    if (player->score > 21)
        cout << player->name << " 爆了！莊家獲勝！\n";    // 玩家爆牌，莊家獲勝
    else if (dealer->score > 21 || player->score > dealer->score)
        cout << player->name << " 贏了！\n";    // 莊家爆牌或玩家點數大於莊家，玩家獲勝
    else if (player->score == dealer->score)
        cout << "平手！\n";    // 莊家與玩家點數相同，平手
    else
        cout << "莊家贏了！\n";
}

int main()
{
    srand(time(0));
    Queue cardDeck(52);          // 宣告牌堆
    initializeDeck(cardDeck);    // 初始化牌堆

    Player player, dealer;    // 宣告並初始化莊家以及玩家
    initializePlayer(&player, "玩家", cardDeck);
    initializePlayer(&dealer, "莊家", cardDeck);

    playerTurn(&player, cardDeck);
    if (player.score <= 21) {
        cout << "\n莊家回合...\n";
        dealerTurn(&dealer, cardDeck);
        determineWinner(&player, &dealer);    // 兩邊抽完都沒有爆的話，最後就用determinewinner來判斷輸贏（裡面也還是有檢查有沒有爆掉）
    }

    return 0;
}

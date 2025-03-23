#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

struct Player { /*玩家結構資料型態,包含 string 類型的玩家名稱以及
int 類型的玩家分數*/
    string name;
    int score;
};

int drawCard()
{
    return rand() % 10 + 1; /*發牌功能,呼叫一次發一張數值在 1-10
    之間的牌*/
}

// 初始化玩家
void initializePlayer(Player* player, string name)
{
    /*利用上面的結構變數,達到完成初始化玩家並且同時發兩張初始手牌
     */
    player->name = name;
    // 一開始玩家會被發兩張手牌，所以呼叫兩次drawCard，並把結果加到玩家的分數欄裡。
    player->score = drawCard() + drawCard();
}

// 顯示玩家分數
void displayScore(Player* player)
{
    /*顯示玩家當前的手牌點數*/
    cout << player->name << "目前手牌的點數為" << player->score << "分" << endl;
}

// 玩家回合
void playerTurn(Player* player)
{
    // 抽還是停的字元變數
    char choice;
    // 要能繼續抽牌的話，就代表還沒有超過21點，因此while的條件設定為小於21點。
    while (player->score < 21) {
        cout << "要抽牌嗎?(h = 抽, s = 停) : ";
        cin >> choice;
        if (choice == 'h') {
            // 抽牌提示;宣告一個變數再呼叫抽牌函數
            int new_draw = drawCard();
            /*將新抽到的手牌點數加上原本玩家擁有的手牌點數,並打印
            出來當前玩家手牌總點數*/
            // 進階規則的觸發條件，玩家要抽到A，且他的數字必須小於等於10，這樣從1點變成11點才會是對玩家有利的。
            // 假如不符合此條件，即用原本的方式判斷即可。
            if (new_draw == 1 && player->score <= 10) {
                new_draw = 11;
                player->score += new_draw;
                cout << "玩家抽到 'A'，因為玩家目前總分小於等於10，因此'A'變成11點,目前總分為: " << player->score << "分" << endl;
            }
            else {
                player->score += new_draw;
                cout << "玩家抽到" << new_draw << "點,目前總分: " << player->score << "分" << endl;
            }
            // 因為有抽牌，因此抽完要再判定有沒有在21點以內。
            if (player->score > 21) {
                cout << player->name << " 爆掉了!遊戲結束。\n";
                return;
            }
        }
        // 選擇不抽牌的情況。
        else if (choice == 's') {
            break;
        }
    }
}

// 莊家回合
void dealerTurn(Player* dealer)
{
    while (dealer->score < 17) {    // 莊家至少要到 17 點
        // 抽牌提示;宣告一個變數再呼叫抽牌函數
        int new_draw = drawCard();
        /*如果莊家點數小於 17,則至少持續增加手牌值到莊家手牌點數大
        於等於 17,並將莊家手牌點數打印出來*/
        while (dealer->score < 17) {
            // 跟上面一樣的進階規則判斷方式，只是從玩家變成莊家而已。
            new_draw = drawCard();
            if (new_draw == 1 && dealer->score <= 10) {
                new_draw = 11;
                dealer->score += new_draw;
                cout << "莊家抽到 'A'，因為莊家目前總分小於等於10，因此'A'變成11點,目前總分為: " << dealer->score << "分" << endl;
            }
            else {
                dealer->score += new_draw;
                cout << "莊家抽到" << new_draw << "點,目前總分: " << dealer->score << "分" << endl;
            }
        }
        // 一樣是有抽牌，就要再判斷有沒有超過21點。
        if (dealer->score > 21) {    // 如果莊家超過 21 點
            // cout << "莊家抽到" << "newCard" << "點,目前總分: " << dealer->score << endl;
            cout << "莊家爆了!玩家獲勝!" << endl;
            return;    // 遊戲結束
        }
    }
}

// 判斷勝負
// 判斷各種輸贏狀況
void determineWinner(Player* player, Player* dealer)
{
    if (player->score > 21) {
        cout << "你爆了!莊家獲勝!\n";
    }
    else if (dealer->score > 21 || player->score > dealer->score) {
        cout << "你贏了!!\n";
    }
    else if (player->score == dealer->score) {
        cout << "平手!\n";
    }
    else {
        cout << "莊家贏了!\n";
    }
}

// 主程式
int main()
{
    srand(time(0));                       // 產生隨機變數
    Player player, dealer;                // 宣告兩個Player結構的變數
    initializePlayer(&player, "玩家");    // 初始化玩家和莊家
    initializePlayer(&dealer, "莊家");
    displayScore(&player);       // 展示玩家初始化抽到的兩張牌的合
    playerTurn(&player);         // 玩家抽牌
    if (player.score <= 21) {    // 如果沒爆才讓莊家回合
        cout << "\n 莊家回合...\n";
        displayScore(&dealer);                // 展示莊家初始化抽到的兩張牌的合
        dealerTurn(&dealer);                  // 莊家抽牌
        determineWinner(&player, &dealer);    // 決出勝負
    }
    return 0;
}
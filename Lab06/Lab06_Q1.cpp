#include <cctype>
#include <cstring>
#include <iostream>
using namespace std;

// 定義 Stack 的節點結構
struct Node {
    char data;     // 存儲字符 (運算子或括號)
    Node* next;    // 指向下一個節點
};

// 使用 linked list 實作 Stack
class Stack {
private:
    Node* top;    // 指向堆疊頂端
public:
    Stack()
    {
        top = nullptr;
    }    // 初始化堆疊

    // Push 操作：將元素放入堆疊
    void push(char ch)
    {
        Node* newNode = new Node();    // 建立新節點
        newNode->data = ch;            // 儲存資料
        newNode->next = top;           // 新節點指向原本的頂端
        top = newNode;                 // 更新頂端為新節點
        // cout << ch << " 已推入堆疊\n";
    }

    // Pop 操作：移除並回傳頂端元素
    char pop()
    {
        if (top == nullptr) {    // 如果堆疊是空的
            // cout << "堆疊為空，無法取出元素。\n";
            return -1;    // 結束這次 pop()
        }

        char poppedchar = top->data;    // 取得頂端元素的值
        Node* temp = top;               // 用 temp 暫存目前頂端節點
        top = top->next;                // 更新頂端為下一個節點
        delete temp;                    // 釋放記憶體，刪除原頂端節點
        // cout << "已取出元素: " << poppedchar << endl;
        // cout << poppedchar;
        return poppedchar;
    }

    // Peek 操作：取得頂端元素但不移除
    char peek()
    {
        if (top == nullptr) {
            // cout << "堆疊為空，無法取出元素。\n";
            return -1;
        }

        return top->data;
    }

    // 判斷堆疊是否為空
    bool isEmpty()
    {
        if (top == nullptr) {    // 回傳空的狀況
            // cout << "堆疊為空，無法取出元素。\n";
            return true;
        }
        else {
            return false;
        }
    }
};

bool isoperator(char op)    // 判斷是不是operator i.e. + - * / ( )
{
    if (op != '+' && op != '-' && op != '*' && op != '/' && op != '(' && op != ')') {
        return false;
    }
    return true;
}
// 判斷運算子(加減乘除) 的優先順序
// 在stack裡的優先順序，因為'('在stack內跟在括號外的優先順序不一樣，所以有instack的跟outstack的。
int instackprecedence(char op)    // 越小越優先
{
    switch (op) {
    case '(':
        return 8;
    case '+':
        return 3;
    case '-':
        return 3;
    case '*':
        return 2;
    case '/':
        return 2;
    default:
        return -1;
    }
}

// 在stack外的優先順序
int outstackprecedence(char op)    // 越小越優先
{
    switch (op) {
    case '(':
        return 0;
    case '+':
        return 3;
    case '-':
        return 3;
    case '*':
        return 2;
    case '/':
        return 2;
    default:
        return -1;
    }
}
// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(const char* infix, char* postfix)
{
    Stack s;
    int i = 0;
    int count = 0;                // 用來記錄postfix字串目前儲存到哪
    while (infix[i] != '\0') {    // 到字串尾才會結束
        // 判斷吃到的char是哪類，總共有3類，第一種是不是operator的，第二種是')'，第三種是非')'的operator。
        if (!isoperator(infix[i])) {    // 第一種，不是operator的話，就直接存在postfix字串。
            postfix[count] = infix[i];
            count++;
        }
        else if (infix[i] == ')') {                      // 第二種，假如是右括號，要一直pop直到左括號。
            while (!s.isEmpty() && s.peek() != '(') {    // stack不是空的話，已經stack最上方的不是'('的話，會一直pop直到這兩個其中一個發生。
                postfix[count] = s.pop();
                count++;
            }
            s.pop();    // ************把'(' 丟掉 *****************
            // 因為')' 會把stack內，碰到'('之前的東西都pop到postfix裡，因此會剩'('在stack中的最上方，而這個'('是要和')'成對消失的。
        }
        // 第三種，剩下的operator只要判斷stack最上方的優先順序是不是小於等於準備要進stack的符號，假如是的話就要一直pop到stack空或是直到stack內的優先順序大於要進stack的符號。
        else {
            while (!s.isEmpty() && instackprecedence(s.peek()) <= outstackprecedence(infix[i])) {
                postfix[count] = s.pop();
                count++;
            }
            s.push(infix[i]);    // 當stack內的符號的優先順序終於比要進stack的符號低時或是stack空了，才把新的符號push到stack內
        }
        i++;                                                   // while index++
        cout << "目前的postfix輸出為: " << postfix << endl;    // 逐步地確認書出狀況。
    }
    // 把剩下的堆疊都 pop 出來，因為上面三種狀況並沒有一定會pop完stack才停止，第一種根本不會pop，第二種可能只會pop到'('為止，第三種可能只會pop到stack內的優先順序比stack外的還低時，
    while (!s.isEmpty() && infix[i] != '(') {
        postfix[count++] = s.pop();
    }
}

int main()
{
    char infix[100], postfix[100];    // 宣告輸出輸入string
    cout << "Enter an Infix expression: ";
    cin >> infix;    // 輸入中序表達式

    InfixToPostfix(infix, postfix);                           // 轉換為後序表達式
    cout << "最終Postfix expression: " << postfix << endl;    // 輸出後序表達式

    return 0;
}

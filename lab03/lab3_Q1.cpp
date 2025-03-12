#include <iostream>
using namespace std;

class Polynomial {
private:    // 宣告存放多項式係數的陣列
    int coefficients[10] = {0};

public:
    Polynomial(int coef[10])    // 初始化多項式，把收到的陣列的資料存到對應的位置
    {
        for (int i = 0; i < 10; i++) {
            coefficients[i] = coef[i];
        }
    }

    void display()    // 用來輸出的函式
    {
        bool firstTerm = true;
        //    先出來的方式: 1. 先看是不是最高次項：是的話 -> 就不會需要印 + 號，直接印出係數即可
        //                2. 接下來看是不是一次項，因為一次項就不需要印出 ^ 次方這個符號了，就印係數和x就好了
        //                3. 最後看是不是常數項，是常數項的話，只需要把數字印出來就好了，x 和 ^ 都不需要印了
        for (int i = 9; i >= 0; i--) {
            if (coefficients[i] != 0) {
                if (!firstTerm) {    // 處理最高次
                    cout << " + ";
                }
                cout << coefficients[i];    // 印出係數
                if (i > 0) {                // 只要不是常數項，就要印出x
                    cout << "x";
                }
                if (i > 1) {    // 只要不是常數項和一次項，都會用到次方的符號 ^
                    cout << "^" << i;
                }
                firstTerm = false;    // 處理完第一次項後，之後的每一項前面都要加上 + 號
            }
        }
        cout << endl;
    }

    // 把值代入，算出數值
    int eval(int x)
    {
        int result = 0;
        int power = 1;    // 一開始常數項 x^0 = 1
        for (int i = 0; i < 10; i++) {
            result += coefficients[i] * power;    // 計算當前項，係數*上一輪處理好的x項的值
            power *= x;                           // 計算下一輪的x^i的值
        }
        return result;
    }

    // 相加的函式
    Polynomial operator_add(const Polynomial &other)
    {
        int resultCoef[10] = {0};
        for (int i = 0; i < 10; ++i) {
            resultCoef[i] = coefficients[i] + other.coefficients[i];    // 相加就是把對應的次方項的係數相加即可
        }
        return Polynomial(resultCoef);
    }

    // 相乘的函式
    Polynomial operator_multi(const Polynomial &other)
    {
        int resultCoef[10] = {0};
        for (int i = 0; i < 10; ++i) {    // 從A的係數項開始乘B的常數項到最高次項，在逐漸地把A的次數往上加，就會把所有的項數都乘到了，有點像是九九乘法表
            for (int j = 0; j < 10 - i; ++j) {
                resultCoef[i + j] += coefficients[i] * other.coefficients[j];
            }
        }
        return Polynomial(resultCoef);
    }
};

int main()
{
    // 係數是從常數開始的
    // sample 1
    // int p1_coef[10] = {6, 3, 2, 5};
    // int p2_coef[10] = {2, 7, 1, 4};
    // sample 2
    // int p1_coef[10] = {3, 6, 2, 8, 7, 10};
    // int p2_coef[10] = {2, 7, 5, 6};
    // sample 3
    int p1_coef[10] = {3, 6, 2, 8, 7, 104};
    int p2_coef[10] = {3, 16, 12, 18, 8, 14, 267};

    // 還無法處理sparse，目前的方法只能處理次方數是連續的

    Polynomial p1(p1_coef);
    Polynomial p2(p2_coef);

    cout << "Polynomial 1: ";
    p1.display();
    cout << "Polynomial 2: ";
    p2.display();

    Polynomial p_sum = p1.operator_add(p2);
    cout << "Sum: ";
    p_sum.display();

    Polynomial p_prod = p1.operator_multi(p2);
    cout << "Product: ";
    p_prod.display();

    // sample 1
    // cout << "Evaluation p1(10): " << p1.eval(10) << endl;
    // cout << "Evaluation p2(10): " << p2.eval(10) << endl;
    // sample 2
    // cout << "Evaluation p1(3): " << p1.eval(3) << endl;
    // cout << "Evaluation p2(3): " << p2.eval(3) << endl;
    // sample 3
    cout << "Evaluation p1(5): " << p1.eval(5) << endl;
    cout << "Evaluation p2(5): " << p2.eval(5) << endl;
    return 0;
}

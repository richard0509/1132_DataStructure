#include <cmath>
#include <iostream>

using namespace std;

class Polynomial {
private:
    int* coefficients;
    int size;

public:
    // 建構函式，傳入多項式的大小和係數
    Polynomial(int size, int* coeffs)
        : size(size)
    {
        coefficients = new int[size];
        for (int i = 0; i < size; i++) {
            coefficients[i] = coeffs[i];
        }
    }

    // 解構函式，釋放動態記憶體
    ~Polynomial()
    {
        delete[] coefficients;
    }

    // 顯示多項式
    void print() const
    {
        bool firstTerm = true;
        for (int i = size - 1; i >= 0; --i) {
            if (coefficients[i] != 0) {
                if (!firstTerm) {
                    cout << (coefficients[i] > 0 ? " + " : " - ");
                }
                else {
                    if (coefficients[i] < 0) {
                        cout << "-";
                    }
                    firstTerm = false;
                }
                if (abs(coefficients[i]) != 1 || i == 0) {
                    cout << abs(coefficients[i]);
                }
                if (i > 0) {
                    cout << "x";
                }
                if (i > 1) {
                    cout << "^" << i;
                }
            }
        }
        cout << endl;
    }

    // 代入數字計算多項式的值
    int evaluate(int x) const
    {
        int result = 0;
        for (int i = size - 1; i >= 0; --i) {
            result = result * x + coefficients[i];
        }
        return result;
    }

    // 多項式加法
    Polynomial operator_add(const Polynomial& other) const
    {
        int maxSize = max(size, other.size);
        int* resultCoeff = new int[maxSize]{0};
        for (int i = 0; i < size; ++i) {
            resultCoeff[i] += coefficients[i];
        }
        for (int i = 0; i < other.size; ++i) {
            resultCoeff[i] += other.coefficients[i];
        }
        return Polynomial(maxSize, resultCoeff);
    }

    // 多項式乘法
    Polynomial operator_multiply(const Polynomial& other) const
    {
        int resultSize = size + other.size - 1;
        int* resultCoeff = new int[resultSize]{0};
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < other.size; ++j) {
                resultCoeff[i + j] += coefficients[i] * other.coefficients[j];
            }
        }
        return Polynomial(resultSize, resultCoeff);
    }
};

int main()
{
    int p1_coeffs[4] = {3, 6, 2, 5};
    Polynomial p1(4, p1_coeffs);
    cout << "Polynomial 1: ";
    p1.print();

    int p2_coeffs[4] = {2, 7, 1, 4};
    Polynomial p2(4, p2_coeffs);
    cout << "Polynomial 2: ";
    p2.print();

    Polynomial p_sum = p1.operator_add(p2);
    cout << "Sum of Polynomial 1 and Polynomial 2: ";
    p_sum.print();

    Polynomial p_prod = p1.operator_multiply(p2);
    cout << "Product of Polynomial 1 and Polynomial 2: ";
    p_prod.print();

    cout << "p1(2) = " << p1.evaluate(2) << endl;
    cout << "p2(2) = " << p2.evaluate(2) << endl;

    return 0;
}

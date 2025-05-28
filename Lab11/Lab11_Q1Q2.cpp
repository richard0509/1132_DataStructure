#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;

class item {
public:
    string name;
    int vdate;
    int popularity;
};

// 從文件中讀取數據並存入向量
vector<item> readFromFile(const string &filename)
{
    vector<item> input;
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return input;
    }
    // 上面這段都跟lab9提供的code一樣

    int n;
    file >> n;
    file.ignore();

    for (int i = 0; i < n; i++) {
        string line;
        getline(file, line);      // 一行一行的把txt檔的內容存入line裡
        stringstream ss(line);    // 用stringstream型態會比較好操作字串

        // 用一個暫時的item物件來儲存內容
        item temp;
        temp.name = "";    // 初始化name為長度為0的字串
        string word;
        // 逐一的把stringstream的內容輸入到word變數裡，stringstream 物件使用>>遇到空格會停下來
        while (ss >> word) {
            if (isdigit(word[0])) {         // 假如word的第一個字元是數字的話，就把內容轉成int型態存到vdate裡，
                temp.vdate = stoi(word);    // 確認是數字後，透過stoi轉成int，因為word是string type，要先轉成int type再存進vdate裡，
                ss >> temp.popularity;      // 因為我們的txt檔，在vdate後面一定是popularity，因此直接用ss >> 就行了，會幫我們自動轉成temp.popularity的型態
                break;                      // 換下一個字
            }
            else {                           // 不是數字的話，代表輸入是name
                if (!temp.name.empty()) {    // 會進入if的話，代表name裡面已經有內容了，代表這次之後還有先的內容要加進去，因此在中間加一個空格
                    temp.name += " ";
                }
                temp.name += word;
            }
        }
        input.push_back(temp);    // 把temp的內容儲存進vector input中
    }

    file.close();
    return input;
}

// 插入排序的function
vector<item> insertion_sort(vector<item> input)
{
    int i, j, insertion_date, insertion_pop;
    for (i = 1; i < input.size(); i++) {    // 注意是從i = 1開始，即第二個元素開始，因為是從第一個元素開始沒有意義，因為他只有一個元素，根本沒有排序的需要，因此從第二個元素開始
        // the number to insert
        insertion_date = input[i].vdate;
        insertion_pop = input[i].popularity;

        j = i - 1;    // 第一個要進行比較的數字 已經排好的array的最後一個元素

        // shift the number right if the sorted array is bigger than the insertion number
        item temp = input[i];
        // 排序的條件是期限小的往前排，假如期限一樣大的話，那就是熱門程度大的往前排
        // 因此是使用or，只要插入的元素的期限比較小就往前，期限一樣大的話，那插入元素的熱門程度就必須比較大才會往前排
        // 以插入元素的角度來看會比較好理解，因為他是不會變的，跟他比的元素會一直換
        while (j >= 0 && (insertion_date < input[j].vdate || (insertion_date == input[j].vdate && insertion_pop > input[j].popularity))) {
            input[j + 1] = input[j];
            j--;
        }
        input[j + 1] = temp;
    }
    return input;
}

int main()
{
    // string filename = "input1.txt";    // 請貼上input檔案的正確路徑
    // string filename = "input2.txt";    // 請貼上input檔案的正確路徑
    string filename = "input3.txt";                 // 請貼上input檔案的正確路徑
    vector<item> input = readFromFile(filename);    // 讀取數據

    input = insertion_sort(input);
    // 輸出排序結果
    cout << "商品排序: " << endl;
    for (item &s : input) {
        cout << s.name << endl;
    }

    return 0;
}

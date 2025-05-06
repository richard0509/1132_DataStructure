#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// 從文件中讀取數據並存入向量
vector<int> readFromFile(const string& filename)
{
    vector<int> arr;
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return arr;
    }

    string line;
    while (getline(file, line)) {    // 持續讀取整行內容
        stringstream ss(line);       // 創建字符串流
        string value;
        while (getline(ss, value, ',')) {    // 用逗號分隔值
            try {
                arr.push_back(stoi(value));    // 將字符串轉換為整數並存入向量
            }
            catch (exception& e) {
                cerr << "Invalid number format in file: " << value << endl;
            }
        }
    }

    file.close();
    return arr;
}

class MaxHeap {
public:
    vector<int> heap;    // 儲存Max Heap的元素

    // 建立Max Heap
    void buildMaxHeap(vector<int>& arr)
    {    // 建立Max Heap
        heap = arr;

        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {    // 從最後一個非葉子節點開始向上執行Max Heap
            heapify(i);
        }
    }

    void heapify(int i)
    {                             // 堆化函式（確保以 i 為根的子樹符合Max Heap性質）
        int largest = i;          // 假設當前節點是最大的
        int left = 2 * i + 1;     // 左子節點索引
        int right = 2 * i + 2;    // 右子節點索引

        // if判斷式，檢查左子節點是否為有效範圍且比當前節點(父節點)大
        // 如果判斷式成立，把largest設為left
        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        // if判斷式，檢查右子節點是否為有效範圍且比當前節點(父節點)大
        // 如果判斷式成立，把largest設為right
        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        // if判斷式，如果最大的不是父節點，交換並繼續堆化
        // 遞迴處理受影響的子樹
        if (largest != i) {
            int temp = heap[i];
            heap[i] = heap[largest];
            heap[largest] = temp;
            heapify(largest);
        }
    }

    // 顯示Heap的內容(使用BFS)
    void printHeap()
    {
        for (int val : heap) {     // 遍歷 Max Heap中的每個元素
            cout << val << " ";    // 輸出元素
        }
        cout << endl;
    }
};

class MiniHeap {
public:
    vector<int> heap;    // 儲存Max Heap的元素

    // 建立Max Heap
    void buildMiniHeap(vector<int>& arr)
    {    // 建立Max Heap
        heap = arr;

        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {    // 從最後一個非葉子節點開始向上執行Max Heap
            heapify(i);
        }
    }

    void heapify(int i)
    {                             // 堆化函式（確保以 i 為根的子樹符合Max Heap性質）
        int smallest = i;         // 假設當前節點是最大的
        int left = 2 * i + 1;     // 左子節點索引
        int right = 2 * i + 2;    // 右子節點索引

        // if判斷式，檢查左子節點是否為有效範圍且比當前節點(父節點)大
        // 如果判斷式成立，把largest設為left
        if (left < heap.size() && heap[left] < heap[smallest]) {
            smallest = left;
        }

        // if判斷式，檢查右子節點是否為有效範圍且比當前節點(父節點)大
        // 如果判斷式成立，把largest設為right
        if (right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }

        // if判斷式，如果最大的不是父節點，交換並繼續堆化
        // 遞迴處理受影響的子樹
        if (smallest != i) {
            int temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;
            heapify(smallest);    // 這個遞迴有時候會讓left right超過heap.size()，因此前面兩個if要做判斷，不然會出現segmentation fault
        }
    }

    // 顯示Heap的內容(使用BFS)
    void printHeap()
    {
        for (int val : heap) {     // 遍歷 Max Heap中的每個元素
            cout << val << " ";    // 輸出元素
        }
        cout << endl;
    }
};

int main()
{
    // 從文件讀取輸入元素
    string filename = "input1.txt";    // 請貼上input檔案的正確路徑
    // string filename = "input2.txt";    // 請貼上input檔案的正確路徑
    // string filename = "input3.txt";              // 請貼上input檔案的正確路徑
    vector<int> arr = readFromFile(filename);    // 讀取數據
    vector<int> arr2 = readFromFile(filename);

    if (arr.empty()) {                                     // 如果數據為空
        cerr << "No valid data found in file." << endl;    // 輸出錯誤信息
        return -1;
    }
    cout << "Input Array for Max Heap: ";    // 輸出讀取的數據
    for (int val : arr) {
        cout << val << " ";    // 輸出每個元素
    }
    cout << endl;

    if (arr2.empty()) {                                    // 如果數據為空
        cerr << "No valid data found in file." << endl;    // 輸出錯誤信息
        return -1;
    }
    cout << "Input Array2 for Mini Heap: ";    // 輸出讀取的數據
    for (int val : arr) {
        cout << val << " ";    // 輸出每個元素
    }
    cout << endl;
    cout << endl;

    MaxHeap maxHeap;              // 創建Max Heap對象
    maxHeap.buildMaxHeap(arr);    // 建立Max Heap

    MiniHeap miniHeap;               // 創建Max Heap對象
    miniHeap.buildMiniHeap(arr2);    // 建立Max Heap

    // 輸出Max Heap的內容
    cout << "Max Heap(By BFS): ";
    maxHeap.printHeap();

    cout << "Mini Heap(By BFS): ";
    miniHeap.printHeap();
    cout << endl;
    // system("pause");
    return 0;
}

#include <iostream>
using namespace std;

// ========================
// 樹的節點類別
// ========================
class TreeNode {
public:
    int data;           // 節點儲存的資料
    TreeNode* left;     // 指向左子節點
    TreeNode* right;    // 指向右子節點

    // 節點建構子：設定資料並初始化左右指標為空
    TreeNode(int val) : data(val), left(nullptr), right(nullptr)
    {
    }
};

// ========================
// 二元搜尋樹類別
// ========================
class BinarySearchTree {
private:
    TreeNode* root;    // 根節點指標

    // --- 私有的遞迴插入方法 ---
    TreeNode* insert(TreeNode* node, int val)
    {
        if (node == nullptr) {
            return new TreeNode(val);    // 找到插入位置，建立新節點
        }

        if (val < node->data) {
            node->left = insert(node->left, val);    // 插入左子樹
        }
        else if (val > node->data) {
            node->right = insert(node->right, val);    // 插入右子樹
        }
        // 如果 val == node->data，不插入（避免重複）

        return node;    // 回傳更新後的節點
    }

    // --- 私有的遞迴搜尋方法 ---
    bool search(TreeNode* node, int target)
    {
        if (node == nullptr)
            return false;

        if (node->data == target)
            return true;
        else if (target < node->data)
            return search(node->left, target);    // 繼續在左子樹找
        else
            return search(node->right, target);    // 繼續在右子樹找
    }

    // --- 私有的中序遍歷方法（左-根-右）---
    void inOrderTraversal(TreeNode* node)
    {
        if (node == nullptr)
            return;

        inOrderTraversal(node->left);     // 先走訪左子樹
        cout << node->data << " ";        // 印出目前節點的資料
        inOrderTraversal(node->right);    // 再走訪右子樹
    }

    // 要實作的部分
    // --- 私有的刪除方法 ---
    TreeNode* deleteNode(TreeNode* node, int val)
    {
        if (node == nullptr) {    // 以防輸入的是空指標
            return nullptr;
        }
        if (val < node->data) {    // 如果要刪的值比目前這個節點小,往左子樹找
            node->left = deleteNode(node->left, val);
        }
        else if (val > node->data) {    // 如果要刪的值比目前這個節點大,往右子樹找
            node->right = deleteNode(node->right, val);
        }
        else {    // 如果要刪的值等於目前這個節點,進入刪除的三種情況
            // 如果無子節點了，即是葉節點的話
            if (node->left == nullptr && node->right == nullptr) {
                delete node;       // 把此node刪除
                return nullptr;    // 刪掉後，回傳空指標更新上次呼叫的節點的內容
            }
            else if (node->left == nullptr) {    // 只有右節點的話
                TreeNode* temp = node->right;    // 保存現在節點的右子樹
                delete node;                     // 刪除現在的節點
                return temp;                     // 把保存下來的右子樹，接到現在這個被刪掉的節點的父節點，換句換說就是把這個節點原本街的子節點，接到這個節點的父節點上
            }
            else if (node->right == nullptr) {    // 只有左節點的話
                TreeNode* temp = node->left;      // 跟只有右節點的情況一樣，只是換成左子樹而已
                delete node;
                return temp;
            }
            else {                                                    // 兩邊都有節點
                TreeNode* succ = findMin(node->right);                // 依照這次題目的規定，在此練習中,碰到刪除的第三種情況時,使用從右邊遞補,取當前節點右子樹中最小的值來頂替。
                node->data = succ->data;                              // 因此先找到右子樹中最好的值，並儲存在succ變數裡，再把此節點的value值更新成succ的數值，數值更新後，再把succ刪除即可
                node->right = deleteNode(node->right, succ->data);    // 再用遞迴的方式，從右子樹找succ這個node，找到並刪除succ
            }
        }
        return node;
    }

    // 用這個找右子樹裡最小值，把這最小值接上來
    // --- 私有的找最小值方法 ---
    TreeNode* findMin(TreeNode* node)
    {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

public:
    // --- 建構子：初始化為空樹 ---
    BinarySearchTree() : root(nullptr)
    {
    }

    // --- 公開插入方法 ---
    void insert(int val)
    {
        root = insert(root, val);
    }

    // --- 公開搜尋方法 ---
    bool search(int target)
    {
        return search(root, target);
    }

    // --- 公開中序遍歷方法 ---
    void displayInOrder()
    {
        cout << "樹的中序遍歷（排序後）結果：" << endl;
        inOrderTraversal(root);
        cout << endl;
    }

    // --- 公開刪除方法 ---
    void deleteValue(int val)
    {
        if (!search(val)) {    // 要是bst裡面沒有這個value的狀況
            cout << "刪除失敗, value: " << val << " 不存在在bst裡" << endl;
            return;
        }
        root = deleteNode(root, val);    // value值存在的狀況
        cout << "刪除" << val << "成功" << endl;
    }
};

int main()
{
    BinarySearchTree bst;    // 建立一棵空的樹

    // 預設插入的資料
    int values[] = {7, 1, 4, 2, 8, 13, 12, 11, 15, 9, 5};
    int n = sizeof(values) / sizeof(values[0]);

    // 把資料插入樹中
    for (int i = 0; i < n; ++i) {
        bst.insert(values[i]);
    }

    // 讓使用者輸入要插入的鍵值
    int key;
    cout << "請輸入要搜尋/新增的鍵值：";
    cin >> key;

    if (bst.search(key)) {
        cout << "值 " << key << " 已存在樹中，不新增。" << endl;
    }
    else {
        cout << "值 " << key << " 不存在，已新增進樹中。" << endl;
        bst.insert(key);
    }

    // 顯示目前樹的中序遍歷結果
    bst.displayInOrder();

    // 讓使用者輸入要刪除的鍵值
    int deleteKey;
    cout << "請輸入要刪除的鍵值：";
    cin >> deleteKey;

    // 刪除節點
    bst.deleteValue(deleteKey);

    // 顯示刪除後的樹
    cout << "刪除後的樹（中序遍歷）：" << endl;
    bst.displayInOrder();

    return 0;
}

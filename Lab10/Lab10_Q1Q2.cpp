#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int EMPTY = -1;    // 用 NULL 代表沒有節點
class TreeNode {
public:
    int value;          // 節點值
    TreeNode* left;     // 左子節點
    TreeNode* right;    // 右子節點

    TreeNode(int val) : value(val), left(nullptr), right(nullptr)
    {
    }    // 初始化節點
};

class BinaryTree {
public:
    TreeNode* root;    // 樹根節點

    BinaryTree() : root(nullptr)
    {
    }

    TreeNode* buildTree(const vector<int>& arr)
    {    // 建立樹
        if (arr.empty() || arr[0] == EMPTY)
            return nullptr;

        queue<TreeNode**> q;            // 建立queue儲存待處理的節點指標
        root = new TreeNode(arr[0]);    // 建立根節點 (陣列第一個元素)
        q.push(&root);                  // 將根節點的指標加入queue

        size_t i = 1;    // 陣列索引
        while (!q.empty() && i < arr.size()) {
            TreeNode** nodePtr = q.front();    // 取出queue的第一個節點指標
            q.pop();                           // 將該節點從queue中刪除

            // 左子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->left = new TreeNode(arr[i]);    // 添加左子節點
                    q.push(&((*nodePtr)->left));                // 將左子節點的指標加入queue
                }
                i++;
            }
            // 右子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->right = new TreeNode(arr[i]);    // 添加右子節點
                    q.push(&((*nodePtr)->right));                // 將右子節點的指標加入queue
                }
                i++;
            }
        }
        return root;
    }

    void Depth_first_search(TreeNode* node)
    {    // 深度優先搜尋
        if (node == nullptr)
            return;
        cout << node->value << " ";         // 訪問當前節點的值
        Depth_first_search(node->left);     // 遞迴遍歷左子樹
        Depth_first_search(node->right);    // 遞迴遍歷右子樹
    }

    void Breadth_first_search(TreeNode* root)
    {
        if (root == nullptr)
            return;
        queue<TreeNode*> q;    // 建立queue儲存待處理的節點指標
        q.push(root);          // 將根節點的指標加入queue

        while (!q.empty()) {
            TreeNode* current = q.front();    // 取出queue的第一個節點指標
            q.pop();                          // 將該節點從queue中刪除
            cout << current->value << " ";
            if (current->left)
                q.push(current->left);    // 將左子節點的指標加入queue
            if (current->right)
                q.push(current->right);    // 將左子節點的指標加入queue
        }
    }

    // 用來得到最大的level，因為sumoflevel要是得到超過tree有的最大值的話，要輸出說超出範圍了。
    int getMaxLevel()
    {
        if (root == nullptr)
            return -1;

        int maxLevel = 0;
        queue<pair<TreeNode*, int>> q;    // 宣告一個queue q其內容是(treenode*, int)
        q.push({root, 0});                // 把root節點放到queue裡

        while (!q.empty()) {
            auto [node, level] = q.front();    // 把queue中的內容變成node, level，因為是有TreeNode* 和 int兩種型態，因此使用auto
            q.pop();

            maxLevel = max(maxLevel, level);    // 讓maxlevel更新

            // 把此node的left和和right child存進q裡，假如有的話
            if (node->left)
                q.push({node->left, level + 1});
            if (node->right)
                q.push({node->right, level + 1});
        }

        return maxLevel;
    }

    int sumofLevel()
    {
        if (root == nullptr)
            return 0;

        int targetLevel;
        cout << "請輸入要查詢的層數(從0開始): ";
        cin >> targetLevel;

        if (targetLevel < 0) {    // level一定會>= 0
            cout << "Invalid level." << endl;
            return 0;
        }
        // 先計算最大層數
        // 超出maxlevel則顯示超出範圍了
        int maxLevel = getMaxLevel();
        if (targetLevel > maxLevel) {
            cout << "超過樹高" << endl;
            return 0;
        }

        // 跟上面的maxlevel一樣，建立一個儲存(TreeNode*, int)的queue q
        // 只是把找maxlevel的部分改成是要是level是我們輸入的targetlevel的話，就增加sum的值
        queue<pair<TreeNode*, int>> q;    // pair: 節點 + 層數
        q.push({root, 0});

        int sum = 0;
        while (!q.empty()) {
            auto [node, level] = q.front();
            q.pop();

            if (level == targetLevel) {
                sum += node->value;
            }
            else if (level > targetLevel) {
                break;
            }

            // 如同maxlevel，讓left right child加入q裡面，假如存在的話
            if (node->left)
                q.push({node->left, level + 1});
            if (node->right)
                q.push({node->right, level + 1});
        }

        cout << "第" << targetLevel << "層的總和為: " << sum << endl;
        return sum;
    }

    // 用來計算該node的數值總和的方程式
    int subtreeSum(TreeNode* node)
    {
        if (!node) {
            return 0;
        }
        // 用遞迴的方式，找到該node的總和
        return node->value + subtreeSum(node->left) + subtreeSum(node->right);
    }

    // 透過subtreeSum得到總和後，用來比較左還右子樹總和比較大的function
    void compareSubtreeSums(TreeNode* node)
    {
        if (node == nullptr) {
            cout << "該節點不存在" << endl;
            return;
        }
        if (!node->left && !node->right) {
            cout << "該節點為葉節點" << endl;
            return;
        }

        // 透過subtreeSum function分別得到此節點的左右節點的總和
        int leftSum = subtreeSum(node->left);
        int rightSum = subtreeSum(node->right);

        cout << "左子樹總和: " << leftSum << endl;
        cout << "右子樹總和" << rightSum << endl;

        // 比較左右子樹總和誰比較大
        if (leftSum > rightSum) {
            cout << "左子樹總和較大" << endl;
        }
        else if (rightSum > leftSum) {
            cout << "右子樹總和較大" << endl;
        }
        else {
            cout << "左右子樹總和一樣大" << endl;
        }
    }

    // 透過此函數找到擁有使用者輸入的節點值的節點
    TreeNode* findNode(TreeNode* node, int target)
    {
        if (node == nullptr)
            return nullptr;

        // 找該節點
        if (node->value == target)
            return node;

        // 透過遞迴的方式，在左右子樹中找該節點值
        TreeNode* leftResult = findNode(node->left, target);
        if (leftResult)
            return leftResult;

        return findNode(node->right, target);
    }
};

int main()
{
    BinaryTree tree;
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, 10, 11, -1, -1};
    tree.buildTree(arr);

    cout << "DFS Result: ";
    tree.Depth_first_search(tree.root);
    cout << endl;

    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);
    cout << endl;

    // Q1
    tree.sumofLevel();

    // Q2
    int targetValue;
    cout << "輸入欲檢查的節點值： ";
    cin >> targetValue;

    // 先利用findNode函數找到擁有使用者輸入的節點值的節點
    TreeNode* targetNode = tree.findNode(tree.root, targetValue);
    // 再把此節點給compareSubtreeSums計算該節點的左右子樹的總和並比較
    tree.compareSubtreeSums(targetNode);
    return 0;
}

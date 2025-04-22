#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 樹的節點
class TreeNode {
public:
    int value;          // 節點的值
    TreeNode* left;     // 左子節點
    TreeNode* right;    // 右子節點

    TreeNode(int val) : value(val), left(nullptr), right(nullptr)
    {
    }    // 初始化節點
};

// 樹結構
class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr)
    {
    }    // 初始化樹

    // 用陣列構建二元樹
    TreeNode* buildTree(vector<int>& arr)
    {
        if (arr.empty())
            return nullptr;

        queue<TreeNode*> q;             // 建立queue儲存待處理的節點
        root = new TreeNode(arr[0]);    // 建立根節點 (陣列第一個元素)
        q.push(root);                   // 將根節點加入queue

        size_t i = 1;                         // 陣列索引
        while (!q.empty()) {                  //&& i < arr.size()
            TreeNode* current = q.front();    // 取出queue中的節點
            q.pop();

            // 添加左子節點
            if (i < arr.size()) {
                current->left = new TreeNode(arr[i]);
                q.push(current->left);    // 將左子節點加入queue
                i++;
            }

            // 添加右子節點
            if (i < arr.size()) {
                current->right = new TreeNode(arr[i]);
                q.push(current->right);    // 將右子節點加入queue
                i++;
            }
        }

        return root;
    }

    // 中序遍歷
    // 是用遞迴的方式，輸入node後，會先在用此node的left link在呼叫一次自己，然後會一直呼叫自己直到left link指到nullptr，在慢慢地拆掉這個遞迴
    // 回到上一層的遞迴，cout這個node的value，並執行right link的部分，會有跟left link一樣，會出現很多層遞迴，並在逐漸被拆掉
    // 一直重複這個從left link到link value到right link的步驟，直到回到最上方的root。
    void inorderTraversal(TreeNode* node)
    {
        if (node == nullptr)
            return;    // 如果節點為空，忽略

        inorderTraversal(node->left);     // 遍歷左子樹
        cout << node->value << " ";       // 訪問當前節點
        inorderTraversal(node->right);    // 遍歷右子樹
    }

    // postorder
    // 和上面inorder的基本一樣，只是把一直重複這個從left link到link value到right link的步驟，變成left link到right link到root的順序而已
    void postorderTraversal(TreeNode* node)
    {
        if (node == nullptr)
            return;    // 如果節點為空，忽略

        postorderTraversal(node->left);     // 遍歷左子樹
        postorderTraversal(node->right);    // 遍歷右子樹
        cout << node->value << " ";         // 訪問當前節點
    }

    // 找出輸入的node底下中，最大的數值，跟traversal很像，都是利用遞迴的方式，從root開始先找出左邊最大的，然後這個left link要找出左邊最大前，要先找出自己left link最大的值
    // left link找到之後，再利用一樣的方式找出right link的最大，最後再用一般的max先找出left link和right link中大的，再和node value比，得到最大值，
    // 底層的最大值找到後，會逐漸的拆解遞迴，慢慢地回傳到root，得到最上方的node的findMax
    // 最找出left link和right link最大時，最底層的node會有兩個都指到nullptr的link，而指到nullptr link就回傳climits中的最小值，所以回到上一層就可以得到node value
    // 為最大值，然後逐一的往上層慢慢解開遞迴，成功的得到root的最大值。
    int findMax(TreeNode* node)
    {
        if (node == nullptr)
            return INT_MIN;    // 表示這裡沒有值

        int leftMax = findMax(node->left);
        int rightMax = findMax(node->right);

        return max(node->value, max(leftMax, rightMax));
    }

    int findMaxLeftTree(TreeNode* node)
    {
        if (node == nullptr || node->left == nullptr)    // 根本沒有左子樹的話就回傳最小值，有的話再用findMax再找最大值。
            return INT_MIN;                              // 沒有左子樹

        return findMax(node->left);    // 對左子樹找最大值
    }

    int findMaxRightTree(TreeNode* node)
    {
        if (node == nullptr || node->right == nullptr)    // 同上面的left，沒有就回傳最小值，有的話再用findMax再找最大值。
            return INT_MIN;                               // 沒有左子樹

        return findMax(node->right);    // 對左子樹找最大值
    }
};

int main()
{
    BinaryTree tree;    // 宣告二元樹
    BinaryTree tree2;

    // 輸入陣列用於構建樹，NULL 表示空子節點
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    // 分配NULL給左右子樹，讓他們不是完整樹，但是我執行的結果就是會出現warning，並且把這個NULL當作是0在使用而已
    vector<int> arr2 = {1, 2, 3, 4, NULL, 5, NULL};

    tree.buildTree(arr);    // 建立樹
    tree2.buildTree(arr2);

    cout << "tree1:" << endl;
    // 中序遍歷輸出
    cout << "Inorder Traversal: ";
    tree.inorderTraversal(tree.root);
    cout << endl;
    cout << "Postorder Traversal: ";
    tree.postorderTraversal(tree.root);
    cout << endl;

    cout << "最大左子數值： " << tree.findMaxLeftTree(tree.root) << endl;
    cout << "最大右子數值： " << tree.findMaxRightTree(tree.root) << endl;
    cout << "整個tree最大值： " << tree.findMax(tree.root) << endl;

    cout << endl;

    cout << "tree2:" << endl;
    cout << "Inorder Traversal: ";
    tree.inorderTraversal(tree2.root);
    cout << endl;
    cout << "Postorder Traversal: ";
    tree.postorderTraversal(tree2.root);
    cout << endl;

    cout << "最大左子數值： " << tree2.findMaxLeftTree(tree2.root) << endl;
    cout << "最大右子數值： " << tree2.findMaxRightTree(tree2.root) << endl;
    cout << "整個tree最大值： " << tree2.findMax(tree2.root) << endl;
    return 0;
}

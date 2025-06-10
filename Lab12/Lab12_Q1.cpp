class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // 從後面開始比，因為從前面開始比會有之後的內容會被覆蓋掉的問題
        // i是nums1要比的index j是nums2要比的index k是nums1要擺資料的index
        int i = m - 1, j = n - 1, k = m + n - 1;
        // 只要nums1和nums2要比的內容的位置還沒更新到< 0(即不存在)就會繼續比
        // 比完後，使用到的數列的index(i or j)和nums1要擺的位置的index(k)都要往前一格
        while (i >= 0 && j >= 0) {
            // nums2要比的內容比較大，就把該index擺到nums1要擺資料的index
            if (nums2[j] >= nums1[i]) {
                nums1[k] = nums2[j];
                j--;
                k--;
            } else { // nums1比較大的情況
                nums1[k] = nums1[i];
                i--;
                k--;
            }
        }
        // 假如nums1的內容先用完的話，就把nums2剩下的內容填入nums1剩下的位置
        // nums2的內容先用完的話，不用特別處理，因為我們的答案是存在nums1，加上
        // 題目給的nums1和nums2是排序好的，因此nums2的內容先用完的話，剩餘的nums1內容
        // 已經是排序好的了，加上我們已經排好的後半段，整個就是排序好的答案了
        while (j >= 0) {
            nums1[k] = nums2[j];
            j--;
            k--;
        }
    }
};

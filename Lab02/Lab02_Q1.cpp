class Solution {
public:
    int findLucky(vector<int>& arr) {
        int count[501] = {0};
        int n = arr.size();
        int largest_num = -1;
        for (int num : arr) {
            count[num]++;
        }
        for (int num : arr) {
            if (num == count[num] && num > largest_num) {
                largest_num = num;
            }
        }
        return largest_num;
    }
};

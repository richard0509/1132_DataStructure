class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        // use two boolean variables to store the state of array
        bool isIncreasing = true, isDecreasing = true;
        // compare array's element and the next element from index 0
        // if every element in the array is smaller(bigger) than the next 
        // then this array is an decreasing(increasing) array, thus a 
        // monotonic array
        for (int i = 0; i < nums.size() - 1; i++) {

                if (nums[i] < nums[i + 1]) {
                    isIncreasing =  false;
                }

                if (nums[i] > nums[i + 1]) {
                    isDecreasing =  false;
                }
        }

        // an array only have to satisfy one of isDecreasing or isIncreasing
        // to be called a monotonic array
        return isDecreasing || isIncreasing;
    }
};

/* ---- Example for this solution ---- 
/* 1 2 3 4 5 6 7, n = 7, k = 2, start = 0
/* 6 7|3 4 5 1 2, n = 5, k = 2, start = 2
/* 6 7 1 2|5 3 4, n = 3, k = 2, start = 4
/* 6 7 1 2 3 5 5, n = 1, k = 2, start = 4
*/
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size(), start = 0;   
        while (n && (k %= n)) {
            for (int i = 0; i < k; ++i) {
                swap(nums[i + start], nums[n - k + i + start]);
            }
            n -= k;
            start += k;
        }
    }
};

class Solution1 {
public:
    void rotate(vector<int>& nums, int k) {
        if (nums.empty()) return;
        k = nums.size() - k % nums.size();          // number of shift
        reverse(nums.begin(), nums.begin() + k);    // reverse first half
        reverse(nums.begin() + k, nums.end());      // reverse second half
        reverse(nums.begin(), nums.end());          // reverse total array
    }
};
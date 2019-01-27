class Solution {
public:
    bool canJump(vector<int>& nums) {
        // greedy algorithm
        int rightmostIndex = nums[0];
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            if(i > rightmostIndex || rightmostIndex >= n - 1) {
                break;
            }
            rightmostIndex = max(rightmostIndex, i + nums[i]);
        }
        return rightmostIndex >= n - 1;
    }
};

class Solution {
public:
    bool canJump(vector<int>& nums) {
        // DP
        int n = nums.size();
        int dp[n];
        dp[0] = nums[0];
        for(int i = 1; i < n; ++i) {
            dp[i] = max(dp[i - 1], nums[i - 1]) - 1;
            if(dp[i] < 0) {
                return false;
            }
        }
        return true;
    }
};
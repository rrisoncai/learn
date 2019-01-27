class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(amount <= 0 || coins.size() <= 0) {
            return 0;
        }
        sort(coins.begin(), coins.end());
        int dp[amount + 1] = {0};

        for(int i = 0; i <= amount; ++i) {
            if(dp[i] == 0) {
                dp[i] = amount + 1;
            }
            for(int j = 0; j < coins.size(); ++j) {
                if(i - coins[j] == 0) {
                    dp[i] = 1;
                }
                else if(i - coins[j] > 0) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
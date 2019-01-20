class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int hash[26] = {0};
        int nTask = tasks.size();
        int totalTime = nTask;
        int maxCount = 0;
        int nMaxCount = 0;
        
        // store item frequency in hash table
        for(int i = 0; i < tasks.size(); ++i) {
            hash[tasks[i] - 'A']++;
            if(maxCount < hash[tasks[i] - 'A']) {
                maxCount = hash[tasks[i] - 'A'];
            }
        }
        
        // find number of items with maxCount
        for(int i = 0; i < 26; ++i) {
            if(hash[i] == maxCount) {
                nMaxCount++;
            }
        }
        
        totalTime = max((n + 1) * (maxCount - 1) + nMaxCount, nTask);
        return totalTime;
    }
};
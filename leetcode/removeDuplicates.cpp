class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty())
            return 0;
        int n = nums.size();
        int l = 1;
        int i = 0;
        for(i = 0; i < n - 1; ++i) {
            if(nums[i] != nums[i + 1]) {
                nums[l] = nums[i + 1];
                l++;
            }
        }
        return l;
    }
};
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int ret = nums[0];
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            if(ret != nums[i]) {
                count--;
                if(count <= 0) {
                    ret = nums[i];
                    count = 1;
                }
            }
            else {
                count++;
                if(count > n / 2) {
                    return ret;
                }
            }
        }
        return ret;
    }
};
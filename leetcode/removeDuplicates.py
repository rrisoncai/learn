class Solution:
    def removeDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        l = 1
        n = len(nums)
        if n == 0:
            return n
        for i in range(n-1):
            if nums[i] != nums[i+1]:
                nums[l] = nums[i+1]
                l += 1
        return l
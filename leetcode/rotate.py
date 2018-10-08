#  ---- Example for this solution ---- 
#  1 2 3 4 5 6 7, n = 7, k = 2, start = 0
#  6 7|3 4 5 1 2, n = 5, k = 2, start = 2
#  6 7 1 2|5 3 4, n = 3, k = 2, start = 4
#  6 7 1 2 3 5 5, n = 1, k = 2, start = 4

class Solution:
    def rotate(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        k %= n
        start = 0
        while n and k:
            for i in range(k):
                nums[n-k+i+start], nums[i+start] = nums[i+start], nums[n-k+i+start]
            n -= k
            start += k
            k %= n
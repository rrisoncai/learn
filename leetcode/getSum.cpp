class Solution {
public:
    int getSum(int a, int b) {
        // 两个整数a,b; a ^ b是无进位的相加
        // a&b得到每一位的进位
        // 让无进位相加的结果与进位不断的异或,直到进位为0；
        if(a & b) {
            return getSum((a&b) << 1, a ^ b);
        }
        else {
            return a | b;
        }
    }
};
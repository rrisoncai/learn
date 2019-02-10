class Solution {
public:
    bool isHappy(int n) {
        while(n != 4) {
            int sum = 0;
            while(n) {
                sum += (n % 10) * (n % 10);
                n = n / 10;
            }
            n = sum;
            if(n == 1) {
                return true;
            }
            if(n == 4) {
                return false;
            }
        }
        return false;
    }
};
class Solution {
public:
    double myPow(double x, int n) {
        if(x == 1.0 || x == 0.0) {
            return x;
        }
        double res = 1.0;
        for(int i = n; i != 0; i/=2) {
            if((i&1) == 1) {
                res *= x;
            }
            x *= x;
        }
        return (n > 0) ? res : 1.0 / res;
    }
};
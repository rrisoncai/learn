class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if(denominator == 1 || denominator == -1) {
            long div = (long) numerator / denominator;
            return to_string(div);
        }
        
        unordered_map<int, int> recur;
        long numer;
        long denom;
        string upper;
        string lower;
        string flag;
        
        numer = (long)numerator;
        denom = (long)denominator;
        flag = ((double)numer / denom >= 0) ? "" : "-";
        numer = abs(numer);
        denom = abs(denom);
        upper = flag + to_string(numer / denom);

        numer = numer % denom;
        numer *= 10;
        while(numer) {
            int ratio = numer / denom;
            int res = numer % denom;
            
            auto iter = recur.find(res);
            if(iter != recur.end() && lower[iter->second] == ratio + '0') {
                lower.insert(iter->second, 1, '(');
                lower += ")";
                break;
            }
            numer = res;
            numer *= 10;
            lower += to_string(ratio);
            recur[res] = lower.size() - 1;
        }
        

        if(!lower.empty()) {
            lower = "." + lower;
        }
        return upper + lower;
    }
};
//简单题考的就是如何处理边界条件、特殊样例
class Solution {
public:
    int lengthOfLastWord(const char *s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int len=0,wlen=0,i=0;
        if(*s=='\0')
            return 0;
        while(*(s+i)!='\0')
        {
            cout<<"p:"<<*(s+i)<<endl;
            if(*(s+i)==' ')
            {
                if(len)
                    wlen=len;
                len=0;
            }
            else
            {
                len++;
            }
            i++;
        }
        if(len)
            return len;
        else
            return wlen;
    }
};
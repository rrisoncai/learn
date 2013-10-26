//还是关于if else语句的问题，我们不但要注意到任何变量对if语句的影响。
//我开始是写成这样的if语句：
//if(A[i]!=A[i+1])
//{
    //repeat=1;
    //A[++pos]=A[i+1];
//}
//if(A[i]==A[i+1])
//{
    //repeat++;
    //if(repeat<3)
        //A[++pos]=A[i+1];
//}
//第一个if语句执行完毕后，A[i+1]==A[i]了，于是第二个if也被执行了。由之前的分情况讨论变成了顺序执行。
//if else语句还是比较好的选择，如果都用if的话，要时刻注意变量对if判定的影响。
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(n==0)return 0;
        int repeat=1,pos=0;
        for(int i=0;i<n;++i)
        {
            if(i+1<n)
            {
                if(A[i]!=A[i+1])
                {
                    repeat=1;
                    A[++pos]=A[i+1];
                }
                else
                {
                    repeat++;
                    if(repeat<3)
                        A[++pos]=A[i+1];
                }
            }
            //cout<<"pos:"<<pos<<" repeat:"<<repeat<<endl;
            //for(int j=0;j<=pos;++j)cout<<A[j]<<" ";cout<<endl;
        }
        return pos+1;
    }
};
//以为自己可以一遍写对的。
//还是改了半个小时才正确提交。
//二分查找倒是写对了，但是在判断相同数字的过程中出错了，改了好几遍，终于对了。
//自己的代码水平还要提高啊。

class Solution {
public:
    int BST(int A[],int low,int high,int target)
    {
        int pos=low+(high-low)/2;
        if(low>high)
            return -1;
        if(A[pos]==target)
            return pos;
        if(A[pos]>target)
            return BST(A,low,pos-1,target);
        if(A[pos]<target)
            return BST(A,pos+1,high,target);
    }
    vector<int> searchRange(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> vi;
        int start,end;
        start=end=-1;
        int pos=BST(A,0,n-1,target);
        int temp=pos;
        if(pos==-1)
        {
            vi.push_back(start);
            vi.push_back(end);
        }
        else
        {
            start=end=pos;
            //cout<<start<<" "<<end<<endl;
            while(pos>-1)
            {
                if(A[start]==A[pos])
                {
                    start=pos;
                }
                else
                {
                    break;
                }
                pos--;
                //cout<<pos<<endl;
            }
            pos=temp;
            while(pos<n)
            {
                if(A[end]==A[pos])
                {
                    end=pos;
                }
                else
                {
                    break;
                }
                pos++;
                //cout<<pos<<endl;
            }
            vi.push_back(start);
            vi.push_back(end);
        }
        return vi;
    }
};
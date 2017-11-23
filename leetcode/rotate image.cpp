//看了stackoverflow才知道怎么做-_-！ leetcode哟
//先转置再交换。
//狡猾的题目：
//矩阵size()==1的话，怎么处理？
//以前我写的是

//for(int i=0;i<matrix.size()-2;++i)
//结果出了错误。找了找错误，发现matrix.size()-2是个很大的值，才想到matrix.size()是unsigned int哎。SOGA
//关于两个数的交换，以前一直用XOR交换，觉得很高端。看了WiKi，发现除了嵌入式要节约外，其余地方最好不用。
//理由：1.现在的编译器可以优化利用临时变量的简单交换；2.因为有指令流水线的关系，XOR交换的效率要低于临时变量的交换。
//涨知识了。

class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        //transpose
        if(matrix.size()>1)
        {
            for(int i=0;i<=(int)matrix.size()-2;++i)
            {
                for(int j=i+1;j<=(int)matrix.size()-1;++j)
                {
                    swap(matrix[i][j],matrix[j][i]);
                }
            }
            //change columns
            for(int i=0;i<matrix.size();++i)
                for(int j=0;j<=matrix[i].size()/2-1;++j)
                {
                    int temp=matrix[i][j];
                    matrix[i][j]=matrix[i][matrix.size()-1-j];
                    matrix[i][matrix.size()-1-j]=temp;
                }
        }
    }
};
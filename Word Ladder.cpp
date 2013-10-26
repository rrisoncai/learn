//一开始想的就是用dijkstra。应该没错吧，但就是TLE。
//然后照着别人的方法改了一遍，终于过了。
//思考的还是太少了啊，没有考虑到dict非常大的情形，不管是拷贝还是遍历都是非常耗时的。
//虽然大体思路一样，数据结构的具体实现也会对结果产生非常大的影响啊。
//自身的计算量 word.size()×25×set.count()，我的算法的计算量dict.size()×dict.size()。
//悲剧
class Solution {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        dict.insert(start);
        dict.insert(end);
         
        int distance=0;
        queue<string> q,q_t;
         
        q.push(start);
        while(dict.size()>0&&!q.empty())
        {
            while(!q.empty())
            {
                string temp=q.front();
                q.pop();
                for(int i=0;i<temp.size();++i)
                {
                    for(int j='a';j<='z';++j)
                    {
                        if(j!=temp[i])
                        {
                            char t=temp[i];
                            temp[i]=j;
                            if(dict.count(temp)>0)
                            {
                                if(temp==end)
                                return distance+2;
                                q_t.push(temp);
                                dict.erase(temp);
                            }
                            temp[i]=t;
                        }
                    }
                }
            }
            swap(q_t,q);
            distance++;
        }
        return 0;
    }
};
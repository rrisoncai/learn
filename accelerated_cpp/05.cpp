#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>

using namespace std;

struct srt
{
    int a;
    int b;
};
list<int> extract(list<int>& v)
{
    list<int> odd;
    list<int>::iterator iter = v.begin();
    while(iter != v.end())
    {
        if(*iter < 60)
        {
            odd.push_back(*iter);
            iter = v.erase(iter);
        }
        else
            iter++;
    }
    return odd;
}
vector<int> extract(vector<int>& v)
{
    vector<int> odd;
    vector<int>::iterator iter  = v.begin();
    while(iter != v.end())
    {
        if( *iter < 60)
        {
            odd.push_back(*iter);
            iter = v.erase(iter);
        }
        else
            iter++;
    }
    return odd;
}
int main()
{
    vector<int> grade_vec;
    vector<int> fails_vec;
    list<int> grade_list;
    list<int> fails_list;
    vector<srt> vs;

    int *addr = 0;
    for(int i = 0; i < 2000; i++)
    {
        grade_vec.push_back(rand() % 100);

        struct srt tmp = {1};
        vs.push_back(tmp);
        if(addr != &(vs[0].a))
        {
            addr = &(vs[0].a);
            cout << i << "\t" << addr << "\t" << vs.size() << endl;
        }
        grade_list.push_back(rand() % 100);
    }

    clock_t start;
    double duration;
    
    start = clock();
    fails_vec = extract(grade_vec);
    duration = (clock() -start) / (double)CLOCKS_PER_SEC;
    cout << "duration: " << duration << endl;

    start = clock();
    fails_list = extract(grade_list);
    duration = (clock() -start) / (double)CLOCKS_PER_SEC;
    cout << "duration: " << duration << endl;
    /*
    for(int i = 0; i < fails.size(); ++i)
        cout << fails[i] << "\t";
    cout << endl;
    for(int i = 0; i < grade.size(); ++i)
        cout << grade[i] << "\t";
    cout << endl;
    */
    return 0;
}

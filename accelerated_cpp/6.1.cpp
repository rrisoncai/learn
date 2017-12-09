#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <random>

using namespace std;

typedef string::const_iterator iter;

iter search_sign(iter i, iter j)
{
    iter k;
    return k;
}
iter search_name(iter i, iter j)
{
    iter k;
    return k;
}
vector<string> find_urls(const string& s)
{
    vector<string> ret;

    iter i = s.begin();
    iter j = s.end();

    while(i != j)
    {
        // search for **://
        i = search_sign(i, j);

        if(i != j)
        {
            // search for name
            iter k = search_name(i, j);
            ret.push_back(string(i,k));
            i = k;
        }
    }
    return ret;
}

bool parlindromes(const string& str)
{
    return equal(str.begin(), str.end(), str.rbegin());
}

bool space(char c)
{
    return isspace(c);
}
bool not_space(char c)
{
    return !isspace(c);
}
vector<string> split(const string& str)
{
    typedef string::const_iterator iter;
    vector<string> ret;
    iter i = str.begin();

    while(i != str.end())
    {
        i = find_if(i, str.end(), not_space);
        iter j;
        j = find_if(i, str.end(), space);

        if(i != str.end())
            ret.push_back(string(i,j));
        i = j;
    }
    return ret;
}
int main()
{
    vector<string> vs;
    vs.push_back("Easy come easy go");
    vs.push_back("see you space");

    vector<string> vt;
    vt.push_back("good day!");
    vt.push_back("commander");

    copy(vt.begin(), vt.end(), back_inserter(vs));

    vt = split(vs[0]);
    for(int i = 0; i != vt.size(); ++i)
        cout << vt[i] << endl;
    cout << vs[1] << " is " << parlindromes(vs[1]) << endl;
    return 0;
}


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool not_space(char a)
{
    return !isspace(a);
}
bool space(char a)
{
    return isspace(a);
}
vector<string> split(const string& s)
{
    vector<string> ret;
    
    string::const_iterator i, j;
    i = s.begin();

    while(i != s.end())
    {
        i = find_if(i, s.end(), not_space);
        j = find_if(i, s.end(), space);

        if(i != s.end())
        {
            ret.push_back(string(i,j));
        }
        i = j;
    }
    return ret;
}
map<string, vector<int> > xref(
        istream& in,
        vector<string> find_words(const string&) = split)
{
    string line;
    int line_number = 0;
    map<string, vector<int> > ret;

    while(getline(in, line))
    {
        line_number++;

        vector<string> words = find_words(line);

        for(vector<string>::const_iterator it = words.begin();
                it != words.end();
                ++it)
        {
            ret[*it].push_back(line_number);
        }
    }
    return ret;
}

int main()
{
    string s = " can you hear me now?";
    map<string, int> counters;

    /*
    while(cin >> s)
    {
        ++counters[s];
    }
    */

    vector<string> words = split(s);
    for(int i = 0; i != words.size(); ++i)
    {
        cout << words[i] << endl;
    }
    /*
    for(map<string, int>::const_iterator it = counters.begin();
            it != counters.end(); ++it)
    {
        cout << it->first << "\t" << it->second << endl;
    }
    */
    return 0;
}

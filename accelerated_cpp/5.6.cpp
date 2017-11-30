#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& s)
{
    vector<string> words;
    int i = 0;
    int j = 0;
    while(i <= j && j != s.size())
    {
        if(s[j] != ' ')
        {
            j++;
        }
        else
        {
            if(i != j)
                words.push_back(s.substr(i,j-i));
            j++;
            i = j;
        }
    }
    return words;
}

int main()
{
    string str = "Can you hear me now?";
    vector<string> words;

    words = split(str);

    for(vector<string>::iterator iter = words.begin(); iter != words.end(); ++iter)
    {
        cout << *iter << endl;
    }
    return 0;
}

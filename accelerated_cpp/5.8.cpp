#include <iostream>
#include <string>
#include <vector>

using namespace std;

string::size_type width(const vector<string>& v)
{
    string::size_type length = 0;

    for(vector<string>::size_type i = 0; i != v.size(); ++i)
    {
        length = max(length, v[i].size());
    }
    return length;
}

vector<string> frame(const vector<string>& v)
{
    vector<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');

    // top border
    ret.push_back(border);

    // next line
    for(vector<string>::size_type i = 0; i != v.size(); ++i)
    {
        ret.push_back("* " + v[i] + string(maxlen - v[i].size(), ' ') + " *");
    }
    // bottom border
    ret.push_back(border);

    return ret;
}
int main()
{
    vector<string> passage;
    passage.push_back("The days are bright and filled with pain.");
    passage.push_back("Enclose me in your gentle rain.");
    passage.push_back("The time you ran was too insane.");

    vector<string> framed_passage;
    framed_passage = frame(passage);

    framed_passage.insert(framed_passage.end(), passage.begin(), passage.end());
    for(int i = 0; i != framed_passage.size(); ++i)
    {
        cout << framed_passage[i] << endl;
    }
    return 0;
}

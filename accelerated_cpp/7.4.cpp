#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef vector<string> RULE;
typedef vector<RULE> RULE_COLLECTION;
typedef map<string, RULE_COLLECTION> GRAMMAR;

void gen_aux(const GRAMMAR&, const string&, vector<string>&);

bool space(char c)
{
    return isspace(c);
}
bool not_space(char c)
{
    return !isspace(c);
}
vector<string> split(const string& s)
{
    string::const_iterator i, j;
    vector<string> ret;

    i = s.begin();

    while(i != s.end())
    {
        i = find_if(i, s.end(), not_space);
        i = find_if(i, s.end(), space);

        if(i != s.end())
        {
            ret.push_back(string(i, j));
        }
        i = j;
    }
    return ret;
}

GRAMMAR read_grammar(istream& in)
{
    GRAMMAR ret;
    string line;

    while(getline(in, line))
    {
        vector<string> entry = split(line);
        if(!entry.empty())
        {
            ret[entry[0]].push_back(RULE(entry.begin() + 1, entry.end()));
        }
    }
    return ret;
}

vector<string> gen_sentence(const GRAMMAR& g)
{
    vector<string> ret;
    gen_aux(g, "<sentense>", ret);
    return ret;
}

bool bracketed(const string& s)
{
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

void gen_aux(const GRAMMAR& g, const string& word, vector<string>& ret)
{
    if(!bracketed(word))
    {
        ret.push_back(word);
    }
    else
    {
        GRAMMAR::const_iterator it = g.find(word);
        if(it == g.end())
            throw logic_error("empty rule");

        const RULE_COLLECTION& c = it->second;

        const RULE& r = c[rand()];

        for(RULE::const_iterator i = r.begin(); i != r.end(); ++i)
            gen_aux(g, *i, ret);
    }
}
int main()
{
    return 0;
}

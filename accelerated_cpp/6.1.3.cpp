#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef string::const_iterator iter;

bool not_url_char(char c)
{
    static const string url_ch = "~;/?:@=&$-_.+!*'(),";
    const string str_tmp = "good day, commander";
    return !(isalnum(c) ||
            find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}
iter url_start(iter b, iter e)
{
    static const string sep = "://";
    iter i = b;
    
    while((i = search(i, e, sep.begin(), sep.end())) != e)
    {
        if(i != b && i + sep.size() != e)
        {
            iter beg = i;
            while(beg != b && isalpha(beg[-1]))
                --beg;
            if(beg != i && !not_url_char(i[sep.size()]))
                return beg;
        }
        i += sep.size();
    }
    return e;
}
iter url_end(iter b, iter e)
{
    return find_if(b, e, not_url_char);
}
vector<string> find_urls(const string& s)
{
    vector<string> ret;
    iter b = s.begin();
    iter e = s.end();

    while(b != e)
    {
        b = url_start(b, e);

        if(b != e)
        {
            iter end = url_end(b, e);
            ret.push_back(string(b, end));
            b = end;
        }
    }
    return ret;
}

int main()
{
    string str = "!!!http://www.google.com;;; ftp://www.baidu.com";
    vector<string> urls;
    
    urls = find_urls(str);

    for(int i = 0; i != urls.size(); ++i)
        cout << urls[i] << endl;

    return 0;
}

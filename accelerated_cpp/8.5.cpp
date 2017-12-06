#include <iostream>
#include <vector>
using namespace std;

template<class ITER, class X>
ITER my_find_if(ITER b, ITER e, const X& x)
{
    while(b != e)
    {
        if(*b == x)
            return b;
        b++;
    }
    return e;
}

int main()
{
    vector<int> vi;
    vi.push_back(1);
    vi.push_back(2);
    vi.push_back(4);
    vi.push_back(5);

    vector<int>::iterator i = vi.begin();
    vector<int>::iterator j = vi.end();
    cout << *my_find_if(i, j, 2) << endl;
    return 0;
}

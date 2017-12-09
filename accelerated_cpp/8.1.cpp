#include <vector>
using namespace std;

template<class Ran, class X>
bool binary_search(Ran begin, Ran end, const X& x)
{
    while(begin < end)
    {
        Ran mid = begin + (end - begin) / 2;
        if(*mid > x)
            end = mid;
        else if(*mid < x)
            begin = mid + 1;
        else
            return true;
    }
    return false;
}
template<class T>
T median(vector<T> v)
{
    typedef typename vector<T>::size_type vec_sz;

    vec_sz size = v.size();


    sort(v.begin(), v.end());

    vec_sz mid = size / 2;
    
    return size % 2 == 0 ? (v[mid] + v[mid - 1]) / 2 : v[mid];
}

template<class T>
T maxi(const T& left, const T& right)
{
    return left > right ? left: right;
}

template<class In, class X>
In find(In begin, In end, const X& x)
{
    while(begin != end && *begin != x)
        ++begin;
    return begin;
}

int main()
{
    vector<int> vi;
    vi.push_back(1);
    vi.push_back(2);
    vi.push_back(3);
    vi.push_back(4);
    int ret = median(vi);

    vector<int>::iterator i = vi.begin();
    vector<int>::iterator j = vi.end();
    vector<int>::iterator a = find(i, j, 2);
    return 0;
}

/*
 * using stable partition
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool pass(int i)
{
    return i % 2;
}
int main()
{
    vector<int> vi;
    vi.push_back(1);
    vi.push_back(2);
    vi.push_back(3);
    vi.push_back(4);
    vi.push_back(5);
    vi.push_back(6);
    vi.push_back(7);

    for(int i = 0; i != vi.size(); ++i)
        cout << vi[i] << "\t";
    cout << endl;
//    vector<int>::iterator iter = stable_partition(vi.begin(), vi.end(), pass);

    vi.erase(remove_if(vi.begin(), vi.end(), pass), vi.end());

    for(int i = 0; i != vi.size(); ++i)
        cout << vi[i] << "\t";
    cout << endl;
    return 0;
}

#include <iostream>
#include <memory>
#include <vector>
#include "vec.h"

using namespace std;

int main()
{
    Vec<int> a;
    
    for(int i = 0; i < 10; ++i)
        a.push_back(i);

    for(int i = 0; i < a.size(); ++i)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}

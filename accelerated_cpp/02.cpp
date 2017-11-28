#include <iostream>

using namespace std;

int main()
{
    float a = 1.2222344;
    cout << a << endl;
    
    streamsize prec = cout.precision(2);
    cout << a << endl;
    cout.precision(prec);
    return 0;
}

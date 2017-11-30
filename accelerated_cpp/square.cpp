#include <iostream>
#include <iomanip>

using namespace std;

double val[3] = {1, 2, 3};
double* f(void)
{
    return val;
}
int main()
{
    double d = f()[2];
    cout << d << endl;
    return 0;
}

/* accelerated cpp chap 3.2
 * computing median of grade using vector.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    double x;
    vector<double> homework;
    typedef vector<double>::size_type vec_sz;

    // invariant: homework contains all the homework grades read so far
    while(cin >> x)
    {
        homework.push_back(x);
    }
    vec_sz size = homework.size();
    
    if(size == 0)
    {
        cout << endl << "you must input your grade." <<
            "please try again." << endl;
        return 1;
    }

    sort(homework.begin(), homework.end());
    vec_sz mid = size / 2;
    double median;
    median = size % 2 == 0 ? (homework[mid] + homework[mid-1]) / 2
        : homework[mid];
    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

typedef double(*fp)(const int&);
fp get_fp();

size_t strlen(const char* p)
{
    size_t size = 0;
    while(*p++ != '\0')
        ++size;
    return size;
}
string letter_grade(double grade)
{
    static const double numbers[] =
    {
        97,94,90,87,84,80,77,74,70,60,0
    };
    static const char* const letters[] =
    {
        "A+","A","A-","B+","B","B-","C+","C","C-","D","F"
    };

    static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);

    for(size_t i = 0; i < ngrades; ++i)
        if(grade >= numbers[i])
            return letters[i];
    return "???";
}
int main()
{
    cout << letter_grade(99) << endl;

    int* p = new int[0];
    cout << p << endl;
    delete[] p;
    cout << p << endl;
    return 0;
}

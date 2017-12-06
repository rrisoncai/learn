#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student_info
{
    string name;
    double midterm;
    double final;
    vector<double> homework;

    istream& read(istream&);
    double grade() const;
};

istream& Student_info::read(istream& in)
{
    cout << "input name, mideterm and final:";
    in >> name >> midterm >> final;
    cout << "input homework:" << endl;
    double hw;
    while(cin >> hw)
        homework.push_back(hw);
    return in;
}
double Student_info::grade() const
{
    return 0.3 * midterm + 0.7 * final;
}
int main()
{
    Student_info s;
    s.read(cin);
    cout << s.grade() << endl;
    return 0;
}


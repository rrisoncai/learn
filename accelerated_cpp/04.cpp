#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student_info
{
    string name;
    double midterm;
    double final;
    vector<double> homework;
};

bool compare(const Student_info& x, const Student_info& y)
{
    return x.name < y.name;
}
double grade(double midterm, double final, vector<double> homework)
{
    double res;
    return res;
}
double grade(const Student_info& s)
{
    return grade(s.midterm, s.final, s.homework);
}
void read_hw(istream& is, vector<double>& vec)
{
}
istream& read(istream& is, Student_info& s)
{
    is >> s.name >> s.midterm >> s.final;
    read_hw(is, s.homework);
    return is;
}
double median(vector<double> vec)
{
    typedef vector<double>::size_type vec_sz;
    vec_sz size = vec.size();

    if(size == 0)
        throw domain_error("median of an empty vector");

    sort(vec.begin(), vec.end());

    vec_sz mid = size / 2;
    return size % 2 == 0 ? (vec[mid] + vec[mid-1]) / 2: vec[mid];
}
int main()
{
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;

    while(read(cin, record))
    {
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }
    sort(students.begin(), students.end(), compare);

    for(vector<Student_info>::size_type i = 0; i != students.size(); ++i)
    {
        try
        {
            double final_grade = grade(students[i]);
            streamsize prec = cout.precision();
        }catch(domain_error)
        {
        }
    return 0;
}

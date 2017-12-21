#include <algorithm>
#include "core.h"
#include "grade.h"

std::istream& read_hw(std::istream& in, std::vector<double>& hw);

std::string Core::name() const
{
    return n;
}

double Core::grade() const
{
    return ::grade(midterm, final, homework);
}

std::istream& Core::read_common(std::istream& in)
{
    std::cout << "read name midterm and final:" << std::endl;
    in >> n >> midterm >> final;
    return in;
}

std::istream& Core::read(std::istream& in)
{
    read_common(in);
    std::cout << "read homework:" << std::endl;
    read_hw(in, homework);
    return in;
}
std::istream& Grad::read(std::istream& in)
{
    read_common(in);
    std::cout << "read thesis:" << std::endl;
    in >> thesis;
    std::cout << "read homework:" << std::endl;
    read_hw(in, homework);
    return in;
}

double Grad::grade() const
{
    return thesis;
}
bool compare(const Core& c1, const Core& c2)
{
    return c1.name() < c2.name();
}

bool compare_Core_ptrs(const Core* cp1, const Core* cp2)
{
    return compare(*cp1, *cp2);
}

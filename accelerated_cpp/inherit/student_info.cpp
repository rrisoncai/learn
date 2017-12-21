#include <iostream>
#include "core.h"
#include "student_info.h"

std::istream& Student_info::read(std::istream& is)
{
    delete cp;
    char ch;
    std::cout << "input student type:undergrad [U],graduate [G]:" << std::endl;
    is >> ch;

    if(ch == 'U')
    {
        cp = new Core(is);
    }
    else
    {
        cp = new Grad(is);
    }

    return is;
}

Student_info::Student_info(const Student_info& s): cp(0)
{
    if(s.cp)
        cp = s.cp->clone();
}

Student_info& Student_info::operator=(const Student_info& s)
{
    if(&s != this)
    {
        delete cp;
        if(s.cp)
            cp = s.cp->clone();
        else
            cp = 0;
    }
    return *this;
}

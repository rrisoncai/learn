#ifndef CORE_H
#define CORE_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

double grade(int midterm, int final, std::vector<double> hw)
{
    return 60;
}
void read_hw(std::istream& in, std::vector<double> hw)
{
}
class Core
{
    friend class Student_info;
    protected:
    virtual Core* clone() const { return new Core(*this); }
    public:
        virtual ~Core() {};
        Core(): midterm(0), final(0) {}
        Core(std::istream& is) {read(is);}
        std::string name() const;
        virtual std::istream& read(std::istream&);
        virtual double grade() const;
    protected:
        std::istream& read_common(std::istream&);
        double midterm, final;
        std::vector<double> homework;

    private:
        std::string n;
};

class Grad: public Core
{
    protected:
        Grad* clone() const { return new Grad(*this); }
    public:
        Grad(): thesis(0) {}
        Grad(std::istream& is){ read(is); }
        double grade() const;
        std::istream& read(std::istream&);
    private:
        double thesis;
};

class Student_info
{
    public:
        Student_info(): cp(0) { if (s.cp) cp = s.cp->clone(); }
        Student_info(std::istream& is): cp(0) { read(is); }
        Student_info(const Student_info&);
        Student_info& operator=(const Student_info&);
        ~Student_info() { delete cp; }

        Student_info& operator=(const Student_info& s)
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
        std::istream& read(std::istream&);
        std::string name() const
        {
            if(cp)
                return cp->name();
            else
                throw std::runtime_error("uninit student");
        }
        double grade() const
        {
            if(cp)
                return cp->grade();
            else
                throw std::runtime_error("uninit student");
        }
        static bool compare(const Student_info& s1, const Student_info& s2)
        {
            return s1.name() < s2.name();
        }
    private:
        Core* cp;
};

istream& Student_info::read(istream& is)
{
    delete cp;
    char ch;
    is >> ch;
    
    if(ch == 'U')
        cp = new Core(is);
    else
        cp = new Grad(is);

    return is;
}
bool compare(const Core&, const Core&);
std::string Core::name() const {return n;}
double Core::grade() const
{
    return ::grade(midterm, final, homework);
}
std::istream& Core::read_common(std::istream& in)
{
    in >> n >> midterm >> final;
    return in;
}
std::istream& Core::read(std::istream& in)
{
    read_common(in);
    read_hw(in, homework);
    return in;
}
std::istream& Grad::read(std::istream& in)
{
    Core::read_common(in);
    in >> thesis;
    read_hw(in,Core::homework);
    return in;
}
double Grad::grade() const
{
    return std::min(Core::grade(), thesis);
}
#endif

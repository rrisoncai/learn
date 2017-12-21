#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Core
{
    public:
        Core(): midterm(0), final(0) { }
        Core(std::istream& is) { read(is); }

        std::string name() const;

        virtual std::istream& read(std::istream&);
        virtual double grade() const;

        virtual ~Core() { }

    protected:
        std::istream& read_common(std::istream&);
        double midterm, final;
        std::vector<double> homework;
        virtual Core* clone() const { return new Core(*this); }

    private:
        std::string n;
        friend class Student_info;
};

class Grad: public Core
{
    public:
        Grad(): thesis(0) { }
        Grad(std::istream& is) { read(is); }

        double grade() const;
        std::istream& read(std::istream&);
    private:
        double thesis;
        Grad* clone() const { return new Grad(*this); }
};

bool compare(const Core&, const Core&);
bool compare_Core_ptrs(const Core* cp1, const Core* cp2);

#endif

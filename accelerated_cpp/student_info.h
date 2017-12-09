#ifndef STUDENT_INFO_H_
#define STUDENT_INFO_H_

class Student_info
{
    public:
        Student_info();
        Student_info(std::istream&):midterm(0), final(0){}
        double grade() const;
        std::istream& read(std::istream&);
        std::string name() const {return n;}
        bool valid() const { return !homework.empty();}

    private:
        std::string n;
        double midterm;
        double final;
        std::vector<double> homework;
};

bool compare(const Student_info& x, const Student_info& y)
{
    return x.name() < y.name();
}
#endif

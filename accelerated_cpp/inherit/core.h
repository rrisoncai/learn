#ifndef CORE_H
#define CORE_H

class Core
{
    public:
        Core();
        Core(std::istream&);
        std::string name() const;
        std::istream& read(std::istream&);
        double grad() const;
    protected:
        std::istream& read_common(std::istream&);
        double midterm, final;
        std::vector<double> homework;

    private:
        std::string n;
};

class Grad: public Core
{
    public:
        Grad();
        Grad(std::istream&);
        double grade() const;
        std::istream& read(std::istream&);
    private:
        double thesis;
};
#endif

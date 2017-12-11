#ifndef STR_H_
#define STR_H_
#include <algorithm>
#include <cstring>
#include <cctype>
#include <iterator>
#include <iostream>
#include "vec.h"


class Str
{
    friend std::istream& operator>>(std::istream&, Str&);
    public:
        typedef Vec<char>::size_type size_type;
        typedef char* iterator;
        typedef const char* const_iterator;

        iterator begin() { return data.begin(); }
        const_iterator begin() const { return data.begin(); }
        iterator end() { return data.end(); }
        const_iterator end() const { return data.end(); }
        size_type size() const { return data.size(); }

        Str() { }
        Str(size_type n, char c): data(n, c) {}
        Str(const char* cp)
        {
            std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
        }
        template<class In> Str(In b, In e)
        {
            std::copy(b, e, std::back_inserter(data));
        }

        char& operator[](size_type i) { return data[i]; }
        const char& operator[](size_type i) const { return data[i]; }
        Str& operator+=(const Str& s)
        {
            std::copy(
                    s.data.begin(), 
                    s.data.end(), 
                    std::back_inserter(data));
            return *this;
        }

    private:
        Vec<char> data;
};

std::ostream& operator<<(std::ostream& os, const Str& s)
{
    for(Str::size_type i = 0; i != s.size(); ++i)
        os << s[i];
    return os;
}
std::istream& operator>>(std::istream& is, Str& s)
{
    s.data.clear();
    
    char c;
    while(is.get(c) && isspace(c));

    if(is)
    {
        do s.data.push_back(c);
        while(is.get(c) && !isspace(c));

        if(is)
            is.unget();
    }
    return is;
}
Str operator+(const Str& a, const Str& b)
{
    Str ret = a;
    ret += b;
    return ret;
}

bool operator==(const Str& a, const Str& b)
{
    return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin());
}
bool operator!=(const Str& a, const Str& b)
{
    return !(a == b);
}
#endif

#include <string>
#include <iostream>
struct Big{
    std::string number = "";
    Big(std::string value);
    Big(){}
    Big (const char* arr);
    Big operator=(const Big& ob);
    Big operator+(const Big& ob);
    Big operator-(const Big& ob);
    bool operator==(const Big& ob);
    bool operator!=(const Big& ob);
    Big operator++(); //prefix
    Big operator++(int); //postfix
    Big operator--(); //prefix --a
    Big operator--(int); //postfix  a--
    Big operator+=(const Big& ob);
    Big operator-=(const Big& ob);
    Big operator*(const Big& ob);
    Big operator*=(const Big& ob);
    bool operator<(const Big& ob);
    bool operator>(const Big& ob);
    bool operator<=(const Big& ob);
    bool operator>=(const Big& ob);
    Big pow(const Big& ob);
};


std::ostream& operator<<(std::ostream& out, const Big& ob);
std::istream& operator>>(std::istream& stream,Big& ob);
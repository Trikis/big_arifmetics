#include <string>
#include <iostream>
struct Big{
    std::string number = "";
    Big(std::string value);
    Big(){}
    Big (const char* arr);
    Big operator=(const Big ob);
    Big operator+(const Big ob);
    Big operator-(const Big ob);
    bool operator==(const Big ob);
    bool operator!=(const Big ob);
};


std::ostream& operator<<(std::ostream& out, const Big& ob);
std::istream& operator>>(std::istream& stream,Big& ob);
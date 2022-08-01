#include <iostream>
#include "big_arifmetics.cpp"
int main(){
    //Your code here
    /*
    Examples:
    Big a,b;
    a = "1";b = "23223";
    a * b; a *= 300;  a - b; a + b; a += b; a -= b; a += "-12"; a -= "-24"; a++; ++a; --a; a--;
    a == b ; a == "23" ' a != "24" ; a > "24"; a < "24"; a >= "24" ; a <= "24";
    a.pow("200000")
    */
    Big a = "10";
    std::cout<<a.pow("100");
    return 0;
}
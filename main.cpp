#include <iostream>
#include "big_arifmetics.cpp"
int main(){
    while (true){
        Big a,b;
        std::cout<<"Первое число: ";
        std::cin >> a;
        std::cout<<"Второе число: ";
        std::cin >>b;
        std::cout<<"\n\nState: "<<(a == b) << std::endl;
    }
}
#include "big_arifrmetics.h"
int maxi(int a, int b){
    if (a > b) return a;
    return b;
}
int char_to_int(char ch){
    if (ch == '0') return 0;
    if (ch == '1') return 1;
    if (ch == '2') return 2;
    if (ch == '3') return 3;
    if (ch == '4') return 4;
    if (ch == '5') return 5;
    if (ch == '6') return 6;
    if (ch == '7') return 7;
    if (ch == '8') return 8;
    return 9;
}
std::string int_to_string(int number){
    if (number == 0) return "0";
    if (number == 1) return "1";
    if (number == 2) return "2";
    if (number == 3) return "3";
    if (number == 4) return "4";
    if (number == 5) return "5";
    if (number == 6) return "6";
    if (number == 7) return "7";
    if (number == 8) return "8";
    return "9";
}
bool is_in_aplhabet(char symbol){
    const std::string alphabet = "-0123456789";
    for (auto elem : alphabet){
        if (elem == symbol) return true;
    }
    return false;
}

bool is_number(std::string value){
    if (value.size() == 0) return false;
    if (value.size() == 1 and value[0] == '-') return false;
    for (auto elem : value){
        if (!is_in_aplhabet(elem)) return false;
    }
    for (int index = 1; index < value.size(); ++index){
        if (value[index] == '-') return false;
    }
    
    if (value[0] != '-'){
        if (value.size() >=2 && value[0] == '0') return false;
    }
    else{
        if (value.size() >= 3 && value[1] == '0') return false;
    }
    return true;
}
std::string first_plus(std::string arg1,std::string arg2){
    std::string res = "";
    int max_size = maxi(arg1.size(),arg2.size());
    int iter1 = max_size - arg1.size(); int iter2 = max_size - arg2.size();
    for (int i = 0; i < iter1; ++i) arg1.insert(0,"0");
    for (int i =0 ; i < iter2; ++i) {
        arg2.insert(0,"0");
    }
    int dop = 0;
    for (int index = max_size - 1; index >= 0; --index){
        int tmp_res = char_to_int(arg1[index]) + char_to_int(arg2[index]) + dop;
        if (tmp_res >= 10) {
            dop =1;
            tmp_res -= 10;
            res.insert(0,int_to_string(tmp_res));
        }
        else{
            dop =0;
            res.insert(0,int_to_string(tmp_res));
        }
    }
    return res;
}
bool is_first_more(std::string arg1, std::string arg2){
    // return True(if abs(arg1) >= abs(arg2)) else return False
    if (arg1[0] == '-') arg1.erase(0,1);
    if (arg2[0] == '-') arg2.erase(0,1);
    if (arg1.size() > arg2.size()) return true;
    if (arg1.size() < arg2.size()) return false;
    for (int index = 0; index < arg1.size(); ++index){
        if (char_to_int(arg1[index]) > char_to_int(arg2[index])) return true;
        if (char_to_int(arg1[index]) < char_to_int(arg2[index])) return false;
    }
    return true;
}
std::string help_minus(std::string arg1, std::string arg2){
    //arg1 с плюсом , arg2 с минусом при этом abs(arg1) >= abs(arg2)
    int max_size = maxi(arg1.size(), arg2.size());
    int iter1 = max_size - arg1.size() ; int iter2 = max_size - arg2.size();
    for (int i = 0; i < iter1; ++i) arg1.insert(0,"0");
    for (int i =0 ; i < iter2; ++i) arg2.insert(0,"0");
    int dop = 0;
    std::string res;
    for (int index = max_size -1; index >=0; --index){
        int tmp_value = char_to_int(arg1[index]) - char_to_int(arg2[index]) - dop;
        if (tmp_value >= 0) {
            dop = 0;
            res.insert(0,int_to_string(tmp_value));
        }else{
            dop = 1;
            tmp_value +=10;
            res.insert(0,int_to_string(tmp_value));
        }
    }
    return res;
}
std::string minus(std::string arg1, std::string arg2){
    //arg1 plus , arg2 minus
    if (is_first_more(arg1, arg2)){
       return help_minus(arg1,arg2);
    }
    //arg2.erase(0,1);
    //arg1.insert(0,"-");
    return "-" + help_minus(arg2,arg1);
}
std::string to_normal(std::string answer){
    std::string res = "";
    if (answer[0] == '-') {res += "-"; answer.erase(0,1);}
    int pos = 0;
    while (pos != answer.size()){
        if (answer[pos] != '0') break;
        pos++;
    }
    if (pos == answer.size()) return "0";
    else {
        answer.erase(0,pos);
        res += answer;
    }
    return res;
}
std::ostream& operator<<(std::ostream& out, const Big& ob){
    out << ob.number;
    return out;
}
std::istream& operator>>(std::istream& stream,Big& ob){
    std::string str;
    stream >>str;
    ob = Big(str);
    return stream;
}

Big::Big(std::string value){
        if (is_number(value)) {
            number = to_normal(value);
        }
        else {
            std::cout<<"[-] Type Error\n";
            exit(1);
        }
}
Big::Big (const char* arr){
        std::string value(arr);
        if (is_number(value)) number = value;
           else {
               std::cout<<"[-] Type Error\n";
               exit(1);
           }
}
Big Big::operator=(const Big ob){
        number = ob.number;
        return *this;
}
Big Big::operator+(const Big ob){
    std::string arg1 = number;
    std::string arg2 = ob.number;
    std::string res = "";
    if (arg1[0] != '-' && arg2[0] != '-'){
        res = first_plus(arg1, arg2);
    }
    if (arg1[0] == '-' and arg2[0] == '-'){
        arg1.erase(0,1); arg2.erase(0,1);
        res = first_plus(arg1, arg2);
        res.insert(0,"-");
    }
    if (arg1[0] == '-' && arg2[0] != '-'){
        arg1.erase(0,1);
        res = minus(arg2,arg1);
    }
    if (arg1[0] != '-' && arg2[0] == '-'){
        arg2.erase(0,1);
        res = minus(arg1,arg2);
    }
    res = to_normal(res);
    return res;
}
Big Big::operator-(const Big ob){
    Big help;
    if (ob.number[0] == '-') help.number = ob.number.substr(1);
    else help.number = "-" + ob.number;
    return *this + help;
}
bool Big::operator==(const Big ob){
    return number == ob.number;
}
bool Big::operator!=(const Big ob){
    return number != ob.number;
}
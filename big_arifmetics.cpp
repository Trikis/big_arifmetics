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
    if (dop == 1) {
        res.insert(0,"1");
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
Big Big::operator=(const Big& ob){
        number = ob.number;
        return *this;
}
Big Big::operator+(const Big& ob){
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
Big Big::operator-(const Big& ob){
    Big help;
    if (ob.number[0] == '-') help.number = ob.number.substr(1);
    else help.number = "-" + ob.number;
    return *this + help;
}
bool Big::operator==(const Big& ob){
    return number == ob.number;
}
bool Big::operator!=(const Big& ob){
    return number != ob.number;
}
Big Big::operator++(){ //prefix
/*
Prefix:
    int a=0;

    int b=++a;    b=1,a=1
*/
  *this = *this + "1";
   return *this;
}
Big Big::operator++(int){
/*
  Postfix:
      int a=0;
      int b=a++;  // a=1,b=0 
*/
    Big tmp_ob = *this;
    *this = *this + "1";
    return tmp_ob;
}
Big Big::operator--(){ 
  *this = *this - "1";
   return *this;
}
Big Big::operator--(int){
    Big tmp_ob = *this;
    *this = *this - "1";
    return tmp_ob;
}
Big Big::operator+=(const Big& ob){
    *this = *this + ob;
    return *this;
}
Big Big::operator-=(const Big& ob){
    *this = *this - ob;
    return *this;
}
Big multiplication_to_odnozn(const Big ob1, const Big ob2){
    // ob1 - любое , ob2 однозначное число    ob1,ob2 > 0
    int mod = char_to_int(ob2.number[0]);
    if (mod == 0) return "0";
    Big res = "0";
    for (int i =0; i < mod; ++i){
        res += ob1;
    }
    res.number = to_normal(res.number);
    return res;
}
Big multiplication(const Big ob1, const Big ob2){
    //ob1 > ob2 > 0
    Big res = "0";
    int stepen = 0;

    for (int index = ob2.number.size() - 1; index >=0 ;--index){
        std::string tmp_str(1,ob2.number[index]);
        Big curr_digit = tmp_str;
        if (stepen == 0) res += multiplication_to_odnozn(ob1,curr_digit);
        else {
            Big tmp = multiplication_to_odnozn(ob1,curr_digit);
            tmp.number += std::string(stepen, '0');
            res += tmp;
        }
        stepen++;
    }
    res.number = to_normal(res.number);
    return res;
}
Big Big::operator*(const Big& ob){
    int znac = 1;
    Big arg1 = *this;
    Big arg2 = ob;
    if (arg1.number[0] == '-') {
        znac *= -1;
        arg1.number.erase(0,1);
    }
    if (arg2.number[0] == '-'){
        znac *= -1;
        arg2.number.erase(0,1);
    }
    if (is_first_more(arg2.number,arg1.number)){
        //Поменять arg1 и arg2 местами
        Big tmp  = arg1;
        arg1 = arg2;
        arg2 = tmp;
    }
    Big res = multiplication(arg1,arg2);
    if (znac == -1) res.number.insert(0,"-");
    res.number = to_normal(res.number);
    return res;
}
Big Big::operator*=(const Big& ob){
    *this = *this * ob;
    return *this;
}
bool Big::operator>(const Big& ob){
    if (*this == ob) return false;
    if (this->number[0] == '-' && ob.number[0] != '-') return false; // - +
    if (this->number[0] != '-' && ob.number[0] == '-') return true; // + -
    if (this->number[0] != '-' && ob.number[0] != '-' ){
        // - +
        if (is_first_more(this->number, ob.number)) return true;   
        else return false;
    }                                                                                    
    if (is_first_more(this->number, ob.number)) return false;
    else return true;                                         // - -
}
bool Big::operator<(const Big& ob){
    if (*this == ob) return false;
    return !(*this > ob);
}
bool Big::operator>=(const Big& ob){
    return !(*this < ob);
}
bool Big::operator<=(const Big& ob){
    return !(*this > ob);
}
Big Big::pow(const Big& ob){
    if (ob.number[0] == '-') {
        std::cout<<"[-] Степень не может быть меньше нуля";
        exit(1);
    }
    if (ob.number == "0") return "1";
    Big res = "1";
    Big arg = ob;
    while (arg.number != "0"){
        res *= *this;
        arg--;
    }
    res.number = to_normal(res.number);
    return res;
}
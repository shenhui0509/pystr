#include "../src/pystr.h"
#include <iostream>

int main(){
    std::string aa("dfahbdiqiqhuiruiquiq");
    pystr::PyStr pstr(std::begin(aa), std::end(aa));
    pystr::PyStr str("asdasdjs asdl hqoh aoihqoh");
    std::cout << str.capitilize() << std::endl;
    std::cout << pstr.capitilize() << std::endl;
    pstr.assign("aaaaa");
    std::cout << pstr.center(11, '*') << std::endl;
    std::cout << pstr.count("aa") << std::endl;
    std::cout << pstr.count("aaa") << std::endl;
    pstr.assign("1\t22\t333\t4444\t\t\t\t55555\t\n11\t222\t3333\t444444444444444444444444444444444\t\n");
    std::cout << pstr.expandtabs() << std::endl;
    pstr.assign("abcdbcdbcddd");
    str.assign("bcd");
    std::cout << pstr.find(str) <<std::endl;
    std::cout << std::string::npos << std::endl;
    pstr.assign("*");
    std::vector<pystr::PyStr> vec{"abc","bcd","cde","def"};
    std::cout << pstr.join(vec) << std::endl;
    std::cout << str.ljust(19,'*') << std::endl;
}

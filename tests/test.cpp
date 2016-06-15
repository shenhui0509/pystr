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
}

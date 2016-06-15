#include "pystr.h"
#include <iostream>

int main(){
    std::string aa("dfahbdiqiqhuiruiquiq");
    pystr::PyStr pstr(std::begin(aa), std::end(aa));
    pystr::PyStr str("asdasdjs asdl hqoh aoihqoh");
    std::cout << str.capitilize() << std::endl;
    std::cout << pstr.capitilize() << std::endl;
}

#ifndef PYSTR_H_
#define PYSTR_H_

#include <string>
#include <algorithm>
#include <cctype>
#include <initializer_list>
#include <iostream>

namespace pystr
{

class PyStr
{
private:
    std::string _m_str;
public:
    //ctors
    PyStr(){}
    PyStr(std::string const& str): _m_str(str){}
    PyStr(char const* c):_m_str(c){}
    PyStr(std::string&& str) noexcept :_m_str(str){}
    PyStr(std::initializer_list<char> il) : _m_str(il){}
    PyStr(const std::string& str, size_t pos, size_t len) : _m_str(str, pos, len){}
    PyStr(size_t n, char c) : _m_str(n,c){}
    PyStr(const char* s, size_t n) : _m_str(s,n){}
    template<class InputIterator>
    PyStr(InputIterator first, InputIterator last) : _m_str(first, last) {}

    //dctor
    ~PyStr(){}
    
    //assignments & operator =
    PyStr& assign(const std::string& str){
        _m_str.assign(str);
        return *this;
    }
    PyStr& assign(const PyStr& p_str){
        _m_str.assign(p_str.cpp_str());
        return *this;
    }
    PyStr& operator=(const std::string& str){
        return assign(str);
    }
    PyStr& operator=(const PyStr& p_str){
        return assign(p_str);
    }

    PyStr& assign(const std::string& str, size_t pos, size_t len){
        _m_str.assign(str, pos, len);
        return *this;
    }
    PyStr& assign(const PyStr& pStr, size_t pos, size_t len){
        _m_str.assign(pStr.cpp_str(), pos, len);
        return *this;
    }

    PyStr& assign(const char* s){
        _m_str.assign(s);
        return *this;
    }
    PyStr& operator=(const char* s){
        return assign(s);
    }

    PyStr& assign(const char* s, size_t n){
        _m_str.assign(s,n);
        return *this;
    }
    PyStr& assign(size_t n, char c){
        _m_str.assign(n,c);
        return *this;
    }
    template<class InputIterator>
    PyStr& assign(InputIterator first, InputIterator last){
        _m_str.assign(first, last);
        return *this;
    }

    PyStr& assign(std::initializer_list<char> il){
        _m_str.assign(il);
        return *this;
    }
    PyStr& operator=(std::initializer_list<char> il){
        return assign(il);
    }

    PyStr& assign(std::string&& s) noexcept{
        _m_str.assign(s);
        return *this;
    }
    PyStr& operator=(std::string&& s) noexcept{
        return assign(s);
    }

    PyStr& operator=(char c){
        _m_str = c;
        return *this;
    }

    const std::string& cpp_str() const noexcept{
        return _m_str;
    }
    friend std::ostream& operator<<(std::ostream& os, const PyStr& pStr){
        os << pStr.cpp_str();
        return os;
    }
    PyStr capitilize() const{
        std::string capitilized = _m_str;
        if(!capitilized.empty()){
            for_each(capitilized.begin(), capitilized.end(), tolower);
            if(islower(*capitilized.begin())){
                *capitilized.begin() = toupper(*capitilized.begin());
            }
        }
        return std::move(PyStr(std::move(capitilized)));
    }
};
} //namespace pystr
#endif

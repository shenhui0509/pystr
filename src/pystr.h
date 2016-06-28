#ifndef PYSTR_H_
#define PYSTR_H_

#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
#include <initializer_list>
#include <iostream>

namespace pystr
{

class PyStr
{
private:
    std::string _m_str;
    bool _range_process(size_t& _start, size_t& _end) {
        if(_start > _m_str.size() || (_end != std::string::npos && _end <= _start)) {
            return false;
        }
        if(_end == std::string::npos) {
            _end = _m_str.size();
        }
        return true;
    }
public:
    //ctors
    PyStr() {}
    PyStr(std::string const& str): _m_str(str) {}
    PyStr(char const* c): _m_str(c) {}
PyStr(std::string&& str) noexcept :
    _m_str(str) {}
    PyStr(std::initializer_list<char> il) : _m_str(il) {}
    PyStr(const std::string& str, size_t pos, size_t len) : _m_str(str, pos, len) {}
    PyStr(size_t n, char c) : _m_str(n, c) {}
    PyStr(const char* s, size_t n) : _m_str(s, n) {}
    template<class InputIterator>
    PyStr(InputIterator first, InputIterator last) : _m_str(first, last) {}

    //dctor
    ~PyStr() {}

    //assignments & operator =
    PyStr& assign(const std::string& str) {
        _m_str.assign(str);
        return *this;
    }
    PyStr& assign(const PyStr& p_str) {
        _m_str.assign(p_str.cpp_str());
        return *this;
    }
    PyStr& operator=(const std::string& str) {
        return assign(str);
    }
    PyStr& operator=(const PyStr& p_str) {
        return assign(p_str);
    }

    PyStr& assign(const std::string& str, size_t pos, size_t len) {
        _m_str.assign(str, pos, len);
        return *this;
    }
    PyStr& assign(const PyStr& pStr, size_t pos, size_t len) {
        _m_str.assign(pStr.cpp_str(), pos, len);
        return *this;
    }

    PyStr& assign(const char* s) {
        _m_str.assign(s);
        return *this;
    }
    PyStr& operator=(const char* s) {
        return assign(s);
    }

    PyStr& assign(const char* s, size_t n) {
        _m_str.assign(s, n);
        return *this;
    }
    PyStr& assign(size_t n, char c) {
        _m_str.assign(n, c);
        return *this;
    }
    template<class InputIterator>
    PyStr& assign(InputIterator first, InputIterator last) {
        _m_str.assign(first, last);
        return *this;
    }

    PyStr& assign(std::initializer_list<char> il) {
        _m_str.assign(il);
        return *this;
    }
    PyStr& operator=(std::initializer_list<char> il) {
        return assign(il);
    }

    PyStr& assign(std::string&& s) noexcept {
        _m_str.assign(s);
        return *this;
    }
    PyStr& operator=(std::string&& s) noexcept {
        return assign(s);
    }

    PyStr& operator=(char c) {
        _m_str = c;
        return *this;
    }

    const std::string& cpp_str() const noexcept {
        return _m_str;
    }
    friend std::ostream& operator<<(std::ostream& os, const PyStr& pStr) {
        os << pStr.cpp_str();
        return os;
    }

    //iterator
    std::string::iterator begin() noexcept {
        return _m_str.begin();
    }
    std::string::iterator end() noexcept {
        return _m_str.end();
    }
    std::string::const_iterator begin() const noexcept {
        return _m_str.cbegin();
    }
    std::string::const_iterator end() const noexcept {
        return _m_str.cend();
    }
    std::string::const_iterator cbegin() const noexcept {
        return _m_str.cbegin();
    }
    std::string::const_iterator cend() const noexcept {
        return _m_str.cend();
    }
    std::string::reverse_iterator rbegin() noexcept {
        return _m_str.rbegin();
    }
    std::string::reverse_iterator rend() noexcept {
        return _m_str.rend();
    }
    std::string::const_reverse_iterator crbegin() const noexcept {
        return _m_str.crbegin();
    }
    std::string::const_reverse_iterator crend() const noexcept {
        return _m_str.crend();
    }
    std::string::const_reverse_iterator rbegin() const noexcept {
        return _m_str.crbegin();
    }
    std::string::const_reverse_iterator rend() const noexcept {
        return _m_str.crend();
    }

    const size_t size() const noexcept {
        return _m_str.size();
    }

    const size_t length() const noexcept {
        return _m_str.length();
    }

    bool empty() const noexcept {
        return _m_str.empty();
    }
    //Python str methods
    PyStr capitilize() const {
        std::string capitilized = _m_str;
        if (!capitilized.empty()) {
            for_each(capitilized.begin(), capitilized.end(), tolower);
            if (islower(*capitilized.begin())) {
                *capitilized.begin() = toupper(*capitilized.begin());
            }
        }
        return std::move(PyStr(std::move(capitilized)));
    }

    PyStr center(const size_t& width, char fillchar = ' ') const {
        if (width <= _m_str.size()) {
            PyStr ret(_m_str);
            return std::move(ret);
        }
        PyStr ret(width, fillchar);
        auto _start = ret.begin();
        _start += (width - _m_str.size()) / 2;
        std::copy(_m_str.begin(), _m_str.end(), _start);
        return std::move(ret);
    }
    char& operator[](size_t pos) {
        return _m_str[pos];
    }
    const char& operator[](size_t pos) const {
        return _m_str[pos];
    }

    size_t count(const PyStr& sub, size_t _start = 0, size_t _end = std::string::npos) const noexcept {
        if (_start >= _m_str.size() || (_end != std::string::npos && _end <= _start)) {
            return 0;
        }
        if (_end == std::string::npos) {
            _end = _m_str.length();
        }
        size_t _cnt = 0, _sub_len = sub.length();
        size_t i = _start, j = 0;
        while (i <= _end - _sub_len) {
            for (j = 0; j < _sub_len; ++j) {
                if (sub[j] == _m_str[i + j])
                    continue;
                else
                    break;
            }
            if (j == _sub_len) {
                ++_cnt;
                i += _sub_len;
            } else {
                ++i;
            }
        }
        return _cnt;
    }

    bool endswith(const PyStr& suffix, size_t _start = 0, size_t _end = std::string::npos) const noexcept {
        if (suffix.empty())
            return true;
        if (_start >= _m_str.size() || (_end != std::string::npos && _end <= _start)) {
            return true;
        }
        if (_end == std::string::npos) {
            _end = _m_str.length();
        }
        --_end;
        auto _rit = suffix.rbegin();
        for (; _rit != suffix.rend(); ++_rit, --_end) {
            if (_m_str[_end] != *_rit) {
                return false;
            }
        }
        return true;
    }

    PyStr expandtabs(size_t tabsize = 8) {
        size_t i = 0;
        size_t _remain = 0;
        size_t _sub_len = 0;
        std::string _result;
        while(i < _m_str.size()) {
            _sub_len = 0;
            if(_m_str[i] == '\t') {
                _result += std::string(tabsize, ' ');
                ++i;
                continue;
            }
            if(_m_str[i] == '\n') {
                _result += '\n';
                ++i;
                continue;
            }
            while(i+_sub_len < _m_str.size() && _m_str[i+_sub_len] != '\t')
                ++_sub_len;
            if(_sub_len >= tabsize) {
                _remain = tabsize;
            } else {
                _remain = tabsize - _sub_len;
            }
            _result += _m_str.substr(i,_sub_len);
            _result += std::string(_remain,' ');
            i += (_sub_len+1);
        }
        return std::move(PyStr(std::move(_result)));
    }

    size_t find(const PyStr& sub, size_t _start = 0, size_t _end = std::string::npos) {
        if(!_range_process(_start, _end)) {
            return std::string::npos;
        }
        size_t i = 0, j = 0;
        while(i < _m_str.size() && j < sub.size()) {
            if(_m_str[i] == sub[j]) {
                ++i;
                ++j;
                continue;
            }
            if(_m_str[i] != sub[j]) {
                ++i;
                j = 0;
                continue;
            }
        }
        if(j == sub.size() && i <= _m_str.size()) {
            return i - j;
        } else {
            return std::string::npos;
        }
    }

    PyStr join(std::vector<PyStr> const& to_joined) {
        std::string result;
        auto _len = to_joined.size();
        auto i = _len - _len;
        for(; i < _len; ++i) {
            result += to_joined[i].cpp_str();
            if(i != _len - 1) {
                result += _m_str;
            }
        }
        return std::move(PyStr(std::move(result)));
    }

    PyStr ljust(size_t width, const char& fillchar = ' ') {
        if(width <= size()) {
            return *this;
        }
        std::string _raw = _m_str;
        size_t _remain = width - size();
        _raw += std::string(_remain, fillchar);
        return std::move(PyStr(std::move(_raw)));
    }

    PyStr rjust(size_t width, const char& fillchar = ' ') {
        if(width <= size()) {
            return *this;
        }
        std::string _raw = _m_str;
        size_t _remain = width - size();
        _raw = std::string(_remain, fillchar) + _raw;
return std::move(PyStr(std:move(_raw)));
    }
};
} //namespace pystr
#endif

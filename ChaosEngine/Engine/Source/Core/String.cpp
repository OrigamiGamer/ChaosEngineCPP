#include "Engine/Include/Core/String.h"

namespace chaos::core {

    // 构造

    String::String(const char* str)
        : _str(str ? str : "")
    {
    }

    String::String(const std::string& str)
        : _str(str)
    {
    }


    // 赋值

    String& String::operator=(const String& other)
    {
        if (this != &other) {
            _str = other._str;
        }
        return *this;
    }

    String& String::operator=(String&& other) noexcept
    {
        if (this != &other) {
            _str = std::move(other._str);
        }
        return *this;
    }

    String& String::operator=(const std::string& str)
    {
        _str = str;
        return *this;
    }

    String& String::operator=(const char* str)
    {
        _str = str ? str : "";
        return *this;
    }


    // 容量

    size_t String::size() const
    {
        return _str.size();
    }

    bool String::empty() const
    {
        return _str.empty();
    }


    // 访问

    char& String::operator[](size_t index)
    {
        return _str[index];
    }

    const char& String::operator[](size_t index) const
    {
        return _str[index];
    }

    char& String::at(size_t index)
    {
        return _str.at(index);
    }

    const char& String::at(size_t index) const
    {
        return _str.at(index);
    }

    const char* String::c_str() const
    {
        return _str.c_str();
    }

    const char* String::data() const
    {
        return _str.data();
    }


    // 修改

    String& String::append(const String& str)
    {
        _str.append(str._str);
        return *this;
    }

    String& String::append(const char* str)
    {
        _str.append(str ? str : "");
        return *this;
    }

    String& String::operator+=(const String& str)
    {
        return append(str);
    }

    String& String::operator+=(const char* str)
    {
        return append(str);
    }

    String& String::insert(size_t pos, const String& str)
    {
        _str.insert(pos, str._str);
        return *this;
    }

    String& String::erase(size_t pos, size_t count)
    {
        _str.erase(pos, count);
        return *this;
    }

    String& String::replace(size_t pos, size_t count, const String& str)
    {
        _str.replace(pos, count, str._str);
        return *this;
    }

    String String::substr(size_t pos, size_t count) const
    {
        return String(_str.substr(pos, count));
    }

    void String::clear()
    {
        _str.clear();
    }


    // 搜索

    size_t String::find(const String& str, size_t pos) const
    {
        return _str.find(str._str, pos);
    }

    size_t String::find(const char* str, size_t pos) const
    {
        return _str.find(str ? str : "", pos);
    }

    size_t String::rfind(const String& str, size_t pos) const
    {
        return _str.rfind(str._str, pos);
    }

    bool String::starts_with(const String& str) const
    {
        if (str.size() > _str.size()) return false;
        return _str.compare(0, str.size(), str._str) == 0;
    }

    bool String::contains(const String& str) const
    {
        return _str.find(str._str) != std::string::npos;
    }


    // 比较

    int String::compare(const String& str) const
    {
        return _str.compare(str._str);
    }


    // 运算符重载

    String operator+(const String& lhs, const String& rhs)
    {
        String result(lhs);
        result += rhs;
        return result;
    }

    bool operator==(const String& lhs, const String& rhs)
    {
        return lhs.compare(rhs) == 0;
    }

    bool operator!=(const String& lhs, const String& rhs)
    {
        return lhs.compare(rhs) != 0;
    }

    bool operator<(const String& lhs, const String& rhs)
    {
        return lhs.compare(rhs) < 0;
    }

    std::ostream& operator<<(std::ostream& os, const String& str)
    {
        return os << str.c_str();
    }

}

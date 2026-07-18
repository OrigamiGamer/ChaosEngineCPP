#include "chaos/log/OutputStream.h"


namespace chaos::log {


    OutputStream::OutputStream(std::string levelName)
        :
        levelName(levelName)
    {

    }


    inline OutputStream* OutputStream::push(std::string content)
    {
        this->_content.append(content);
        return this;
    }


    inline OutputStream* OutputStream::push(const char* content)
    {
        this->_content.append(content);
        return this;
    }


    inline OutputStream* OutputStream::push(float content)
    {
        this->_content.append(std::to_string(content));
        return this;
    }


    inline OutputStream* OutputStream::push(double content)
    {
        this->_content.append(std::to_string(content));
        return this;
    }


    inline OutputStream* OutputStream::push(int content)
    {
        this->_content.append(std::to_string(content));
        return this;
    }


    inline OutputStream* OutputStream::push(long content)
    {
        this->_content.append(std::to_string(content));
        return this;
    }


    template<typename T>
    OutputStream& OutputStream::operator<<(T* content)
    {
        this->push(content);
        return *this;
    }


    inline void OutputStream::clear()
    {
        this->_content.clear();
    }


}
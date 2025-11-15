#pragma once

#include "Class/Log/OutputStream.h"

namespace Chaos::Log {



    OutputStream::OutputStream(std::string typeName)
        :
        typeName(typeName)
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



    inline void OutputStream::clear()
    {
        this->_content.clear();
    }



}
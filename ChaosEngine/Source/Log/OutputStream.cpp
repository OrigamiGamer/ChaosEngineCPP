#pragma once

#include "Class/Log/OutputStream.h"

namespace Chaos::Log {



    OutputStream::OutputStream()
    {

    }



    OutputStream* OutputStream::push(std::string content)
    {
        this->_content.append(content);
        return this;
    }



    OutputStream* OutputStream::push(const char* content)
    {
        this->_content.append(content);
        return this;
    }



    OutputStream* OutputStream::push(float content)
    {
        this->_content.append(std::to_string(content));
        return this;
    }



    OutputStream* OutputStream::push(double content)
    {
        this->_content.append(std::to_string(content));
        return this;
    }



    OutputStream* OutputStream::push(int content)
    {
        this->_content.append(std::to_string(content));
        return this;
    }



    OutputStream* OutputStream::push(long content)
    {
        this->_content.append(std::to_string(content));
        return this;
    }



    void OutputStream::clear()
    {
        this->_content.clear();
    }



}
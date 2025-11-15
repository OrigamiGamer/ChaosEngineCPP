#pragma once

#include "Class/Log/Logger.h"

namespace Chaos::Log {



    Logger::Logger()
    {
        this->addType("INFO", Log::TypeColor::White);
        this->addType("WARN", Log::TypeColor::Yellow);
        this->addType("ERROR", Log::TypeColor::Red);
    }



    bool Logger::addType(std::string new_typeName, Log::TypeColor new_typeColor)
    {
        if (this->_typeMap.find(new_typeName) != this->_typeMap.end()) return false;    // typeName has been existed

        this->_typeMap.insert_or_assign(new_typeName, new_typeColor);
        return true;
    }



    bool Logger::removeType(std::string typeName)
    {
        auto _it = this->_typeMap.find(typeName);
        if (_it == this->_typeMap.end()) return false;  // can NOT find this typeName

        this->_typeMap.erase(_it);
        return true;
    }



    void Logger::print(Log::OutputStream& new_output)
    {
        Log::TypeColor _typeColor = this->_typeMap.at(new_output.typeName);
        this->_outputs.push_back(new_output);
        if (enabled) {
            std::cout
                << "\033[3"
                << _typeColor
                << "m"
                << "[" << new_output.typeName << "] "
                << new_output._content
                << "\033[0m"
                << std::endl;
        }
    }



}
#pragma once

#include "Class/Log/Logger.h"

namespace Chaos::Log {



    Logger::Logger()
    {

    }



    void Logger::print(Log::OutputStream& new_output)
    {
        this->_outputs.push_back(new_output);
        if (enabled) {
            std::cout << new_output._content << std::endl;
        }
    }



}
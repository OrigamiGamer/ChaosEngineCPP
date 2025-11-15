#pragma once

#include "Class/Log/Log.h"



namespace Chaos::Log {



    class Logger {
    private:
        std::vector<Log::OutputStream> _outputs;
        std::map<std::string, Log::TypeColor> _typeMap; // Default Types: white [INFO], yellow [WARN], red [ERROR]

    public:
        bool enabled = true;

        Logger();

        bool addType(std::string new_typeName, Log::TypeColor new_typeColor);

        bool removeType(std::string typeName);

        inline void print(Log::OutputStream& new_output);

        friend class Log::OutputStream;
    };



}
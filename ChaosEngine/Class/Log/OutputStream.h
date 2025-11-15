#pragma once

#include "Class/Log/Log.h"



namespace Chaos::Log {



    class OutputStream {
    private:
        std::string _content;

    public:
        std::string typeName;

        OutputStream(std::string typeName = "INFO");

        inline OutputStream* push(std::string content);
        inline OutputStream* push(const char* content);
        inline OutputStream* push(float content);
        inline OutputStream* push(double content);
        inline OutputStream* push(int content);
        inline OutputStream* push(long content);

        inline void clear();

        friend class Log::Logger;
    };



}
#pragma once

#include "Class/Log/Log.h"



namespace Chaos::Log {



    class OutputStream {
    private:
        std::string _content;

    public:
        OutputStream();

        OutputStream* push(std::string content);
        OutputStream* push(const char* content);
        OutputStream* push(float content);
        OutputStream* push(double content);
        OutputStream* push(int content);
        OutputStream* push(long content);

        void clear();

        friend class Log::Logger;
    };



}
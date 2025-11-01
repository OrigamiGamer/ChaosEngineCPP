#pragma once

#include "Class/Log/Log.h"



namespace Chaos::Log {



    class Logger {
    private:
        std::vector<Log::OutputStream> _outputs;

    public:
        bool enabled = true;

        Logger();

        void print(Log::OutputStream& new_output);

        friend class Log::OutputStream;
    };



}
#pragma once

#include "Class/Log/Log.h"



namespace Chaos::Log {



    class LoggerManager {
    public:
        static std::vector<Log::Logger*> s_loggers;

        LoggerManager();

        static bool registerLogger(Log::Logger* new_logger);

    };



}
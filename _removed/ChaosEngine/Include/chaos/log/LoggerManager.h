#pragma once

#include "chaos/log/log.h"


namespace chaos::log {



    class LoggerManager {
    public:
        static std::vector<log::Logger*> s_loggers;

        LoggerManager();

        static bool registerLogger(log::Logger* in_logger);

    };



}
#include "chaos/log/LoggerManager.h"

namespace chaos::log {



    std::vector<log::Logger*> LoggerManager::s_loggers;



    LoggerManager::LoggerManager()
    {

    }



    bool LoggerManager::registerLogger(log::Logger* in_logger)
    {
        if (!in_logger) return false;

        log::LoggerManager::s_loggers.push_back(in_logger);
        return true;
    }



}
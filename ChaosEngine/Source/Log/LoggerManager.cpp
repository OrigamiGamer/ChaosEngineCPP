#pragma once

#include "Class/Log/LoggerManager.h"

namespace Chaos::Log {



    std::vector<Log::Logger*> LoggerManager::s_loggers;



    LoggerManager::LoggerManager()
    {

    }



    bool LoggerManager::registerLogger(Log::Logger* new_logger)
    {
        if (!new_logger) return false;

        Log::LoggerManager::s_loggers.push_back(new_logger);
        return true;
    }



}
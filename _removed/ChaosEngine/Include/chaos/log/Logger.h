#pragma once

#include "chaos/log/log.h"


namespace chaos::log {


    class Logger {
    private:
        std::vector<log::OutputStream> _outputs;
        std::map<std::string, log::LevelColor> _typeMap; // Default Types: white [INFO], yellow [WARN], red [ERROR]

    public:
        bool enabled = true;

        Logger();

        bool addType(std::string levelName, log::LevelColor levelColor);

        bool removeType(std::string levelName);

        inline void print(log::OutputStream& in_output);

        friend class log::OutputStream;
    };


}
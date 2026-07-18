#include "chaos/log/Logger.h"


namespace chaos::log {


    Logger::Logger()
    {
        this->addType("INFO", log::LevelColor::White);
        this->addType("WARN", log::LevelColor::Yellow);
        this->addType("ERROR", log::LevelColor::Red);
    }


    bool Logger::addType(std::string levelName, log::LevelColor levelColor)
    {
        if (this->_typeMap.find(levelName) != this->_typeMap.end()) return false;    // the type name has already existed

        this->_typeMap.insert_or_assign(levelName, levelColor);
        return true;
    }


    bool Logger::removeType(std::string levelName)
    {
        auto _it = this->_typeMap.find(levelName);
        if (_it == this->_typeMap.end()) return false;  // cannot find this levelName

        this->_typeMap.erase(_it);
        return true;
    }


    void Logger::print(log::OutputStream& in_output)
    {
        log::LevelColor _levelColor(log::LevelColor::White);  // default log type color

        auto _it = this->_typeMap.find(in_output.levelName);
        if (_it != this->_typeMap.end()) {
            _levelColor = _it->second;
        }
        else {
            log::OutputStream _out;
            _out.levelName = "WARN";
            _out.push("Unknown log type -> \"");
            _out.push(in_output.levelName);
            _out.push("\"");
            this->print(_out);
        }

        this->_outputs.push_back(in_output);
        if (enabled) {
            std::cout
                << "\033[3"
                << static_cast<int>(_levelColor)
                << "m"
                << "[" << in_output.levelName << "] "
                << in_output._content
                << "\033[0m"
                << std::endl;
        }
    }


}
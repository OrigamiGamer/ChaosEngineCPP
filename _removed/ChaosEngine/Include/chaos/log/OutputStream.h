#pragma once

#include "chaos/log/log.h"


namespace chaos::log {



    class OutputStream {
    private:
        std::string _content;

    public:
        std::string levelName;

        OutputStream(std::string levelName = "INFO");

        inline OutputStream* push(std::string content);
        inline OutputStream* push(const char* content);
        inline OutputStream* push(float content);
        inline OutputStream* push(double content);
        inline OutputStream* push(int content);
        inline OutputStream* push(long content);

        template<typename T>
        OutputStream& operator<<(T* content);

        inline void clear();

        friend class log::Logger;
    };



}
#ifndef LOGGER_H
#define LOGGER_H

#pragma once
#include "../singleton/singleton.h"

namespace LTF
{

    class Logger
    {
    public:
        enum class Level
        {
            DEBUG = 0,
            INFO = 1,
            WARN = 2,
            ERROR = 3,
            FATAL = 4,
        };

    private:
        friend class Singleton<LTF::Logger>;

    private:
        // CTORS
        Logger();
        Logger(const Logger& rhs) = delete;
        Logger& operator=(const Logger& rhs) = delete;
        ~Logger();

    public:
    };
};

#endif // LOGGER_H

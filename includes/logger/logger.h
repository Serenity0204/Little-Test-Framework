#ifndef LOGGER_H
#define LOGGER_H

#pragma once
#include "../singleton/singleton.h"
#include <string>

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

        struct Info
        {
        public:
            std::string function;
            std::string file;
            int line;
            Info(const std::string& function = "", const std::string& file = "", int line = 0)
            {
                this->function = function;
                this->file = file;
                this->line = line;
            }
        };

    private:
        friend class Singleton<LTF::Logger>;

    private:
        // CTORS
        Logger();
        Logger(const Logger& rhs) = delete;
        Logger& operator=(const Logger& rhs) = delete;
        ~Logger();

    private:
        // std::map<std::string, std::vector<std::string>> m_messages;

    public:
        void debug(const std::string& message, const Info& info)
        {
        }
    };
};

#endif // LOGGER_H

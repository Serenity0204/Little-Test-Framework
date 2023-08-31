#ifndef LOGGER_H
#define LOGGER_H

#pragma once

#include "../singleton/singleton.h"
#include <chrono>
#include <ctime>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
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
            std::string file;
            int line;
            Info(const std::string& file = "", int line = 0)
            {
                this->file = file;
                this->line = line;
            }
        };

    private:
        friend class Singleton<LTF::Logger>;

    private:
        // class attributes
        std::ofstream m_file;
        std::mutex m_lock;
        LTF::Logger::Level m_level;
        std::string m_path;
        int m_message_count = 0;

    private:
        // CTORS
        Logger() = default;
        ~Logger();

        Logger(const Logger& rhs) = delete;
        Logger& operator=(const Logger& rhs) = delete;

    private:
        // helper methods
        std::string level_str(LTF::Logger::Level level) const;
        std::string format_output(const std::string& level, const std::string& time, const LTF::Logger::Info& info, const std::string& message);
        std::string get_time_stamp();
        inline bool should_print(LTF::Logger::Level level) const { return level <= this->m_level; }
        void rotate_log_file();

    public:
        // core fucntionalities
        void log(LTF::Logger::Level level, const std::string& message, const Info& info);
        void level(LTF::Logger::Level level);
        void open(const std::string& path);

        // for testing
        inline int count() { return this->m_message_count; }
    };
};

#endif // LOGGER_H

#include "logger.h"

LTF::Logger::~Logger()
{
    if (!this->m_file.is_open()) return;
    this->m_file.close();
}

std::string LTF::Logger::level_str(LTF::Logger::Level level) const
{
    std::string str = "";
    switch (level)
    {
    case LTF::Logger::Level::DEBUG:
        str = "DEBUG";
        break;
    case LTF::Logger::Level::ERROR:
        str = "ERROR";
        break;
    case LTF::Logger::Level::FATAL:
        str = "FATAL";
        break;
    case LTF::Logger::Level::INFO:
        str = "INFO";
        break;
    case LTF::Logger::Level::WARN:
        str = "WARN";
        break;
    default:
        throw std::runtime_error("input level does not exist");
        break;
    }
    return str;
}

std::string LTF::Logger::get_time_stamp()
{
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);

    // Convert to Pacific Time (UTC-7 or UTC-8 depending on daylight saving time)
    std::tm pacific_time;

    // platform specific
#ifdef _WIN32
    gmtime_s(&pacific_time, &current_time);
#else
    gmtime_r(&current_time, &pacific_time);
#endif

    pacific_time.tm_hour -= 7;                         // UTC-7
    if (pacific_time.tm_isdst) pacific_time.tm_hour++; // Adjust for daylight saving time (UTC-8)

    // Convert to string
    std::ostringstream oss;
    oss << std::put_time(&pacific_time, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string LTF::Logger::format_output(const std::string& level, const std::string& time, const LTF::Logger::Info& info, const std::string& message)
{
    std::string output_str = "";
    output_str += time + " " + level + " " + info.file + ":" + std::to_string(info.line) + " " + message;
    return output_str;
}

void LTF::Logger::log(LTF::Logger::Level level, const std::string& message, const Info& info)
{
    std::lock_guard<std::mutex> lock(this->m_lock);
    // if level too high then not log
    if (!this->should_print(level)) return;
    std::string time_output = this->get_time_stamp();
    std::string level_output = this->level_str(level);
    std::string output = this->format_output(level_output, time_output, info, message);
}

void LTF::Logger::level(LTF::Logger::Level level)
{
    this->m_level = level;
}

void LTF::Logger::open(const std::string& path)
{
    if (this->m_file.is_open()) this->m_file.close();
    this->m_file.open(path);
    if (this->m_file.fail()) throw std::logic_error("cannot open the file at " + path);
    this->m_path = path;
}
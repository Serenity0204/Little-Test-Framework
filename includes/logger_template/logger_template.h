#ifndef LOGGER_TEMPLATE_H
#define LOGGER_TEMPLATE_H

#pragma once

#include "../logger/logger.h"
#include "../singleton/singleton.h"

namespace LTF
{
// set path
#define LTF_LOG_INIT(path) LTF::Singleton<LTF::Logger>::instance().open(path);

// set level
#define LTF_LOG_LEVEL(input_level) LTF::Singleton<LTF::Logger>::instance().level(input_level);

// debug
#define LTF_DEBUG(message) LTF::Singleton<LTF::Logger>::instance().log(LTF::Logger::Level::DEBUG, message, LTF::Logger::Info(__FILE__, __LINE__));

// info
#define LTF_INFO(message) LTF::Singleton<LTF::Logger>::instance().log(LTF::Logger::Level::INFO, message, LTF::Logger::Info(__FILE__, __LINE__));

// warning
#define LTF_WARNING(message) LTF::Singleton<LTF::Logger>::instance().log(LTF::Logger::Level::WARNING, message, LTF::Logger::Info(__FILE__, __LINE__));

// error
#define LTF_ERROR(message) LTF::Singleton<LTF::Logger>::instance().log(LTF::Logger::Level::ERROR, message, LTF::Logger::Info(__FILE__, __LINE__));

// fatal
#define LTF_FATAL(message) LTF::Singleton<LTF::Logger>::instance().log(LTF::Logger::Level::FATAL, message, LTF::Logger::Info(__FILE__, __LINE__));
};

#endif // LOGGER_TEMPLATE_H

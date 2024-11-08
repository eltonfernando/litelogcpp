#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#define CSI "\x1B[" // Control Sequence Introducer (ANSI spec name)
#define CLEAR CSI "0m"
#define WHITE CSI "0;37m"
#define GREEN CSI "0;32m"
#define YELLOW CSI "0;33m"
#define RED CSI "0;31m"
#define RED_BOLD CSI "1;31m"

//------------------------------------------------------------------

class Logging
{
public:
    enum class LogLevel
    {
        DEBUG = 0,
        INFO,
        WARN,
        ERROR,
        FATAL
    };
    static std::string toString(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::FATAL:
            return "FATAL";
        }
        return "UNKNOWN";
    }

    static std::string colorLog(LogLevel level, std::string &message)
    {
        switch (level)
        {
        case LogLevel::DEBUG:
            return WHITE + message + CLEAR;
        case LogLevel::INFO:
            return GREEN + message + CLEAR;
        case LogLevel::WARN:
            return YELLOW + message + CLEAR;
        case LogLevel::ERROR:
            return RED + message + CLEAR;
        case LogLevel::FATAL:
            return RED_BOLD + message + CLEAR;
        }
        return "UNKNOWN";
    }
    static Logging &getInstance()
    {
        static Logging instance;
        return instance;
    }
    void log(LogLevel level, const std::string &file, int line, const std::string &message);
    void debug(const std::string &file, const int &line, const std::string &message);
    void setLevel(LogLevel level) { this->level = level; }
    std::string getCurrentDateTime();

    //~Logging();
private:
    LogLevel level = LogLevel::DEBUG;

};

//---------------------------------------------------------------------

#define LOG_DEBUG(message) Logging::getInstance().log(Logging::LogLevel::DEBUG,__FILE__, __LINE__, message)
#define LOG_INFO(message) Logging::getInstance().log(Logging::LogLevel::INFO, __FILE__, __LINE__, message)
#define LOG_WARN(message) Logging::getInstance().log(Logging::LogLevel::WARN, __FILE__, __LINE__, message)
#define LOG_ERROR(message) Logging::getInstance().log(Logging::LogLevel::ERROR, __FILE__, __LINE__, message)
#define LOG_FATAL(message) Logging::getInstance().log(Logging::LogLevel::FATAL, __FILE__, __LINE__, message)

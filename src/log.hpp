#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <memory>
#include <fstream>

#define CSI "\x1B[" // Control Sequence Introducer (ANSI spec name)
#define CLEAR CSI "0m"
#define WHITE CSI "0;37m"
#define GREEN CSI "0;32m"
#define YELLOW CSI "0;33m"
#define RED CSI "0;31m"
#define RED_BOLD CSI "1;31m"

enum class LogLevel
{
    DEBUG = 0,
    INFO,
    WARN,
    ERROR,
    FATAL
};

//------------------------------------------------------------------
class ILogger
{
public:
    virtual void write(LogLevel currentLevel, const std::string &message) = 0;
};

//------------------------------------------------------------------

class SysLog : public ILogger
{
public:
    SysLog();
    SysLog(LogLevel loggerLevel);
    virtual void write(LogLevel currentLevel, const std::string &message);

private:
    std::string colorLog(LogLevel currentLevel, const std::string &message);
    LogLevel level = LogLevel::DEBUG;
};


class FileWriter: public ILogger
{
public:
    explicit FileWriter(const std::string &filename);
    ~FileWriter();
    virtual void write(LogLevel currentLevel, const std::string &message);
    void close();
    private:
        std::ofstream m_file;
        std::string m_filename;
        LogLevel level = LogLevel::DEBUG;

};



class Logging
{
public:
    static Logging &getInstance()
    {
        static Logging instance;
       if (instance.loggers.empty()){
            instance.loggers.push_back(std::make_unique<SysLog>(LogLevel::DEBUG));
            instance.loggers.push_back(std::make_unique<FileWriter>("log.txt"));}
        return instance;
    }
    std::string toString(LogLevel level);
    void log(LogLevel level, const std::string &file, int line, const std::string &message);
    void debug(const std::string &file, const int &line, const std::string &message);
    void setLevel(LogLevel level) { this->level = level; }
    std::string getCurrentDateTime();
    //~Logging();
private:
    LogLevel level = LogLevel::DEBUG;
    std::vector<std::unique_ptr<ILogger>> loggers;
};




#define LOG_DEBUG(message) Logging::getInstance().log(LogLevel::DEBUG, __FILE__, __LINE__, message)
#define LOG_INFO(message) Logging::getInstance().log(LogLevel::INFO, __FILE__, __LINE__, message)
#define LOG_WARN(message) Logging::getInstance().log(LogLevel::WARN, __FILE__, __LINE__, message)
#define LOG_ERROR(message) Logging::getInstance().log(LogLevel::ERROR, __FILE__, __LINE__, message)
#define LOG_FATAL(message) Logging::getInstance().log(LogLevel::FATAL, __FILE__, __LINE__, message)

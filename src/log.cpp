#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "log.hpp"

SysLog::SysLog() {
    level = Logging::LogLevel::DEBUG;
}
SysLog::SysLog(Logging::LogLevel loggerLevel) {
    level = loggerLevel;
}
void SysLog::write(Logging::LogLevel currentLevel, const std::string &message) {
    std::cout << colorLog(currentLevel,message) << std::endl;
}

std::string SysLog::colorLog(Logging::LogLevel currentLevel, const std::string &message) {
    {
            switch (currentLevel)
            {
            case Logging::LogLevel::DEBUG:
                return WHITE + message + CLEAR;
            case Logging::LogLevel::INFO:
                return GREEN + message + CLEAR;
            case Logging::LogLevel::WARN:
                return YELLOW + message + CLEAR;
            case Logging::LogLevel::ERROR:
                return RED + message + CLEAR;
            case Logging::LogLevel::FATAL:
                return RED_BOLD + message + CLEAR;
            }
            return "UNKNOWN";
        }
}

void Logging::log(LogLevel currenteLevel, const std::string& file,int line ,const std::string& message){
    if (this->level > currenteLevel)
        return;
    auto msg = getCurrentDateTime() + " "+toString(currenteLevel) + " " + file + ":" + std::to_string(line) + " " + message;
   // for (auto& logger : loggers)
  //      logger->write(currenteLevel, msg);
}
std::string Logging::getCurrentDateTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm localTime = *std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
        return oss.str();
}
void Logging::debug(const std::string& file, const int& line, const std::string& message){
    if (level > LogLevel::DEBUG)
        return;
    log(LogLevel::DEBUG, file, line, message);
}

#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "log.hpp"





void Logging::log(LogLevel level, const std::string& file,int line ,const std::string& message){
    if (this->level > level)
        return;
    auto msg = getCurrentDateTime() + " "+toString(level) + " " + file + ":" + std::to_string(line) + " " + message;
    std::cout <<colorLog(level, msg)<< std::endl;

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

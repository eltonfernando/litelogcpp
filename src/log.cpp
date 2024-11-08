#include <iostream>
#include "log.hpp"





void Logging::log(LogLevel level, const std::string& file,int line ,const std::string& message){
    if (this->level > level)
        return;
    auto msg = toString(level) + " " + file + ":" + std::to_string(line) + " " + message;
    std::cout <<colorLog(level, msg)<< std::endl;

}

void Logging::debug(const std::string& file, const int& line, const std::string& message){
    if (level > LogLevel::DEBUG)
        return;
    log(LogLevel::DEBUG, file, line, message);
}

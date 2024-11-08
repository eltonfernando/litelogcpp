#include <stdio.h>
#include <iostream>
#include "src/log.hpp"
#include <vector>
#include <memory>


int main()
{   
    auto logFile = std::make_unique<FileWriter>("logxx.txt");
    //logFile->setLevel(LogLevel::INFO);
    auto logSys = std::make_unique<SysLog>();
    logSys->setLevel(LogLevel::DEBUG);

    Logging::getInstance().addLogger(std::move(logFile));
    Logging::getInstance().addLogger(std::move(logSys));
   
    LOG_DEBUG("Elton Hello World!");
    LOG_INFO("Elton Hello World!");
    LOG_WARN("Elton Hello World!");
    LOG_ERROR("Elton Hello World!");
    LOG_FATAL("Elton Hello World!");
    return 0;
}
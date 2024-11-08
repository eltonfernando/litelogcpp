#include <stdio.h>
#include <iostream>
#include "src/log.hpp"
int main()
{   //Logging::getInstance();
    Logging::getInstance().setLevel(Logging::LogLevel::ERROR);
    //SysLog *log = new SysLog(Logging::LogLevel::ERROR);
    //Logging::getInstance().addLogger(log);
    LOG_DEBUG("Elton Hello World!");
    LOG_INFO("Elton Hello World!");
    LOG_WARN("Elton Hello World!");
    LOG_ERROR("Elton Hello World!");
    LOG_FATAL("Elton Hello World!");
    return 0;
}
#include <stdio.h>
#include <iostream>
#include "log.hpp"
int main()
{   
    Logging::getInstance().setLevel(Logging::LogLevel::ERROR);
    LOG_DEBUG("Elton Hello World!");
    LOG_INFO("Elton Hello World!");
    LOG_WARN("Elton Hello World!");
    LOG_ERROR("Elton Hello World!");
    LOG_FATAL("Elton Hello World!");
    return 0;
}
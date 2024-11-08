#include <stdio.h>
#include <iostream>
#include "src/log.hpp"
#include <vector>
#include <memory>


int main()
{   
    Logging::getInstance();
    Logging::getInstance().setLevel(LogLevel::INFO);
    LOG_DEBUG("Elton Hello World!");
    LOG_INFO("Elton Hello World!");
    LOG_WARN("Elton Hello World!");
    LOG_ERROR("Elton Hello World!");
    LOG_FATAL("Elton Hello World!");
    return 0;
}
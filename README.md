# litelogcpp
Lib de logging para c++

![](doc/image.png)
## Features

1. [ x ] Console log
2. [ x ] File log
3. [ x ] Color log file
4. [ x ] Thread safey
5. [  ] Benchmarks

build 
```shel
git clone https://github.com/eltonfernando/litelogcpp.git
cd litelogcpp
mkdir build
cd build
cmake ..
make
```

```c++
#include <stdio.h>
#include <iostream>
#include "src/log.hpp"
#include <vector>
#include <memory>


int main()
{   
    auto logFile = std::make_unique<FileWriter>("log.txt");
    logFile->setLevel(LogLevel::INFO);
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
```


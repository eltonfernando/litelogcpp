# litelogcpp
Lib de logging para c++

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
#include "log.hpp"
int main()
{   
    Logging::getInstance().setLevel(Logging::LogLevel::INFO);
    LOG_DEBUG("Elton Hello World!");
    LOG_INFO("Elton Hello World!");
    LOG_WARN("Elton Hello World!");
    LOG_ERROR("Elton Hello World!");
    LOG_FATAL("Elton Hello World!");
    return 0;
}
```
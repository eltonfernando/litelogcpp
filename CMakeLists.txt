cmake_minimum_required(VERSION 3.0.0)

project(litelogcpp VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(litelogcpp main.cpp src/log.cpp)

target_include_directories(litelogcpp PUBLIC src)
target_link_libraries(litelogcpp stdc++fs)

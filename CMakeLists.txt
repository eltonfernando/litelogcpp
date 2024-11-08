cmake_minimum_required(VERSION 3.0.0)

project(litelogcpp VERSION 0.1.0)

add_executable(litelogcpp main.cpp src/log.cpp)

target_include_directories(litelogcpp PUBLIC src)
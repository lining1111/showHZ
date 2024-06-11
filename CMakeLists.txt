cmake_minimum_required(VERSION 3.27)
project(showHZ)

set(CMAKE_CXX_STANDARD 11)

add_executable(showHZ main.cpp
        gpu.cpp
        gpu.h
        font.cpp
        font.h
        display.cpp
        display.h
        utils.cpp
        utils.h)
target_link_libraries(showHZ)

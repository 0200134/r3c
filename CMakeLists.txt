cmake_minimum_required(VERSION 3.14)
project(r3c LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(r3c
    src/main.cpp
    
    src/transpiler.cpp
)

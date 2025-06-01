cmake_minimum_required(VERSION 3.15)

project(mips LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mips main.cpp
        include/execute.cpp
        include/instructions.cpp
        include/constants.cpp
)

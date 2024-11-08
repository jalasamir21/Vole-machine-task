cmake_minimum_required(VERSION 3.27)
project(untitled6)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled6 main.cpp
        Register.cpp
        Register.h
        Memory.cpp
        Memory.h
        CPU.cpp
        CPU.h
        CU.cpp
        CU.h
        ALU.cpp
        ALU.h
        MainUi.cpp
        MainUi.h
        Machine.cpp
        Machine.h)

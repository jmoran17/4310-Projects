cmake_minimum_required(VERSION 3.10)
project(Project1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/sorting.cpp
)

add_executable(Project1 ${SOURCES})
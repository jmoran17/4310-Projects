cmake_minimum_required(VERSION 3.10)
project(Project1)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the header files
include_directories(include)

# Add all source files
set(SOURCES
    src/main.cpp
    src/parser.cpp
    src/scheduler.cpp
    src/sorting.cpp
)

# Create the executable
add_executable(Project1 ${SOURCES})
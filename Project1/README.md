Project 1: Multithreaded Sorting & CPU Scheduling Simulation
============================================================

Author: Joseph Moran
Date: 24 October 2025
Course: CS 4310 - Operating Systems

Overview
--------
This project demonstrates two main concepts:

1. Multithreaded sorting: A demonstration of concurrent execution using C++ threads.
2. CPU scheduling simulation: Implements several CPU scheduling algorithms (FCFS, SJF, Preemptive Priority, and Round Robin) to simulate process management.

Input
-----
The CPU scheduling simulation reads process information from "input.txt" with the following format:

Pid Arrival_Time Burst_Time Priority

- Pid: Unique numeric process ID
- Arrival_Time: Time the task arrives (milliseconds)
- Burst_Time: CPU time requested by the task (milliseconds)
- Priority: Task priority (lower number = higher priority)

Sorting uses a predefined array within the program.

Building the Project
-------------------
# If you already have the project build skip to running program step 2

1. Create a build directory:
   mkdir build
   cd build

2. Run CMake to configure:
   cmake ..

3. Build the executable:
   cmake --build .

Running the Program
-------------------
1. Navigate to the root directory:
   cd ..

2. If you already have the program build or after building run the executable in terminal:
   .\build\Debug\Project1.exe

Function
--------
1. The program first runs a multithreaded sorting example.
2. It then prompts the user to select a CPU scheduling algorithm:
   - FCFS
   - SJF
   - Preemptive Priority
   - Round Robin

3. The selected algorithm will run on the processes read from "input.txt", and metrics will be displayed (waiting time, turnaround time, etc.).

Notes
-----
- Ensure "input.txt" is located in the root project directory or provide the correct path.
- The project uses C++17 and standard threading libraries.
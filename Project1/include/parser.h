#ifndef PARSER_H
#define PARSER_H

#include <sstream>
#include <string>
#include <vector>

//class to hold process information
class Process{
    public:
        int Pid;
        int arrivalTime;
        int burstTime;
        int priority;
        int remainingTime;
        bool completed = false;
        
        int waitingTime = 0;
        int turnaroundTime = 0;
        int responseTime = -1;
        int endTime = 0;
};

std::vector<Process> parseProcess(const std::string& filename);

#endif
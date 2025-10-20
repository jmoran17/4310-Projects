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
};

Process parseProcess(std::vector<std::string>& fileName);

#endif
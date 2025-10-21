#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "parser.h"
#include <vector>

//struct for average metrics
struct Metrics{
    int totalWait = 0;
    int totalTurn = 0;
    int totalResponse = 0;
    int busyTime = 0;

    float avgWait = 0.0f;
    float avgTurn = 0.0f;
    float avgResponse= 0.0f;
    float cpuUtil = 0.0f;
};

//functions for parsing the file and running the scheduling algorithm
Metrics FCFS(std::vector<Process>& Processes);
Metrics SJF(std::vector<Process>& Processes);
Metrics Preemptive(std::vector<Process>& Processes);
Metrics RR(std::vector<Process>& Processes, int quantum);

#endif
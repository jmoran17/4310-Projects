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
void initalizeProcess(std::vector<Process>& Processes);
Metrics metricCalcs(const std::vector<Process>& Processes, Metrics& m, int currentTime);
void arrivalSort(std::vector<Process>& Processes);
int jumpToNext(std::vector<Process>& Processes, int currentTime);
std::vector<Process*> readyQueue(std::vector<Process>& Processes, int currentTime);
void runProcess(Process& p, int& currentTime, int duration);
Metrics FCFS(std::vector<Process>& Processes);
Metrics SJF(std::vector<Process>& Processes);
Metrics Preemptive(std::vector<Process>& Processes);
Metrics RR(std::vector<Process>& Processes, int quantum);

#endif
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "parser.h"
#include <vector>

//functions for parsing the file and running the scheduling algorithm
std::vector<Process> FCFS(const std::vector<Process> Processes);
std::vector<Process> SJF(const std::vector<Process> Processes);
std::vector<Process> Preemptive(const std::vector<Process> Processes);
std::vector<Process> RR(const std::vector<Process> Processes, int quantum);

#endif
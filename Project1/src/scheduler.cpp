#include "scheduler.h"
#include <algorithm>
#include <iostream>

Metrics metricCalcs(const std::vector<Process>& Processes, Metrics& m, const int currentTime){
    //calculate totals
    for(const auto& p : Processes){
        m.busyTime += p.burstTime;
        m.totalWait += p.waitingTime;
        m.totalTurn += p.turnaroundTime;
        m.totalResponse += p.responseTime;
    }
    //compute averages using Process array size
    m.avgWait = static_cast<float>(m.totalWait) / Processes.size();
    m.avgTurn = static_cast<float>(m.totalTurn) / Processes.size();
    m.avgResponse = static_cast<float>(m.totalResponse) / Processes.size();
    m.cpuUtil = (static_cast<float>(m.busyTime) / currentTime) * 100;
    //return metric file
    return m;
}

void processCalcs(std::vector<Process>& Processes, int& currentTime){
    for(auto& p : Processes){
        if(currentTime <= p.arrivalTime){
            currentTime = p.arrivalTime;
        }
        p.waitingTime = currentTime - p.arrivalTime;//calculates against initial currentTime
        p.responseTime = p.waitingTime;
        p.turnaroundTime = currentTime - p.arrivalTime;//uses currentTime after burst has been added
    }
}

void runProcess(Process& p, int& currentTime, int duration){
    if(currentTime <= p.arrivalTime){
            currentTime = p.arrivalTime;
        }
        p.waitingTime = currentTime - p.arrivalTime;//calculates against initial currentTime
        p.responseTime = p.waitingTime;
        p.turnaroundTime = currentTime - p.arrivalTime;//uses currentTime after burst has been added
    
    for(int t = 0; t < duration; t++){
            currentTime++;
            std::cout<< "Time " << currentTime << " milliseconds: Process " << p.Pid << " is running. \n";
        }
    }
}
Metrics FCFS(std::vector<Process>& Processes){
    //initialize metrics and currentTime
    Metrics m; 
    int currentTime = 0;

    //sort the Processes by arrival time to get a FCFS order
    std::sort(Processes.begin(), Processes.end(),
        [](const Process& a, const Process& b){return a.arrivalTime < b.arrivalTime; });


    processCalcs(Processes, currentTime);
    m = metricCalcs(Processes, m, currentTime);

    return m;
}

Metrics SJF( std::vector<Process>& Processes){
    //initialize metrics and currentTime
    Metrics m;
    int currentTime = 0;
    std::vector<Process> ready;
    //sort processes by arrival time to get SJF order
    std::sort(Processes.begin(), Processes.end(),
        [](const Process& a, const Process& b){return a.burstTime < b.burstTime; });
    for (auto& p : Processes){
        if(currentTime >= p.arrivalTime){
            ready.push_back(p);
        }
    }
    logger(Processes, currentTime);
    processCalcs(Processes, currentTime);
    m = metricCalcs(Processes, m, currentTime);

    return m;
}

Metrics Preemptive( std::vector<Process>& Processes){
    Metrics m;
    return m;
}

Metrics RR(std::vector<Process>& Processes, int quantum){
    Metrics m;
    return m;
}
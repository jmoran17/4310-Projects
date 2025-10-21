#include "scheduler.h"
#include <algorithm>
#include <iostream>

Metrics FCFS(std::vector<Process>& Processes){
    //initialize metrics
    Metrics m;

    //sort the Processes by arrival time to get a FCFS order
    std::sort(Processes.begin(), Processes.end(),
        [](const Process& a, const Process& b){return a.arrivalTime < b.arrivalTime; });
    int currentTime = 0;
    for(auto& p : Processes){
        if(currentTime <= p.arrivalTime){
            currentTime = p.arrivalTime;
        }
        p.waitingTime = currentTime - p.arrivalTime;//calculates against initial currentTime
        p.responseTime = p.waitingTime;
        //for loop printing progress of task every ms
        for(int t = 0; t < p.burstTime; t++){
            currentTime++;
            std::cout<< "Time " << currentTime << " milliseconds: Process " << p.Pid << " is running. \n";
        }

        p.turnaroundTime = currentTime - p.arrivalTime;//uses currentTime after burst has been added
    }

    for (auto& p : Processes){
        m.busyTime += p.burstTime;
        m.totalWait += p.waitingTime;
        m.totalTurn += p.turnaroundTime;
        m.totalResponse += p.responseTime;
    }
    m.avgWait = static_cast<float>(m.totalWait) / Processes.size();
    m.avgTurn = static_cast<float>(m.totalTurn) / Processes.size();
    m.avgResponse = static_cast<float>(m.totalResponse) / Processes.size();
    m.cpuUtil = (static_cast<float>(m.busyTime) / currentTime) * 100;
    return m;
}

Metrics SJF(const std::vector<Process>& Processes){

}

Metrics Preemptive(const std::vector<Process>& Processes){


}

Metrics RR(const std::vector<Process>& Processes, int quantum){

}
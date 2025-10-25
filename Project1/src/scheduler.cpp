#include "scheduler.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>

void initializeProcess(std::vector<Process>& Processes){
    for (auto& p : Processes) {
        p.remainingTime = p.burstTime;
        p.completed = false;
        p.waitingTime = 0;
        p.turnaroundTime = 0;
        p.responseTime = -1;
    }
}

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

void arrivalSort(std::vector<Process>& Processes){
    std::sort(Processes.begin(), Processes.end(),
        [](const Process& a, const Process& b){return a.arrivalTime < b.arrivalTime; });
}

int jumpToNext(std::vector<Process>& Processes, int currentTime){
        int nextArrival = INT_MAX;
        for(auto& p : Processes){
            if(!p.completed && p.arrivalTime > currentTime){
                nextArrival = std::min(nextArrival, p.arrivalTime);
            }
        }
        return nextArrival;
}

std::vector<Process*> readyQueue(std::vector<Process>& Processes, int currentTime){
    std::vector<Process*> ready;
    for(auto& p : Processes){
        if(!p.completed && p.arrivalTime <= currentTime){
            ready.push_back(&p);
        }
    }
    return ready;
}


void runProcess(Process& p, int& currentTime, int duration){
    if (currentTime < p.arrivalTime) {
        currentTime = p.arrivalTime;
    }

    // Record response time 
    if (p.responseTime == -1)
        p.responseTime = currentTime - p.arrivalTime;

    // Execute for 'duration' units 
    for (int t = 0; t < duration; t++) {
        currentTime++;
        std::cout << "Time " << currentTime
                  << " ms: Process " << p.Pid
                  << " is running.\n";
        // Reduce remaining time every iteration
        p.remainingTime--;
    }

    // If process finished, update metrics
    if (p.remainingTime <= 0) {
        p.completed = true;
        p.turnaroundTime = currentTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
    }
}

Metrics FCFS(std::vector<Process>& Processes){
    //initialize metrics and currentTime
    Metrics m; 
    int currentTime = 0;

    //initialize and sort the Processes by arrival time
    initializeProcess(Processes);
    arrivalSort(Processes);

    for(auto& p : Processes){
        runProcess(p, currentTime, p.burstTime);
    }
    m = metricCalcs(Processes, m, currentTime);

    return m;
}

Metrics SJF( std::vector<Process>& Processes){
    //initialize metrics and currentTime
    Metrics m;
    int currentTime = 0;
    int completed = 0;
    int totalProcesses = Processes.size();

    
    //initialize and sort the Processes by arrival time
    initializeProcess(Processes);
    arrivalSort(Processes);

    while(completed < totalProcesses){
        auto ready = readyQueue(Processes, currentTime);
    

        if(ready.empty()){
            int nextArrival = INT_MAX;
            for(auto& p : Processes){
                if(!p.completed){
                    nextArrival = std::min(nextArrival, p.arrivalTime);
                }
            }
            currentTime = nextArrival;
            continue;
        }

        Process* shortest = ready[0];
        for(auto& p : ready){
        if(p->burstTime < shortest->burstTime){
            shortest = p;
        }
    }
        runProcess(*shortest, currentTime, shortest->burstTime);
    
        shortest->completed = true;
        completed++;
    }
    m = metricCalcs(Processes, m, currentTime);

    return m;
}

Metrics Preemptive(std::vector<Process>& Processes){
    Metrics m;
    int currentTime = 0;
    int completed = 0;
    int totalProcesses = Processes.size();

    //initialize and sort the Processes by arrival time
    initializeProcess(Processes);
    arrivalSort(Processes);

    while(completed < totalProcesses){
        auto ready = readyQueue(Processes, currentTime);

        if (ready.empty()) {
            currentTime = jumpToNext(Processes, currentTime);
            continue;
        }

        Process* highest = ready[0];
        for(auto* p : ready){
            if (p->priority < highest->priority) {
                highest = p;
            } else if (p->priority == highest->priority) {
                if (p->arrivalTime < highest->arrivalTime){
                    highest = p;
                }
            }
        }

        runProcess(*highest, currentTime, 1);
        if(highest->completed){
            completed++;
        }
    }
    m = metricCalcs(Processes, m, currentTime);

    return m;
}

Metrics RR(std::vector<Process>& Processes, int quantum){
    Metrics m;
    int currentTime = 0;
    int completed = 0;
    int nxtIndex = 0;
    int totalProcesses = Processes.size();

    //initialize and sort the Processes by arrival time
    initializeProcess(Processes);
    arrivalSort(Processes);

    std::queue<Process*> rrQueue;
    std::unordered_set<Process*> inQueue;

    for(auto& p : Processes){
        if(p.arrivalTime <= currentTime){
            rrQueue.push(&p);
            inQueue.insert(&p);
        }
    }


    while(completed < totalProcesses){
       
        if(rrQueue.empty()){
            currentTime = jumpToNext(Processes,currentTime);
        }

        //add new arrived processes to queue
        auto ready = readyQueue(Processes, currentTime);
        for(auto* p : ready){
            if(inQueue.find(p) == inQueue.end() && !p->completed){
                rrQueue.push(p);
                inQueue.insert(p);
            }
        }
        
        //check if still empty
        if(rrQueue.empty()){
            continue;
        }

        //get nxt Process
        Process* p = rrQueue.front();
        rrQueue.pop();
        inQueue.erase(p);

        int runTime = std::min(quantum, p->remainingTime);
        runProcess(*p, currentTime, runTime);

        if(!p->completed){
                // Re-add unfinished process to the queue
            rrQueue.push(p);
            inQueue.insert(p);
        } else {
                completed++;
            }
    }

    m = metricCalcs(Processes, m, currentTime);
    return m;
}